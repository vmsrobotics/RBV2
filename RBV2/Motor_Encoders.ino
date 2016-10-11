////280 pulses per revolution
//
///* Encoder Library - TwoKnobs Example
// * http://www.pjrc.com/teensy/td_libs_Encoder.html
// *
// * This example code is in the public domain.
// * Encoder myEnc(pin1, pin2);
// *   Create an Encoder object, using 2 pins. You may create mulitple Encoder objects, where each uses its own 2 pins. The first pin should be capable of interrupts. 
// *   If both pins have interrupt capability, both will be used for best performance. Encoder will also work in low performance polling mode if neither pin has interrupts.
// * myEnc.read();
// *   Returns the accumulated position. This number can be positive or negative.
// * myEnc.write(newPosition);
// *   Set the accumulated position to a new number.
// */
//
//#include <Encoder.h>
//
//// Change these pin numbers to the pins connected to your encoder.
////   Best Performance: both pins have interrupt capability
////   Good Performance: only the first pin has interrupt capability
////   Low Performance:  neither pin has interrupt capability
//Encoder leftMotor(5, 6);
//Encoder rightMotor(58, 59);
////   avoid using pins with LEDs attached
//
//void setup() {
//  Serial.begin(9600);
//  Serial.println("TwoKnobs Encoder Test:");
//}
//
//long positionLeft  = -999;
//long positionRight = -999;
//
//void loop() {
//  long newLeft, newRight;
//  newLeft = leftMotor.read();
//  newRight = rightMotor.read();
//  if (newLeft != positionLeft || newRight != positionRight) {
//    Serial.print("Left = ");
//    Serial.print(newLeft);
//    Serial.print(", Right = ");
//    Serial.print(newRight);
//    Serial.println();
//    positionLeft = newLeft;
//    positionRight = newRight;
//  }
//  // if a character is sent from the serial monitor,
//  // reset both back to zero.
//  if (Serial.available()) {
//    Serial.read();
//    Serial.println("Reset both knobs to zero");
//    leftMotor.write(0);
//    rightMotor.write(0);
//  }
//}
