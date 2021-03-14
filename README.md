# Challenge: Vacuum Cleaner Speed Control
## Description
**Develop the “speed control” module such that:**
  * The design follows a time triggered approach
  * Design is implemented using test driven development approach
  * Used test design techniques are :
    * Equivalence partitioning
    * Boundary value analysis
    * State transition testing up to 1 switch coverage

## Specifications
  * There are 3 speeds: minimum, medium and maximum speeds
  * Default speed = medium
  * There are 3 switches that can control the speed: “+ ve ”, ve ” and “
  * If “+ ve ” switch is pre pressed, speed increases by 1 step if speed != maximum
  * If “ ve ” switch is pre pressed, speed decreases by 1 step if speed != minimum
  * If “p” switch is pressed for 30 seconds, speed decreases by 1 step if speed != minimum
  * Priority of switches is:
    1. “p” switch
    2. "-ve" switch
    3. "+ve" switch

## Motor Angles Specifications
  * The speed control sets the motor angle according to the speed
    * Minimum speed --> 140 degrees
    * Medium speed --> 90 degrees
    * Maximum speed --> 10 degrees

## Tools
  * Code::Blocks v20.03
  * Unity C Test Harness
  * Doxygen Documentation Generator

## How to Simulate HW on PC?
  * A text file will simulate the switches data [(switch.txt)]()
  * Another text file will store the set motor angle [(motor.txt)]()
  * Both files inside the project folder structure
  * Every line correspond to a test case
