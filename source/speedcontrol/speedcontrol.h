/**
 * @file speedcontrol.h
 * @brief Speedcontrol header file
 */

#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED


/** @brief A variable can assign the three States of Motor Speed */
typedef enum {MIN, MED, MAX} MotorSpeed_t;


/** @brief Set Motor Default Speed to MED
 * @param void
 * @return void
 */
void Speed_Init(void);


/** @brief Write Current Speed State on the Motor as Degrees <br>
 * if Speed: MIN --> Angle = 140                             <br>
 * if Speed: MED --> Angle = 90                              <br>
 * if Speed: MAX --> Angle = 10
 * @param void
 * @return unsigned char current Motor Angle According to Speed State
 */
short MotAngle_Write(void);


/** @brief Increase Motor Speed as follow: <br>
 * MIN -> MED
 * MED -> MAX
 * @param void
 * @return void
 */
void Speed_Increase(void);


/** @brief Decrease Motor Speed as follow: <br>
 * MAX -> MED
 * MED -> MIN
 * @param void
 * @return void
 */
void Speed_Decrease(void);


/** @brief Update Motor Speed according to Switches States with priority
 * P Switch then, -ve Switch then, +ve Switch
 * @param void
 * @return void
 */
void Speed_Update(void);

#endif // MOTOR_H_INCLUDED
