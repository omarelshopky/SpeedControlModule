/**
 * @file init_test.c
 * @brief Testing initialize process
 * @details Here we apply Unit Test using Unity Test-Harness on init funcions in switch and speedcontrol
 *
 */

 /*    Include Unity    */
#include "../unity/unity_fixture.h"

/*    Include Modules under test    */
#include "../fake_switch/fake_switch.h"
#include "../../source/speedcontrol/speedcontrol.h"

/* Helper Variable in Out of Bounds Tests */
static SwitchState_t Expected_State;

/** @brief Define (INIT) test group */
TEST_GROUP(INIT);

/** @brief Steps are executed before each test */
TEST_SETUP(INIT){

}

/** @brief Steps are executed after each test */
TEST_TEAR_DOWN(INIT){
    FakeSW_Destroy();
}


/*----------------Helper Functions---------------*/


/** @brief  Check Released State after init
 * @param TARGET SwitchType_t Test target Switch
 * @return void
 */
static void ReleasedAfterInit(Switch_t TARGET){
    FakeSW_Init(TARGET);
    LONGS_EQUAL(RELEASED, Get_FakeSW_State(TARGET));
}

/** @brief Set +ve, -ve & P switches to an specific State
 * @param STATE SwitchState_t State to be
 * @return void
 */
static void SetAllSwitches(SwitchState_t STATE){
    Set_FakeSW_State(POSTIVE, STATE);
    Set_FakeSW_State(NEGATIVE, STATE);
    Set_FakeSW_State(P, STATE);
}

/** @brief Check States of +ve, -ve & P switches
 * @param STATE SwitchState_t State to be checked
 * @return void
 */
static void CheckAllSwitches(SwitchState_t STATE){
    LONGS_EQUAL(STATE, Get_FakeSW_State(POSTIVE));
    LONGS_EQUAL(STATE, Get_FakeSW_State(NEGATIVE));
    LONGS_EQUAL(STATE, Get_FakeSW_State(P));
}

/*------------------Test Cases------------------*/

/** <b> Test Description : </b> +ve Switch State is Released after Initialization <br>
  * <b> Test Technique: </b> Equivalence partitioning */
TEST(INIT, PostiveSwitchIsReleasedAfterInit){
    /*!
		  * @par Given : +ve Switch State is unknown
		  * @par When  : FakeSW_Init() is called
		  * @par Then  : +ve Switch State is RELEASED
	*/
    ReleasedAfterInit(POSTIVE);
}


/** <b> Test Description : </b> -ve Switch State is Released after Initialization <br>
 *  <b> Test Technique: </b> Equivalence partitioning */
TEST(INIT, NegativeSwitchIsReleasedAfterInit){
    /*!
		  * @par Given : -ve Switch State is unknown
		  * @par When  : FakeSW_Init() is called
		  * @par Then  : -ve Switch State is RELEASED
	*/
    ReleasedAfterInit(NEGATIVE);
}


/** <b> Test Description : </b> P Switch State is Released after Initialization <br>
 *  <b> Test Technique: </b> Equivalence partitioning */
TEST(INIT, PSwitchIsReleasedAfterInit){
    /*!
		  * @par Given : P Switch State is unknown
		  * @par When  : FakeSW_Init() is called
		  * @par Then  : P Switch State is RELEASED
	*/
    ReleasedAfterInit(P);
}


/** <b> Test Description : </b> +ve, -ve & P State dont't change if input switch was -1 (Max from Left) <br>
 *  <b> Test Technique: </b> Boundary Value Analysis */
TEST(INIT, SwitchOutofBoundsMaxFromLeftDoesNotAffect){
    /*!
		  * @par Given : +ve, -ve & P Switch Set State to PREPRESSED
		  * @par When  : FakeSW_Init() is called with parameter -1
		  * @par Then  : +ve, -ve & P Switch State are PREPRESSED
	*/
	// Assign State to switches to check if there affected or not
	Expected_State = PREPRESSED;
	/* Arrange */
    SetAllSwitches(Expected_State);

    /* Act */
    FakeSW_Init(-1);

    /* Assert */
    CheckAllSwitches(Expected_State);
}


/** <b> Test Description : </b> +ve, -ve & P State dont't change if input switch was -50,000,000 (med from Left) <br>
 *  <b> Test Technique: </b> Boundary Value Analysis */
TEST(INIT, SwitchOutofBoundsMedFromLeftDoesNotAffect){
    /*!
		  * @par Given : +ve, -ve & P Switch Set State to PREPRESSED
		  * @par When  : FakeSW_Init() is called with parameter -50,000,000
		  * @par Then  : +ve, -ve & P Switch State are PREPRESSED
	*/
	// Assign State to switches to check if there affected or not
	Expected_State = PREPRESSED;
	/* Arrange */
    SetAllSwitches(Expected_State);

    /* Act */
    FakeSW_Init(-50000000);

    /* Assert */
    CheckAllSwitches(Expected_State);
}


