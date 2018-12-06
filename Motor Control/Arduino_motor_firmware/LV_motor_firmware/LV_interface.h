/*
  LV_interface.h - Library for communicating with Labview software.
  Created by Francesco Maita, May 5, 2016.
*/

#ifndef LV_interface_h
#define LV_interface_h

#include "Arduino.h"

typedef enum {
  M_ERROR = 255,
  NONE = 0,
  SET_MOTOR,
  SET_DISTANCE,
  SET_SPEED,
  SET_MOVE_TYPE,
  SET_IM_TIME,
  SET_N_CYCLES,
  START,
  STOP,
  STOP_AND_RELEASE,
  SET_HOME,
  FIND_HOME,
  STEPMOVE_FORWARD,
  STEPMOVE_BACKWARD
} lv_cmd;


typedef enum {
  NO_MOTOR = 255,
  NEVA_17 = 0
} lv_motor;

typedef enum {
  MOVE_FREE_FORWARD = 0,
  MOVE_FREE_BACKWARD,
  CYCLE_FORWARD_FIRST,
  CYCLE_BACKWARD_FIRST,
  MOVE_STEP_FORWARD,
  MOVE_STEP_BACKWARD
} lv_movetype;

typedef union {
  float floatingPoint;
  byte binary[4];
  int integer;
} binaryFloat;

class LabviewData
{
  public:
    LabviewData();
    void SerialBegin();
    void SerialBegin(long baudrate);
    void SerialEnd();
    void SerialRead(int BytesToRead);
    int getIndex();
    lv_cmd getCmd();
    lv_motor getMotor();
    lv_movetype getMoveType();
    float getSpeed();
    float getDistance();
    int getIMtime();
    int getNcycles();
    bool operate();
  private:
    int _index;
    lv_cmd _cmd;
    binaryFloat _ParamBuffer;
    lv_motor _motor;
    lv_movetype _movetype;
    float _speed;
    float _distance;
    int _im_time;
    int _Ncycles;
    int _steps_rev;
    bool _go;
    lv_motor parseMotor(int CmdBuffer);
    lv_movetype parseMoveType(int ParamBuffer);
};

class LabviewMotor
{
  public:
    LabviewMotor();
    lv_motor motor;
    lv_movetype movetype;
    float speed;
    float distance;
    int im_time;
    int Ncycles;
    int steps_rev;
    int counter;
    bool go;
    //AGGIUNGERE FUNZIONI DI MOVIMENTO
    /*
     * move();
     */
};



#endif
