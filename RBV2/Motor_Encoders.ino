//280 pulses per revolution
// Circumference of 4" wheel = pi * D, or 3.14 * 4 = 12.56 inches
//12.56 / 280 = 0.045 inches per pulse.
//to travel 12 inches, you would need to go for about 266 pulses (pulses = Distance/rate, or 12 / .045)

/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 * Encoder myEnc(pin1, pin2);
 *   Create an Encoder object, using 2 pins. You may create mulitple Encoder objects, where each uses its own 2 pins. The first pin should be capable of interrupts. 
 *   If both pins have interrupt capability, both will be used for best performance. Encoder will also work in low performance polling mode if neither pin has interrupts.
 * myEnc.read();
 *   Returns the accumulated position. This number can be positive or negative.
 * myEnc.write(newPosition);
 *   Set the accumulated position to a new number.
 */

#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder leftMotor(58, 59);
Encoder rightMotor(56, 57);
//   avoid using pins with LEDs attached

void encoderTest()
{
  leftMotor.write(0);
  rightMotor.write(0);
  for (int x = 0; x < 500; x = abs(leftMotor.read()))
  {
    leftMotorF(50);
//    rightMotorF(150);
    Serial.print("Left = ");
    Serial.print(leftMotor.read());
    Serial.print(", Right = ");
    Serial.print(rightMotor.read());
    Serial.println();
  }
  stop();
}

void forwardDistance(float distance, byte speed) //distance in inches
{
  Serial.println("Forward using encoders");
  leftMotor.write(0);
  rightMotor.write(0);
  
  int masterPower = speed;
  int slavePower;
  int error; //difference in encoder values
  int kp = 5; //constant of proportionality
  int distanceTravelled;
  float encDistance = distance / 0.045; //cacluate the number of encoder tics
  encDistance = (int) encDistance;  //cast the number of encoder tics as an integer
  
    
  while(distanceTravelled < encDistance)  //
    {
      distanceTravelled = leftMotor.read();
      error = leftMotor.read()-rightMotor.read(); //calculate current error
      slavePower += error / kp;
      leftMotorF(masterPower);
      rightMotorF(slavePower);
      Serial.print("Left = ");
      Serial.print(leftMotor.read());
      Serial.print(", Right = ");
      Serial.print(rightMotor.read());
      Serial.println();
            
     }
  stop();
  }

//void reverseDistance(long distance, byte speed)
//{
//  
//}
//
//void turnRightDistance(long distance, byte speed)
//{
//  
//}
//
//void turnLeftDistance(long distance, byte speed)
//{
//  
//}

