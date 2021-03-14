/**
 * @file update_test.c
 * @brief Testing Update Data & State process
 * @details Here we apply Unit Test using Unity Test-Harness on update funcions in switch and speedcontrol
 *
 */

#include <stdio.h>
#include <string.h>

 /*    Include Unity    */
#include "../unity/unity_fixture.h"

/*    Include Modules under test    */
#include "../fake_switch/fake_switch.h"
#include "../../source/speedcontrol/speedcontrol.h"
#include "../../source/switches/switch.h"

/* Helper function to read TestData */
static unsigned char Get_TestData(SwitchState_t* Postive_State, SwitchState_t* Negative_State, SwitchState_t* P_State, unsigned char* P_PressTime, unsigned char TestLine);

static void Arrange_TestData(SwitchState_t Postive_State, SwitchState_t Negative_State, SwitchState_t P_State, unsigned char P_PressTime);

static void Write_TestResult(unsigned char MotorAngle, unsigned char TestNum);

static void Check_TestCase(unsigned char TestCaseNum, unsigned char TestLine, unsigned char* TestsCounter);

/** @brief Define (UPDATE) test group */
TEST_GROUP(UPDATE);

/** @brief Steps are executed before each test */
TEST_SETUP(UPDATE){
    FakeSW_Init(POSTIVE);
    FakeSW_Init(NEGATIVE);
    FakeSW_Init(P);
    Speed_Init();
    UT_PTR_SET(Get_SWState, Get_FakeSW_State);
    UT_PTR_SET(Get_PressTime, Get_FakeSW_PressTime);
}

/** @brief Steps are executed after each test */
TEST_TEAR_DOWN(UPDATE){

}



/*------------------Test Cases------------------*/


/** **Test Description :** Speed Increase from Medium to Maximum (Motor Angle = 10 Degrees) by Speed_Increase function */
TEST(UPDATE, SpeedIncreaseFromMedToMax){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90)
		  * @par When  : Speed_Increase() is called
		  * @par Then  : Motor Speed Increase to MAX (Motor Angle is 10)
	*/

    /* Act */
    Speed_Increase();

    /* Assert */
    LONGS_EQUAL(10, MotAngle_Write());
}


/** **Test Description :** Speed Decrease from Medium to Minimum (Motor Angle = 140 Degrees) by Speed_Decrease function */
TEST(UPDATE, SpeedDecreaseFromMedToMin){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90)
		  * @par When  : Speed_Decrease() is called
		  * @par Then  : Motor Speed Decrease to MID (Motor Angle is 140)
	*/

    /* Act */
    Speed_Decrease();

    /* Assert */
    LONGS_EQUAL(140, MotAngle_Write());
}


/** **Test Description :** If +ve Switch Prepressed, Speed Increase from Medium to Maximum (Motor Angle = 10 Degrees) */
TEST(UPDATE, SpeedIncreaseAfterPrepressedPostiveSwitch){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90)
		  * @par When  : Speed_Update() is called while +ve Switch State is PREPRESSED
		  * @par Then  : Motor Speed Increase to MAX (Motor Angle is 10)
	*/
	/* Arrange */
    Set_FakeSW_State(POSTIVE, PREPRESSED);

    /* Act */
    Speed_Update();

    /* Assert */
    LONGS_EQUAL(10, MotAngle_Write());
}

/** **Test Description :** If -ve Switch Prepressed, Speed Decrease from Medium to Minimum (Motor Angle = 140 Degrees) */
TEST(UPDATE, SpeedDecreaseAfterPrepressedNegativeSwitch){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90)
		  * @par When  : Speed_Update() is called while -ve Switch State is PREPRESSED
		  * @par Then  : Motor Speed Increase to MIN (Motor Angle is 140)
	*/
	/* Arrange */
    Set_FakeSW_State(NEGATIVE, PREPRESSED);
    Speed_Init();

    /* Act */
    Speed_Update();

    /* Assert */
    LONGS_EQUAL(140, MotAngle_Write());
}


