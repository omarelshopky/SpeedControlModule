/**
 * @file switch.h
 * @brief Switch Header file
 *
 */

#ifndef SWITCH_H_INCLUDED
#define SWITCH_H_INCLUDED

/** @brief A variable can assign the four States of Switch */
typedef enum {PREPRESSED, PRESSED, PRERELEASED, RELEASED} SwitchState_t;

/** @brief A variable can assign three types of Switches */
typedef enum {POSTIVE, NEGATIVE, P} Switch_t;



/** @brief Get Current State of Specific Switch
 * @param SW Switch_t Which Switch to apply this function on
 * @return SwitchState_t The State of intended switch
 */
SwitchState_t Get_RealSW_State(Switch_t SW);


/** @brief Initialize Switch State to Released before begin
 * @param SW Switch_t Which Switch to initialize
 * @return void
 */
void SW_Init(Switch_t SW);


/** @brief Get Press Time of P Switch
 * @param void
 * @return unsigned char The Press Time of P Switch
 */
unsigned char Get_RealSW_PressTime(void);


/** @brief Pointer to Get Switch State Functions
 */
extern SwitchState_t   (*Get_SWState)(Switch_t SW);


/** @brief Pointer to Get Switch State Functions
 */
extern unsigned char   (*Get_PressTime)(void);


void Update_Switch(Switch_t SW);

#endif // SWITCH_H_INCLUDED
