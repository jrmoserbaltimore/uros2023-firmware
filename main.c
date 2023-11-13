#pragma config(Motor,  port1,           LeftTread,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Servo1,        tmotorServoStandard, openLoop)
#pragma config(Motor,  port3,           Scoop,         tmotorVex269_MC29, openLoop)
#pragma config(Motor,  port10,          RightTread,    tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "types.h"
#include "inputs.c"
#include "treadcontrols.c"

task main()
{
  JoystickValues js;
  while(true)
  {
    sleep(5);
    getJoystickValues(js);
    // TODO:  if (treadMode) move treads, if (scoopMode) move scoop
    moveTreads(js);
  }
}