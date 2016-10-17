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
Encoder leftMotor(5, 6);
Encoder rightMotor(58, 59);
//   avoid using pins with LEDs attached

//float positionLeft  = -999;
//float positionRight = -999;

void forwardDistance(float distance, byte speed) //distance in inches
{
  Serial.println("Forward using encoders");
//  leftMotor.write(0);
 // rightMotor.write(0);
  
  float leftMotr;
  float rightMotr;
  float avgDistance;
  
  while(avgDistance < distance)  //12 inches
    {
      leftMotorF(speed);
      rightMotorF(speed);
      leftMotr = leftMotor.read();
      rightMotr = rightMotor.read();
      Serial.print("Left = ");
      Serial.print(leftMotr);
      Serial.print(", Right = ");
      Serial.print(rightMotr);
      Serial.println();
      avgDistance = (abs(leftMotr) + abs(rightMotr))/2;
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
//  // if a character is sent from the serial monitor,
//  // reset both back to zero.
//  if (Serial.available()) {
//    Serial.read();
//    Serial.println("Reset both knobs to zero");

//  }
//}
