/**
 * @file fake_switch.h
 * @brief Fake Switch header file
 */

#ifndef FAKE_SWITCH_H_INCLUDED
#define FAKE_SWITCH_H_INCLUDED

#include"../../source/switches/switch.h"



/** @brief Set State to Specific Switch
 * @param SW Switch_t Which Switch to apply this function on
 * @param STATE SwitchState_t The intended State
 * @return void
 */
void Set_FakeSW_State(Switch_t SW, SwitchState_t STATE);


/** @brief Get Current State of Specific Switch
 * @param SW Switch_t Which Switch to apply this function on
 * @return SwitchState_t The State of intended switch
 */
SwitchState_t Get_FakeSW_State(Switch_t SW);


/** @brief Initialize Switch State to Released before begin
 * @param SW Switch_t Which Switch to initialize
 * @return void
 */
void FakeSW_Init(Switch_t SW);


/** @brief Set Press Time for Switch
 * @param TIME int press time in ms
 * @return void
 */
void Set_FakeSW_PressTime(unsigned char TIME);


/** @brief Get Press Time of P Switch
 * @param void
 * @return unsigned char The Press Time of P Switch
 */
unsigned char Get_FakeSW_PressTime(void);


/** @brief Initialize everything again
 * @param void
 * @return void
 */
void FakeSW_Destroy(void);

#endif // FAKE_SWITCH_H_INCLUDED
