///****************************************************************************************************************************
// * Functions:
// * wait(); looks for a button push before putting the bot into motion
// * forward(duration, speed); drive both motors forward for "duration" in ms, at speed (0-255)
// * reverse(duration, speed); drive both motors in reverse for "duration" in ms, at speed (0-255)
// * turnLeft(duration, speed); drive the left motor in reverse, right motor forward for "duration" in ms, and speed (0-255)
// * turnRight(duration, speed); drive the left motor forward, right motor in reverse for "duration" in ms, and speed (0-255)
// * stop(); stops the robot and applies the brakes.  For functions with a duration, this is already applied
// * sonarTurnRight (distance, speed, duration of turn, number of turns) drive forward until the bot reaches distance (inches) 
// * from obstacle, turn right for duration, repeat for indicated number of turns
//
// *************The following functions should be used for testing and debugging **********************************************
// * leftMotorF(speed); drive the left motor forward at speed (0-255); you'll have to implement a stop() function
// * rightMotorF(speed); drive the right motor forward at speed (0-255); you'll have to implement a stop() function
// * leftMotorR(speed); drive the left motor in reverse at speed (0-255); you'll have to implement a stop() function
// * rightMotorR(speed); drive the right motor in reverse at speed (0-255); you'll have to implement a stop() function
// * sonarSerial(); prints the sonar readings on the serial monitor
// *****************************************************************************************************************************
// * Pin Assignments
// * 2 Motor Controller A_EN
// * 3 Motor Controller A_RPWM
// * 4 Motor Controller A_DIS
// * 5 Left Motor Encoder (yellow)
// * 6 Left Motor Encoder (white)
// * 7 Motor Controller B_DIS
// * 8 Motor Controller B_EN
// * 9 Motor Controller B_RPWM
// * 10 Motor Controller B_LPWM
// * 11 Motor Controller A_LPWM
// * 12 Servo
// * 13 Servo
// * 14 
// * 15 Color S0
// * 16 Color S1
// * 17 Color S2
// * 18 Color S3
// * 19 Color OUT
// * 20 SDA
// * 21 SCL
// * 22 Ultrasonic Trigger
// * 23 Ultrasonic Echo
// * 24
// * 52 Wait button (internal pullup)
// * 53 
// * 58  Left Motor Encoder (yellow)
// * 59  Left Motor Encoder (white)


