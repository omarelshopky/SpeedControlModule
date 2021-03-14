/**
 * @file speedcontrol.c
 * @brief Speedcontrol Main file
 * @details Here we get change in speed from switches, then convert it into degrees and write it on motor
 *
 */


  /*    Include Header    */
#include"speedcontrol.h"

  /*    Include Modules    */
#include"../../test/fake_switch/fake_switch.h"

/** @brief a variables with MotorSpeed_t type store current Motor Speed */
static MotorSpeed_t MOT_SPEED;


void Speed_Init(){

    MOT_SPEED = MED;
 }


short MotAngle_Write(){

    if (MOT_SPEED == MIN){
        return 140;

    }else if (MOT_SPEED == MED){
        return 90;

    }else if (MOT_SPEED == MAX){
        return 10;

    }else{

    }
 }


 void Speed_Increase(){
    if (MOT_SPEED == MIN){
        MOT_SPEED = MED;

    }else if (MOT_SPEED == MED){
        MOT_SPEED = MAX;

    }else {

    }
 }

 void Speed_Decrease(){
    if (MOT_SPEED == MAX){
        MOT_SPEED = MED;

    }else if (MOT_SPEED == MED){
        MOT_SPEED = MIN;

    }else {

    }
 }


 void Speed_Update(){

    if (Get_FakeSW_State(P) == PRESSED && Get_FakeSW_PressTime() >= 30){
        Speed_Decrease();

    }

    if (Get_FakeSW_State(NEGATIVE) == PREPRESSED){
        Speed_Decrease();

    }

    if (Get_FakeSW_State(POSTIVE) == PREPRESSED){
        Speed_Increase();

    }
 }
