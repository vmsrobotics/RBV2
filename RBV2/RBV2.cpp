#include "Arduino.h"
#include "RBV2.h"

Motor::Motor (int A_EN, int A_DIS, int A_RPWM, int A_LPWM, int B_EN, int B_DIS, int B_RPWM, int B_LPWM)
{
  pinMode(A_EN, OUTPUT);
  pinMode(A_DIS, OUTPUT);
  pinMode(A_RPWM, OUTPUT);
  pinMode(A_LPWM, OUTPUT);

  pinMode(B_EN, OUTPUT);
  pinMode(B_DIS, OUTPUT);
  pinMode(B_RPWM, OUTPUT);
  pinMode(B_LPWM, OUTPUT);
}

void Motor::forward (int duration, byte speed)
{
  leftMotorF(speed);
  rightMotorF(speed);
  delay (duration);
  stop();
}

void Motor::reverse (int duration, byte speed)
{
  leftMotorR(speed);
  rightMotorR(speed);
  delay (duration);
  stop();
}

void Motor::stop()
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

void Motor::turnRight(int duration, int speed)   //add gyro code later angle = seconds of turn
{
  leftMotorF (speed);
  rightMotorR (speed);
  delay(duration);
  stop();
}

void Motor::turnLeft(int duration, int speed)   //add gyro code later angle = seconds of turn
{
  leftMotorR (speed);
  rightMotorF (speed);
  delay(duration);
  stop();
}

void Motor::leftMotorF(byte speed)
{
  digitalWrite(A_RPWM, HIGH); //left motor forward
  analogWrite(A_LPWM, 255-speed);
}

void Motor::rightMotorF (byte speed)
{
  digitalWrite(B_LPWM, HIGH);  //right motor forward
  analogWrite(B_RPWM, 255-speed);
}

void Motor::leftMotorR(byte speed)
{
  analogWrite(A_RPWM, (255-speed)); //left motor reverse
  digitalWrite(A_LPWM, HIGH);
}

void Motor::Motor::rightMotorR(byte speed)
{
  digitalWrite(B_RPWM, HIGH);  //right motor reverse
  analogWrite(B_LPWM, (255-speed));
}