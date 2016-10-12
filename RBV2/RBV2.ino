
///****************************************************************************************************************************
// * ROBOT SETUP
// * Left motor is attached to Channel A
// * Right motor is attached to Channel B
// * 
// * Functions:
// * wait() looks for a button push before putting the bot into motion
// * leftMotorF(speed) drive the left motor forward at speed (0-255); you'll have to implement a stop() function
// * rightMotorF(speed) drive the right motor forward at speed (0-255); you'll have to implement a stop() function
// * leftMotorR(speed) drive the left motor in reverse at speed (0-255); you'll have to implement a stop() function
// * rightMotorR(speed) drive the right motor in reverse at speed (0-255); you'll have to implement a stop() function
// * forward(duration, speed) drive both motors forward for "duration" in ms, at speed (0-255)
// * reverse(duration, speed) drive both motors in reverse for "duration" in ms, at speed (0-255)
// * turnLeft(duration, speed) drive the left motor in reverse, right motor forward for "duration" in ms, and speed (0-255)
// * turnRight(duration, speed) drive the left motor forward, right motor in reverse for "duration" in ms, and speed (0-255)
// * stop() stops the robot and applies the brakes.  For functions with a duration, this is already applied
// * 
//******************************************************************************************************************************/

//******************************  ENTER YOUR FUNCTIONS HERE  *******************************************************************
void setup()
{
  Serial.begin(115200); //Setup serial port for debugging our code
}


  
void loop()
{
  //  Look for button push, then execute loop
  wait(); //this function is waiting for a button push to make the robot go
  forward(1000, 100); 
// turnLeft(250, 100);
// reverse(2000, 100);

//leftMotorF(150);
rightMotorF(150);
// leftMotorF(50);
//delay(500);
//stop();
//leftMotorR(100);
//delay (1000);
//stop();
//  rightMotorR(2000, 150);
// for (int i = 0; i < 4; i++)
// {
// forward(1000, 100);
// turnRight(725, 100);
// }

} 


