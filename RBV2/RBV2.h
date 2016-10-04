#ifndef RBV2_H
#define RBV2_H

#include "Arduino.h"

class Motor
{
  public:
    void forward (int duration, byte speed);
    void reverse (int duration, byte speed);
    void stop();
    void turnRight(int duration, int speed);
    void turnLeft(int duration, int speed);
    void leftMotorF(byte speed);
    void rightMotorF (byte speed);
    void leftMotorR(byte speed);
    void rightMotorR(byte speed);
  private:
    const byte A_EN;    //right wheel
    const byte A_RPWM;    //(forward)
    const byte A_DIS;    
    const byte A_LPWM;   //(reverse)
    
    const byte B_EN;   //left wheel
    const byte B_RPWM;   //(forward)
    const byte B_DIS;   
    const byte B_LPWM;  //(reverse)
    const byte LED;
};

#endif


