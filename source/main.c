/**
 * @file main.c
 * @author Omar Hesham
 * @brief The main file
 * @details Here we call unity test harness to do tests and update switches & speedcontrol  in main()
 *
 */

/*    Include Standard Libraries of input-output stream    */
#include <stdio.h>
#include <stdlib.h>

/*    Include Unity    */
#include "../test/unity/unity_fixture.h"
#define MAKE_UNITY_VERBOSE	argc = 2; argv[1] = "-v"

/*    Include Modules    */
#include "switches/switch.h"
#include "speedcontrol/speedcontrol.h"

/** @brief Test Groups Runner */
static void RunAllTests(void){
    RUN_TEST_GROUP(SET);
    RUN_TEST_GROUP(INIT);
    RUN_TEST_GROUP(UPDATE);
}

/** @brief main function run all Test Groups & SpeedControl Module
 *
 * @param argc int
 * @param argv[] char*
 * @return int 0 if all is fine & 1 if there's an error
 */
int main(int argc, char * argv[])
{
    /*    Make Unity verbose rather than using Command Line    */
    MAKE_UNITY_VERBOSE;

    /*    Call Unity Main    */
    UnityMain(argc, argv, RunAllTests);

    printf("App is Running.....");
    SW_Init(P);
    SW_Init(POSTIVE);
    SW_Init(NEGATIVE);
    Speed_Init();

    while(1){

        Update_Switch(P);
        Update_Switch(POSTIVE);
        Update_Switch(NEGATIVE);

        Speed_Update();
        MotAngle_Write();
    }

    return 0;
}