/** <b> Test Description : </b> +ve, -ve & P State dont't change if input switch was -100,000,000 (min from Left) <br>
 *  <b> Test Technique: </b> Boundary Value Analysis */
TEST(INIT, SwitchOutofBoundsMinFromLeftDoesNotAffect){
    /*!
		  * @par Given : +ve, -ve & P Switch Set State to PREPRESSED
		  * @par When  : FakeSW_Init() is called with parameter -100,000,000
		  * @par Then  : +ve, -ve & P Switch State are PREPRESSED
	*/
	// Assign State to switches to check if there affected or not
	Expected_State = PREPRESSED;
	/* Arrange */
    SetAllSwitches(Expected_State);

    /* Act */
    FakeSW_Init(-100000000);

    /* Assert */
    CheckAllSwitches(Expected_State);
}


/** <b> Test Description : </b> +ve, -ve & P State dont't change if input switch was 3 (Min from Right) <br>
 *  <b> Test Technique: </b> Boundary Value Analysis */
TEST(INIT, SwitchOutofBoundsMinFromRightDoesNotAffect){
    /*!
		  * @par Given : +ve, -ve & P Switch Set State to PREPRESSED
		  * @par When  : FakeSW_Init() is called with parameter 3
		  * @par Then  : +ve, -ve & P Switch State are PREPRESSED
	*/
	// Assign State to switches to check if there affected or not
	Expected_State = PREPRESSED;
	/* Arrange */
    SetAllSwitches(Expected_State);

    /* Act */
    FakeSW_Init(3);

    /* Assert */
    CheckAllSwitches(Expected_State);
}


/** <b> Test Description : </b> +ve, -ve & P State dont't change if input switch was 50,000,001 (Med from Right) <br>
 *  <b> Test Technique: </b> Boundary Value Analysis */
TEST(INIT, SwitchOutofBoundsMedFromRightDoesNotAffect){
    /*!
		  * @par Given : +ve, -ve & P Switch Set State to PREPRESSED
		  * @par When  : FakeSW_Init() is called with parameter 50,000,001
		  * @par Then  : +ve, -ve & P Switch State are PREPRESSED
	*/
	// Assign State to switches to check if there affected or not
	Expected_State = PREPRESSED;
	/* Arrange */
    SetAllSwitches(Expected_State);

    /* Act */
    FakeSW_Init(50000001);

    /* Assert */
    CheckAllSwitches(Expected_State);
}


/** <b> Test Description : </b> +ve, -ve & P State dont't change if input switch was 100,000,000 (Max from Right) <br>
 *  <b> Test Technique: </b> Boundary Value Analysis */
TEST(INIT, SwitchOutofBoundsMaxFromRightDoesNotAffect){
    /*!
		  * @par Given : +ve, -ve & P Switch Set State to PREPRESSED
		  * @par When  : FakeSW_Init() is called with parameter 100,000,000
		  * @par Then  : +ve, -ve & P Switch State are PREPRESSED
	*/
	// Assign State to switches to check if there affected or not
	Expected_State = PREPRESSED;
	/* Arrange */
    SetAllSwitches(Expected_State);

    /* Act */
    FakeSW_Init(100000000);

    /* Assert */
    CheckAllSwitches(Expected_State);
}


/** <b> Test Description : </b> Check Motor Default speed is Meduim (Motor Angle = 90 Degrees) at begin **/
TEST(INIT, DefaultSpeedIsMedium){
    /*!
		  * @par Given : Motor Speed is unknown (Motor Angle is unknown)
		  * @par When  : Speed_Init() is called
		  * @par Then  : Motor Speed is MED (Motor Angle is 90)
	*/
    /* Act */
    Speed_Init();

    /* Assert */
    LONGS_EQUAL(90, MotAngle_Write());
}


/** @brief Tests Runner */
TEST_GROUP_RUNNER(INIT){
    // EP Test Cases
    RUN_TEST_CASE(INIT, PostiveSwitchIsReleasedAfterInit);
    RUN_TEST_CASE(INIT, NegativeSwitchIsReleasedAfterInit);
    RUN_TEST_CASE(INIT, PSwitchIsReleasedAfterInit);

    // BVA Test Cases
    RUN_TEST_CASE(INIT, SwitchOutofBoundsMaxFromLeftDoesNotAffect);
    RUN_TEST_CASE(INIT, SwitchOutofBoundsMedFromLeftDoesNotAffect);
    RUN_TEST_CASE(INIT, SwitchOutofBoundsMinFromLeftDoesNotAffect);
    RUN_TEST_CASE(INIT, SwitchOutofBoundsMinFromRightDoesNotAffect);
    RUN_TEST_CASE(INIT, SwitchOutofBoundsMedFromRightDoesNotAffect);
    RUN_TEST_CASE(INIT, SwitchOutofBoundsMaxFromRightDoesNotAffect);

    // Motor
    RUN_TEST_CASE(INIT, DefaultSpeedIsMedium);
}