/** **Test Description :** If P Switch pressed for 30 secoonds, Speed Decrease from Medium to Minimum (Motor Angle = 140 Degrees) */
TEST(UPDATE, SpeedDecreaseAfterPrepressedPSwitch){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90)
		  * @par When  : Speed_Update() is called while P Switch State is PRESSED for 30 seconds
		  * @par Then  : Motor Speed Increase to MIN (Motor Angle is 140)
	*/
	/* Arrange */
    Set_FakeSW_State(P, PRESSED);
    Set_FakeSW_PressTime(30);

    /* Act */
    Speed_Update();

    /* Assert */
    LONGS_EQUAL(140, MotAngle_Write());
}


/** **Test Description :** Speed Change From Med (Default Speed) To Max (when +ve Switch PrePressed) *
 * Remain Max (When +ve Switch PrePressed) Then to Med (when -ve Switch PrePressed) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMaxRemainMaxThenToMed){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (+ve -> +ve -> -ve)
		  * @par Then  : Motor Speed is MED (Motor Angle is 90)
	*/
	unsigned char TestCase_Num = 1;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 90; /* Speed: MED */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Max (+ve Switch PrePressed) *
 * Remain Max (When +ve Switch PrePressed due)  <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMaxThenRemainMaxDue){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (+ve -> +ve -> +ve)
		  * @par Then  : Motor Speed is MAX (Motor Angle is 10)
	*/
	unsigned char TestCase_Num = 2;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 10; /* Speed: MAX */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}

/** **Test Description :** Speed Change From Med (Default Speed) To Max (+ve Switch PrePressed) *
 * Return to Med State (When P Switch Pressed 30s) then to Max (+ve Switch PrePressed) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMaxReturnMedThenMax){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (+ve -> P -> +ve)
		  * @par Then  : Motor Speed is MAX (Motor Angle is 10)
	*/
	unsigned char TestCase_Num = 3;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 10; /* Speed: MAX */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Max (+ve Switch PrePressed) *
 * Return to Med State (-ve Switch PrePressed) then to Min (When P Switch Pressed 30s) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMaxReturnMedThenMin){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (+ve -> -ve -> P)
		  * @par Then  : Motor Speed is MIN (Motor Angle is 140)
	*/
	unsigned char TestCase_Num = 4;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 140; /* Speed: MIN */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Min (When P Switch Pressed 30s) *
 * Remain Min (-ve Switch PrePressed) then to Med (When +ve Switch PrePressed) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMinRemainMinThenMed){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (P -> -ve -> +ve)
		  * @par Then  : Motor Speed is MED (Motor Angle is 90)
	*/
	unsigned char TestCase_Num = 5;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 90; /* Speed: MED */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Min (When -ve Switch PrePressed) *
 * Remain Min (-ve Switch PrePressed then P Switch Pressed 30s)<br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMinRemainMinDue){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (-ve -> -ve -> P)
		  * @par Then  : Motor Speed is MIN (Motor Angle is 140)
	*/
	unsigned char TestCase_Num = 6;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 140; /* Speed: MIN */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Min (When P Switch Pressed 30s) *
 * Return to Med (+ve Switch PrePressed) then to Max (+ve Switch PrePressed) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMinReturnMedThenMax){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (P -> +ve -> +ve)
		  * @par Then  : Motor Speed is MAX (Motor Angle is 10)
	*/
	unsigned char TestCase_Num = 7;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 10; /* Speed: MAX */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Min (When -ve Switch PrePressed ) *
 * Return to Med (+ve Switch PrePressed) then to Min (When P Switch Pressed 30s) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMedToMinReturnMedThenMin){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (-ve -> +ve -> P)
		  * @par Then  : Motor Speed is MIN (Motor Angle is 140)
	*/
	unsigned char TestCase_Num = 8;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 140; /* Speed: MIN */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** **Test Description :** Speed Change From Med (Default Speed) To Min (When -ve Switch PrePressed ) *
 * Return to Med NOT to Max (when +ve Switch PrePressed) <br>
 *  **Test Technique:** State Transition Testing up to 1 switch coverage */
TEST(UPDATE, SpeedChangeFromMinToMaxInOneStepIsInvalid){
    /*!
		  * @par Given : Motor Speed is MED (Motor Angle is 90) as Defualt
		  * @par When  : Speed_Update() is called while Switches State change according to Test Data (-ve -> +ve)
		  * @par Then  : Motor Speed is MED (Motor Angle is 140)
	*/
	unsigned char TestCase_Num = 9;

	/* Arrange & Act */
	unsigned char TestLine = 1, TestsCounter = 0;
	while(TestsCounter != TestCase_Num){
        Check_TestCase(TestCase_Num, TestLine, &TestsCounter);
        TestLine++;
	}

    /* Motor Angle */
    unsigned char Expected_Angle = 90; /* Speed: MED */
    unsigned char Real_Angle = MotAngle_Write();

    /* Write Result */
    Write_TestResult(Real_Angle, TestCase_Num);

    /* Assert */
    LONGS_EQUAL(Expected_Angle, Real_Angle);
}


/** @brief Tests Runner */
TEST_GROUP_RUNNER(UPDATE){
    RUN_TEST_CASE(UPDATE, SpeedIncreaseFromMedToMax);
    RUN_TEST_CASE(UPDATE, SpeedDecreaseFromMedToMin);
    RUN_TEST_CASE(UPDATE, SpeedIncreaseAfterPrepressedPostiveSwitch);
    RUN_TEST_CASE(UPDATE, SpeedDecreaseAfterPrepressedNegativeSwitch);
    RUN_TEST_CASE(UPDATE, SpeedDecreaseAfterPrepressedPSwitch);

    /* State Transition Testing up to 1 switch coverage */
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMaxRemainMaxThenToMed);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMaxThenRemainMaxDue);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMaxReturnMedThenMax);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMaxReturnMedThenMin);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMinRemainMinThenMed);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMinRemainMinDue);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMinReturnMedThenMax);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMedToMinReturnMedThenMin);
    RUN_TEST_CASE(UPDATE, SpeedChangeFromMinToMaxInOneStepIsInvalid);

}


