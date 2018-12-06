#include "LV_interface.h"
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

const int N_MOTORS = 2;
// these vars keep memory of time and number of cycles of 2 motors indipendently
int halfCyclesToEnd[N_MOTORS] = {0, 0};
unsigned long TimeRef[N_MOTORS] = {0, 0};
unsigned long TimeCount[N_MOTORS] = {0, 0};

// this var enables indipendent step move on 2-axis
bool stepmove[N_MOTORS] = {0, 0};

//bytes available on Serial
int BytesToRead = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Create a Data object able to communicate with Labview software
LabviewData LVdata;
LabviewMotor LVmotor[N_MOTORS];
// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #1 (M1 and M2) and #2 (M3 and M4)
Adafruit_StepperMotor *MotorX = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *MotorY = AFMS.getStepper(200, 2);

// wrappers for the first motor! - Needed as input of AccelStepper object!
void forwardstepX() {
  MotorX->onestep(FORWARD, DOUBLE);
}
void backwardstepX() {
  MotorX->onestep(BACKWARD, DOUBLE);
}
// wrappers for the second motor! - Needed as input of AccelStepper object!
void forwardstepY() {
  MotorY->onestep(FORWARD, DOUBLE);
}
void backwardstepY() {
  MotorY->onestep(BACKWARD, DOUBLE);
}

// Now we'll wrap the 2 steppers in an AccelStepper object
AccelStepper StepperX(forwardstepX, backwardstepX);
AccelStepper StepperY(forwardstepY, backwardstepY);

//i'm wrapping the AccelStepper objects and Adafruit_StepperMotor in an array. In this way i can use the index of array for function abstraction
Adafruit_StepperMotor *Motor_collection[N_MOTORS] = {MotorX, MotorY};
AccelStepper Stepper_collection[N_MOTORS] = {StepperX, StepperY};

void setup() {
  //Initialize a serial connection - defaut = 9600 bps
  LVdata.SerialBegin(115200);
  // create with the default frequency 1.6KHz
  AFMS.begin();
  //set speed, max speed and acceleration for Stepper X and Y
  for (int i = 0; i < 2; i++)
  {
    LVmotor[i].speed = 100;
    Stepper_collection[i].setMaxSpeed(900.0f);
    Stepper_collection[i].setAcceleration(200.0f);
    Stepper_collection[i].setSpeed(100);
  }
}

void loop()
{
  BytesToRead = Serial.available();
  //check if a new command has been sent
  if (BytesToRead >= 6)
  {
    //parse the incoming packet: 1Byte - MotorIndex, 1Byte - Command, 4Bytes - Parameter (uint32_t or float)
    LVdata.SerialRead(BytesToRead);
    //place the data in the right place depending on the command received
    switch (LVdata.getCmd())
    {
      case   NONE:
        break;
      case SET_MOTOR:
        LVmotor[LVdata.getIndex()].motor = LVdata.getMotor();
        break;
      case SET_DISTANCE:
        LVmotor[LVdata.getIndex()].distance = LVdata.getDistance();
        break;
      case SET_SPEED:
        LVmotor[LVdata.getIndex()].speed = LVdata.getSpeed();
        //the speed has to be set before the movement so let's do it now
        Stepper_collection[LVdata.getIndex()].setSpeed(LVmotor[LVdata.getIndex()].speed);
        break;
      case SET_MOVE_TYPE:
        LVmotor[LVdata.getIndex()].movetype = LVdata.getMoveType();
        break;
      case SET_IM_TIME:
        LVmotor[LVdata.getIndex()].im_time = LVdata.getIMtime();
        break;
      case SET_N_CYCLES:
        //static save the total number of cycles
        LVmotor[LVdata.getIndex()].Ncycles = LVdata.getNcycles();
        //save the cycle number on the sweep variable too
        halfCyclesToEnd[LVdata.getIndex()] =  2 * LVmotor[LVdata.getIndex()].Ncycles + 1;  //needed because i update counter each half-cycle (2*number) and at the beginning (+1)
        break;
      case START:
      case STOP:
        LVmotor[LVdata.getIndex()].go = LVdata.operate();
        break;
      case STOP_AND_RELEASE:
        LVmotor[LVdata.getIndex()].go = LVdata.operate();
        //release the torque on the stopped motor
        Motor_collection[LVdata.getIndex()]->release();
        break;
      case SET_HOME:
        Stepper_collection[0].setCurrentPosition(StepperX.currentPosition());
        Stepper_collection[1].setCurrentPosition(StepperY.currentPosition());
        //needed after setCurrentPosition
        Stepper_collection[0].setSpeed(LVmotor[0].speed);
        Stepper_collection[1].setSpeed(LVmotor[1].speed);
        break;
      case FIND_HOME:
      //NOT WORKING///////////////////////////////////////////////////////////////////////////////////////////////////
      case STEPMOVE_FORWARD:
        break;
      case STEPMOVE_BACKWARD:
        break;
    }
  }
  //Move the motors depending on the command received
  for (int i = 0; i < N_MOTORS; i++)
  {
    if (LVmotor[i].go)
    {
      switch (LVmotor[i].movetype)
      {
        case MOVE_FREE_FORWARD:
          //DEBUG//Motor_collection[i]->onestep(FORWARD, DOUBLE); //SPEED CANNOT WORK IF USED LIKE THIS
          FreeMove(i, "FORWARD");
          break;
        case MOVE_FREE_BACKWARD:
          //DEBUG//Motor_collection[i]->onestep(BACKWARD, DOUBLE); //SPEED CANNOT WORK IF USED LIKE THIS
          FreeMove(i, "BACKWARD");
          break;
        case CYCLE_FORWARD_FIRST:
          SimpleCycle(i, "FORWARD_FIRST");
          break;
        case CYCLE_BACKWARD_FIRST:
          SimpleCycle(i, "BACKWARD_FIRST");
          break;
        case MOVE_STEP_FORWARD:
          StepMove(i, "FORWARD");
          break;
        case MOVE_STEP_BACKWARD:
          StepMove(i, "BACKWARD");
          break;
      }
      //DEBUG//Stepper_collection[i].runSpeed(); //CONTROL SPEED BUT STRANGE BEHAVIOUR
      Stepper_collection[i].runSpeedToPosition(); //AWESOME!!!!!
    }
  }
}


