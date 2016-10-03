// These are the pin connections for the motor controller, they won't change.
const byte A_EN = 2;    //right wheel
const byte A_RPWM = 3;    //(forward)
const byte A_DIS = 4;    
const byte A_LPWM = 11;   //(reverse)

const byte B_EN = 8;   //left wheel
const byte B_RPWM = 9;   //(forward)
const byte B_DIS = 7;   
const byte B_LPWM = 10;  //(reverse)
const byte LED = 13;

void setup()
{
// Let's declare some things first.  Leave these ones alone...
pinMode(A_EN, OUTPUT);
pinMode(A_DIS, OUTPUT);
pinMode(B_EN, OUTPUT);
pinMode(B_DIS, OUTPUT);
pinMode(LED, OUTPUT);
/** PWM pin configurate */
pinMode(A_RPWM, OUTPUT);
pinMode(A_LPWM, OUTPUT);
pinMode(B_RPWM, OUTPUT);
pinMode(B_LPWM, OUTPUT);

digitalWrite(A_DIS, LOW);
digitalWrite(B_DIS, LOW);
digitalWrite(A_EN, HIGH);
digitalWrite(B_EN, HIGH);
digitalWrite(LED, HIGH);

///****************************************************************************************************************************
// * ROBOT SETUP
// * Left motor is attached to Channel A
// * Right motor is attached to channel B
// * 
// * Functions:
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

// forward(1000, 100); 
// turnLeft(250, 100);
// reverse(2000, 100);

// leftMotorF(2000, 150);
// rightMotorF(2000, 150);
// leftMotorF(50);
// delay(1000);
  leftMotorR(100);
  delay (1000);
  stop();
//  rightMotorR(2000, 150);
// for (int i = 0; i < 4; i++)
// {
// forward(1000, 100);
// turnRight(725, 100);
// }

}


  
void loop()
{
  //Nothing to put here, we only want our code to run once.
}

void forward (int duration, byte speed)
{
  leftMotorF(speed);
  rightMotorF(speed);
  delay (duration);
  stop();
}

void reverse (int duration, byte speed)
{
  leftMotorR(speed);
  rightMotorR(speed);
  delay (duration);
  stop();
}

void stop()
{
  digitalWrite(A_EN, LOW);
  digitalWrite(B_EN, LOW);
  digitalWrite(A_RPWM, HIGH);
  digitalWrite(A_LPWM, HIGH);
  digitalWrite(B_RPWM, HIGH);
  digitalWrite(B_LPWM, HIGH);
  delay(100);
  digitalWrite(A_EN, HIGH);
  digitalWrite(B_EN, HIGH);
}

void turnRight(int duration, int speed)   //add gyro code later angle = seconds of turn
{
  leftMotorF (speed);
  rightMotorR (speed);
  delay(duration);
  stop();
}

void turnLeft(int duration, int speed)   //add gyro code later angle = seconds of turn
{
  leftMotorR (speed);
  rightMotorF (speed);
  delay(duration);
  stop();
}

void leftMotorF(byte speed)
{
  digitalWrite(A_RPWM, HIGH); //left motor forward
  analogWrite(A_LPWM, 255-speed);
}

void rightMotorF (byte speed)
{
  digitalWrite(B_LPWM, HIGH);  //right motor forward
  analogWrite(B_RPWM, 255-speed);
}

void leftMotorR(byte speed)
{
  analogWrite(A_RPWM, (255-speed)); //left motor reverse
  digitalWrite(A_LPWM, HIGH);
}

void rightMotorR(byte speed)
{
  digitalWrite(B_RPWM, HIGH);  //right motor reverse
  analogWrite(B_LPWM, (255-speed));
}



/*
Channel A
EN pin 2
RPWM pin 3
DIS pin 4
LPWM pin 11

Channel B
EN pin 8
RPWM pin 9
DIS pin 7
LPWM pin 10

Rotate forward: EN = HIGH, RPWM = PWM, LPWM = HIGH, DIS = vacant
Rotate reverse: EN = HIGH, RPWM = HIGH, LPWM = PWM, DIS = vacant
Stop and brake: EN = HIGH, RPWM = HIGH, LPWM = HIGH, DIS = vacant
Stop but not brake: EN = 0, RPWM = HIGH, LPWM = HIGH, DIS = vacant
Prohibit : EN = X, RPWM = X, LPWM = X, DIS = HIGH

*/
