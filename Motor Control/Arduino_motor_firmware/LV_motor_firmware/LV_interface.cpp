/*
  LV_interface.cpp - Library for communicating with LabviewData software.
  Created by Francesco Maita, May 5, 2016.
*/

#include "Arduino.h"
#include "LV_interface.h"


LabviewData::LabviewData()
{

}

LabviewMotor::LabviewMotor()
{

}


void LabviewData::SerialBegin()
{
  Serial.begin(9600);
}

void LabviewData::SerialBegin(long baudrate)
{
  Serial.begin(baudrate);
}


void LabviewData::SerialEnd()
{
  Serial.end();
}

void LabviewData::SerialRead(int BytesToRead)
{
  byte RxBuffer[128];  //define a buffer of 32 bytes
  for (int i = 0; i < BytesToRead; i++) //read all the data available in the serial in the buffer
  {
    RxBuffer[i] = Serial.read();
  }
  _index = int(RxBuffer[0]); //1 byte for the motor index
  int CmdBuffer;
  CmdBuffer = int(RxBuffer[1]); //1 byte for the command type
  binaryFloat ParamBuffer; //4 bytes for the parameter
  for (int j = 0; j < 4; j++)
  {
    ParamBuffer.binary[j] = RxBuffer[j + 2];
  }
  switch (CmdBuffer)
  {
    case 0:
      _cmd = NONE;
      break;
    case 1:
      _cmd = SET_MOTOR;
      _motor = parseMotor(ParamBuffer.integer);
      break;
    case 2:
      _cmd = SET_DISTANCE;
      _distance = ParamBuffer.floatingPoint;
      break;
    case 3:
      _cmd = SET_SPEED;
      _speed = ParamBuffer.floatingPoint;
      break;
    case 4:
      _cmd = SET_MOVE_TYPE;
      _movetype = parseMoveType(ParamBuffer.integer);
      break;
    case 5:
      _cmd = SET_IM_TIME;
      _im_time = ParamBuffer.integer;
      break;
    case 6:
      _cmd = SET_N_CYCLES;
      _Ncycles = ParamBuffer.integer;
      break;
    case 7:
      _cmd = START;
      _go = HIGH;
      break;
    case 8:
      _cmd = STOP;
      _go = LOW;
      break;
    case 9:
      _cmd = STOP_AND_RELEASE;
      _go = LOW;
      break;
    case 10:
      _cmd = SET_HOME;
      break;
    case 11:
      _cmd = FIND_HOME;
      break;
    case 12:
      _cmd = STEPMOVE_FORWARD;
      break;
    case 13:
      _cmd = STEPMOVE_BACKWARD;
    default:
      _cmd = M_ERROR;
      break;
  }

}

int LabviewData::getIndex()
{
  return _index;
}

lv_cmd LabviewData::getCmd()
{
  return _cmd;
}

lv_motor LabviewData::getMotor()
{
  return _motor;
}

lv_movetype LabviewData::getMoveType()
{
  return _movetype;
}


float LabviewData::getSpeed()
{
  return _speed;
}

float LabviewData::getDistance()
{
  return _distance;
}

int LabviewData::getIMtime()
{
  return _im_time;
}

int LabviewData::getNcycles()
{
  return _Ncycles;
}

bool LabviewData::operate()
{
  return _go;
}

lv_motor LabviewData::parseMotor(int ParamBuffer)
{
  switch (ParamBuffer)
  {
    case 0:
      _steps_rev = 200;
      return NEVA_17;
      break;
    default:
      _steps_rev = 1;
      return NO_MOTOR;
      break;
  }
}


lv_movetype LabviewData::parseMoveType(int ParamBuffer)
{
  switch (ParamBuffer)
  {
    case 0:
      return MOVE_FREE_FORWARD;
      break;
    case 1:
      return MOVE_FREE_BACKWARD;
      break;
    case 2:
      return CYCLE_FORWARD_FIRST;
      break;
    case 3:
      return CYCLE_BACKWARD_FIRST;
      break;
    case 4:
      return MOVE_STEP_FORWARD;
      break;
    case 5:
      return MOVE_STEP_BACKWARD;
      break;
    default:
      return MOVE_FREE_FORWARD;
      break;
  }
}