//this function manages the Cycling of motors. Variables like halfCyclesToEnd, TimeRef and TimeCount are all
//index dependent (=array) so all the motors can be used in parallel indipendently one from each other.

void SimpleCycle (int motor_index, String direction)
{
  //if it's the first time this is called for a new series of cycles, then set the initial direction
  if (halfCyclesToEnd[motor_index] ==  2 * LVmotor[motor_index].Ncycles + 1 && direction == "BACKWARD_FIRST")
  {
    //the other case is not needed because "FORWARD_FIRST" is the standard case
    LVmotor[motor_index].distance = -LVmotor[motor_index].distance;
    LVmotor[motor_index].speed = -LVmotor[motor_index].speed;
  }
  //set the initial movement and speed
  if (halfCyclesToEnd[motor_index] ==  2 * LVmotor[motor_index].Ncycles + 1)
  {
    Stepper_collection[motor_index].move(LVmotor[motor_index].distance);
    Stepper_collection[motor_index].setSpeed(LVmotor[motor_index].speed);
    halfCyclesToEnd[motor_index]--;
  }
  // the half cycle is done, now wait IMtime
  if (Stepper_collection[motor_index].distanceToGo() == 0)
  {
    //start counting time
    if (TimeRef[motor_index] == 0)
    {
      //each time distanceToGo is zero half cycle has passed!
      halfCyclesToEnd[motor_index]--;
      //keep the initial time in memory
      TimeRef[motor_index] = millis();
    }
    //update timer
    if (TimeRef[motor_index] > 0) //count the time passing
    {
      TimeCount[motor_index] = millis() - TimeRef[motor_index];
    }
    //if IMtime has passed reset the counter and start moving back
    if (TimeCount[motor_index] >= LVmotor[motor_index].im_time)
    {
      TimeRef[motor_index] = 0;
      LVmotor[motor_index].distance = -LVmotor[motor_index].distance;
      Stepper_collection[motor_index].move(LVmotor[motor_index].distance);
      //need to set negative speed to move back or the control will behave in a strange way
      LVmotor[motor_index].speed = -LVmotor[motor_index].speed;
      Stepper_collection[motor_index].setSpeed(LVmotor[motor_index].speed);
    }
  }
  //if all the cycles hav been run stop the motor, release the torque and reset the time counter
  if (halfCyclesToEnd[motor_index] == 0)
  {
    //reset timer for next commands
    TimeRef[motor_index] = 0;
    LVmotor[motor_index].go = 0;
    Motor_collection[motor_index]->release();
  }
}


void FreeMove (int motor_index, String direction)
{
  if (direction == "BACKWARD")
  {
    Stepper_collection[motor_index].move(-1);
    Stepper_collection[motor_index].setSpeed(-LVmotor[motor_index].speed);
  }
  else
  {
    Stepper_collection[motor_index].move(1);
    Stepper_collection[motor_index].setSpeed(LVmotor[motor_index].speed);
  }
}

void StepMove (int motor_index, String direction)
{
  //check variables for backward - forward is standard
  if (direction == "BACKWARD" && stepmove[motor_index] == LOW)
  {
    Stepper_collection[motor_index].move(-LVmotor[motor_index].distance);
    Stepper_collection[motor_index].setSpeed(-LVmotor[motor_index].speed);
    stepmove[motor_index] = HIGH;
  }
  else if (direction == "FORWARD" && stepmove[motor_index] == LOW)
  {
    Stepper_collection[motor_index].move(LVmotor[motor_index].distance);
    Stepper_collection[motor_index].setSpeed(LVmotor[motor_index].speed);
    stepmove[motor_index] = HIGH;
  }
  if (Stepper_collection[motor_index].distanceToGo() == 0)
  {
    LVmotor[motor_index].go = 0;
    Motor_collection[motor_index]->release();
    //reset stepmove variable
    stepmove[motor_index] = LOW;
  }
}

