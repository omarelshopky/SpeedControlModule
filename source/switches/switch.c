/**
 * @file switch.c
 * @brief Switch main file
 *
 */

#include <stdbool.h>

 /*    Include Header    */
#include"switch.h"


/** @brief A variables with SwichState_t type store Switches State */
static SwitchState_t POSTIVE_SWITCH_STATE;
static SwitchState_t NEGATIVE_SWITCH_STATE;
static SwitchState_t P_SWITCH_STATE;

/** @brief A variable to store Press Time for switch */
unsigned char PRESS_TIME;



SwitchState_t   (*Get_SWState)(Switch_t SW);

unsigned char   (*Get_PressTime)(void);




SwitchState_t Get_RealSW_State(Switch_t SW){
    switch(SW){
    case POSTIVE:
        return POSTIVE_SWITCH_STATE;
        break;
    case NEGATIVE:
        return NEGATIVE_SWITCH_STATE;
        break;
    case P:
        return P_SWITCH_STATE;
        break;
    default:
        break;
    }
}


void SW_Init(Switch_t SW){
    if(IsOutOfBounds(SW)){
        return;

    }else{
        Get_SWState = Get_RealSW_State;
        Get_PressTime = Get_RealSW_PressTime;
        switch(SW){
        case POSTIVE:
            POSTIVE_SWITCH_STATE = RELEASED;
            break;
        case NEGATIVE:
            NEGATIVE_SWITCH_STATE = RELEASED;
            break;
        case P:
            P_SWITCH_STATE = RELEASED;
            break;
        default:
            break;
        }
    }
}


unsigned char Get_RealSW_PressTime(void){
    return PRESS_TIME;
}


void Update_Switch(Switch_t SW){


}

