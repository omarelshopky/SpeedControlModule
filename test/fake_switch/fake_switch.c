/**
 * @file fake_switch.c
 * @brief Fake Switch main file
 * @details Here we Simulate Switch so we can Test it and give it any statues
 *
 */

#include <stdbool.h>

 /*    Include Header    */
#include"fake_switch.h"

/** @brief A variables with SwichState_t type store Switches State */
static SwitchState_t POSTIVE_SWITCH_STATE;
static SwitchState_t NEGATIVE_SWITCH_STATE;
static SwitchState_t P_SWITCH_STATE;

/** @brief A variable to store Press Time for switch */
unsigned char PRESS_TIME;

/** @brief Check Whether Switch value Out of Bounds or not
 * @param SW Switch_t Tested Value
 * @return bool true if Switch value Out of Bounds & False if not
 */
bool IsOutOfBounds(Switch_t SW){
    return (SW < 0) || (SW > 2);
}

void Set_FakeSW_State(Switch_t SW, SwitchState_t STATE){
    switch(SW){
    case POSTIVE:
        POSTIVE_SWITCH_STATE =  STATE;
        break;
    case NEGATIVE:
        NEGATIVE_SWITCH_STATE = STATE;
        break;
    case P:
        P_SWITCH_STATE = STATE;
        break;
    default:
        break;
    }
}


SwitchState_t Get_FakeSW_State(Switch_t SW){
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


void FakeSW_Init(Switch_t SW){
    if(IsOutOfBounds(SW)){
        return;

    }else{
        switch(SW){
        case POSTIVE:
            POSTIVE_SWITCH_STATE =  RELEASED;
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


void Set_FakeSW_PressTime(unsigned char TIME){
    PRESS_TIME = TIME;
}


unsigned char Get_FakeSW_PressTime(void){
    return PRESS_TIME;
}


void FakeSW_Destroy(){
    FakeSW_Init(POSTIVE);
    FakeSW_Init(NEGATIVE);
    FakeSW_Init(P);
    Set_FakeSW_PressTime(0);
}