/** @brief This function has multi tasks: it get Required Test Case by count how many test cases has finished
 * Return Speed to default before every Test Case and Get and Arrange each Test Line.
 * @param TestCaseNum unsigned char Number of current Test Case
 * @param TestLine unsigned char Number of Test Line to Get and Arrange
 * @param TestsCounter unsigned char* how many test case had read
 * @return void
 */
static void Check_TestCase(unsigned char TestCaseNum, unsigned char TestLine, unsigned char* TestsCounter){
    //Test Data
	SwitchState_t Postive_State, Negative_State, P_State;
	unsigned char P_PressTime;

    /* End of Test Case */
    if(Get_TestData(&Postive_State, &Negative_State, &P_State, &P_PressTime, TestLine) == 2){

        *TestsCounter += 1;

        /* Check if there are other test cases (Srart from default) or it is what we want */
        if(*TestsCounter != TestCaseNum){
            Speed_Init();
        }else{

        }

    /* Correct Data */
    }else if(Get_TestData(&Postive_State, &Negative_State, &P_State, &P_PressTime, TestLine) == 0){
            Arrange_TestData(Postive_State,Negative_State, P_State, P_PressTime);

    }else{

    }

}


/** @brief Get TestData from switch.txt file to use it in Tests
 * @param Postive_State SwitchState_t* Current +ve Switch State
 * @param Negative_State SwitchState_t* +ve Switch State
 * @param P_State SwitchState_t* Current p Switch State
 * @param P_PressTime unsigned char* Current P Press Time
 * @param TestLine unsigned char Number of current Test Line
 * @return unsigned char 0 if Data is Correct, 2 implies End of Test Case and 1 if Data is incorrect
 */
