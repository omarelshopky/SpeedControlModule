/**
 * @file set_test.c
 * @brief Testing Set State process
 * @details Here we apply Unit Test using Unity Test-Harness on Set funcions in switch and speedcontrol
 *
 */

 /*    Include Unity    */
#include "../unity/unity_fixture.h"

/*    Include Modules under test    */
#include "../fake_switch/fake_switch.h"

/** @brief Define (SET) test group */
TEST_GROUP(SET);

/** @brief Steps are executed before each test */
TEST_SETUP(SET){

}

/** @brief Steps are executed after each test */
TEST_TEAR_DOWN(SET){
    FakeSW_Destroy();
}

/** @brief  Check Set Switch State
 * @param TARGET Switch_t Test target Switch
 * @param STATE SwitchState_t Test State
 * @return void
 */
static void SetSWState(Switch_t TARGET, SwitchState_t STATE){
    Set_FakeSW_State(TARGET, STATE);
    LONGS_EQUAL(STATE, Get_FakeSW_State(TARGET));
}


/*------------------Test Cases------------------*/


/** <b> Test Description : </b> Set Postive Switch State**/
TEST(SET, SetPostiveSWState){
    /*!
		  * @par Given : Postive Switch State is RELEASED
		  * @par When  : Switch State is set to PREPRESSED
		  * @par Then  : PostiveSwitch State is PREPRESSED
	*/
    SetSWState(POSTIVE, PREPRESSED);
}


/** <b> Test Description : </b> Set Negative Switch State**/
TEST(SET, SetNegativeSWState){
    /*!
		  * @par Given : Negative Switch State is RELEASED
		  * @par When  : Switch State is set to PREPRESSED
		  * @par Then  : Negative State is PREPRESSED
	*/
    SetSWState(NEGATIVE, PREPRESSED);
}


/** <b> Test Description : </b> Set P Switch State**/
TEST(SET, SetPSWState){
    /*!
		  * @par Given : P Switch State is RELEASED
		  * @par When  : Switch State is set to PRESSED
		  * @par Then  : Negative State is PRESSED
	*/
    SetSWState(P, PRESSED);
}


/** <b> Test Description : </b> Set press Time for Switch **/
TEST(SET, SetSwitchPressTime){
    /*!
		  * @par Given : Switch's Press Time is unknown
		  * @par When  : Press Time is set to 30 ms
		  * @par Then  : Switch's Press Time is 30 ms
	*/
    /* Act */
    Set_FakeSW_PressTime(30);

    /* Assert */
    LONGS_EQUAL(30, Get_FakeSW_PressTime());
}



/** @brief Tests Runner */
TEST_GROUP_RUNNER(SET){
    RUN_TEST_CASE(SET, SetPostiveSWState);
    RUN_TEST_CASE(SET, SetNegativeSWState);
    RUN_TEST_CASE(SET, SetPSWState);
    RUN_TEST_CASE(SET, SetSwitchPressTime);
}