static unsigned char Get_TestData(SwitchState_t* Postive_State, SwitchState_t* Negative_State, SwitchState_t* P_State, unsigned char* P_PressTime, unsigned char TestLine){
    FILE* data = fopen("switch.txt", "r+");
//
    char str1[20];
    char str2[20];
    char str3[20];
    char str4[10];
    unsigned char time;
    if(data){

        // Get Data
        unsigned char i;
        for(i = 0; i < TestLine; i++){

            memset(str1,0,20);
            memset(str2,0,20);
            memset(str3,0,20);
            memset(str4,0,10);

            fscanf(data, "%s\t%s\t%s\t%s\n",str1, str2, str3, str4);

            time = atoi(str4);
        }

        // Check if Data is Correct or not
        if(strcmp(str1, "PRE_PRESSED") == 0){
            *Postive_State = PREPRESSED;

        }else if(strcmp(str1, "PRESSED") == 0){
            *Postive_State = PRESSED;

        }else if(strcmp(str1, "PRE_RELEASED") == 0){
            *Postive_State = PRERELEASED;

        }else if(strcmp(str1, "RELEASED") == 0){
            *Postive_State = RELEASED;

        }else if(strcmp(str1, "-") == 0){
            return 2;

        }else{
            printf("Incorrect TestData\n");
            return 1;
        }

        if(strcmp(str2, "PRE_PRESSED") == 0){
            *Negative_State = PREPRESSED;

        }else if(strcmp(str2, "PRESSED") == 0){
            *Negative_State = PRESSED;

        }else if(strcmp(str2, "PRE_RELEASED") == 0){
            *Negative_State = PRERELEASED;

        }else if(strcmp(str2, "RELEASED") == 0){
            *Negative_State = RELEASED;

        }else{
            printf("Incorrect TestData\n");
            return 1;
        }

        if(strcmp(str3, "PRE_PRESSED") == 0){
            *P_State = PREPRESSED;

        }else if(strcmp(str3, "PRESSED") == 0){
            *P_State = PRESSED;

        }else if(strcmp(str3, "PRE_RELEASED") == 0){
            *P_State = PRERELEASED;

        }else if(strcmp(str3, "RELEASED") == 0){
            *P_State = RELEASED;

        }else{
            printf("Incorrect TestData\n");
            return 1;
        }


        if(time >= 0){
            *P_PressTime = time;

        }else{
            printf("Incorrect TestData\n");
            return 1;
        }

        fclose(data);

    }else{

        printf("Failed To open TestData file\n");
        return 1;
    }
    return 0;
}


/** @brief Arrange Data from Get_TestData() and apply it into Fake Switch module to see result
 * @param Postive_State SwitchState_t +ve Switch State
 * @param Negative_State SwitchState_t -ve Switch State
 * @param P_State SwitchState_t P Switch State
 * @param P_PressTime unsigned char P Press Time
 * @return void
 */
static void Arrange_TestData(SwitchState_t Postive_State, SwitchState_t Negative_State, SwitchState_t P_State, unsigned char P_PressTime){

    Set_FakeSW_State(POSTIVE, Postive_State);

    Set_FakeSW_State(NEGATIVE, Negative_State);

    Set_FakeSW_State(P, P_State);

    Set_FakeSW_PressTime(P_PressTime);

    Speed_Update();
}


/** @brief Write Test Data Result (Motor Angle) in motor.txt
 * @param MotorAngle unsigned char Motor Angle Result from Test Data
 * @param TestNum Number of current Test Case
 * @return void
 */
static void Write_TestResult(unsigned char MotorAngle, unsigned char TestNum){
    FILE* result = fopen("motor.txt", "r");
    FILE* Temp = fopen("Temp.tmp", "w");

    char str[12];

    if(result && Temp){
        unsigned char i;

        for(i = 1; i <= TestNum; i++){
            memset(str, 0, 12);
            fscanf(result, "%s\n", str);
            fprintf(Temp, "%s\n", str);

        }

        fprintf(Temp, "%hhu\n", MotorAngle);
    }else{
        printf("Failed To open Result file\n");

    }


    fclose(result);
    fclose(Temp);

    remove("motor.txt");

    rename("Temp.tmp", "motor.txt");
}
