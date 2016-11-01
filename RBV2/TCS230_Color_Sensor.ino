/////*  http://circuitdigest.com/microcontroller-projects/arduino-color-sensor-tcs3200
////    VDD to +5V
////    GND to GROUND
////    OE (output Enable) to GND
////    S0 to UNO pin 15
////    S1 to UNO pin 16
////    S2 to UNO pin 17
////    S3 to UNO pin 18
////    OUT to UNO pin 19
////
////    The color which needs to be sensed by the color sensor is selected by two pins S2 and S3. With these two pins logic control we can tell sensor which color 
////    light intensity is to be measured.  
////    
////    Say we need to sense the RED color intensity we need to set both pins to LOW. Once that is done the sensor detects the 
////    intensity and sends the value to the control system inside the module.
////    S2          S3          Photodiode Type
////    L           L           Red
////    L           H           Blue
////    H           L           Clear (no filter)
////    H           H           Green
////
////    The light intensity measured by array is sent to current to frequency converter. What it does is, it puts out a square wave whose frequency is in relation 
////    to current sent by ARRAY.
////
////    So we have a system which sends out a square wave whose frequency depends on light intensity of color which is selected by S2 and S3.
//// 
////    The signal frequency sent by module can be modulated depending on use. We can change the output signal frequency bandwidth.
////    
////    S0          S1          Output Frequency Scaling (f0)
////    L           L           Power Down
////    L           H           2%
////    H           L           20%
////    H           H           100%
////    
////The frequency scaling is done by two bits S0 and S1. For convenience we are going to limit the frequency scaling to 20%. This is done by setting S0 to high and 
////S1 to LOW. This feature comes in handy when we are using the module on system with low clock.
////
////Although different colors have different sensitivity, for a normal use it won’t make much difference.
////The DUE here sends a signal to the module to detect colors and the data received by the module is shown in the serial monitor.
////
////The DUE detects three color intensities separately and shows them on serial output.
////
////The DUE can detect the signal pulse duration by which we can get the frequency of square wave sent by module. With the frequency at hand we can match it with color on sensor.
////
////Int frequency = pulseIn(19, LOW);
//// 
////As by above condition the DUE reads pulse duration on 19th pin of DUE and stores it value in “frequency” integer.
////We are going to do this for all three colors for color recognition. All three color intensities are shown by frequencies on 16x2 LCD.
//// 
//// */
//
//
//unsigned int frequency = 0;
//const byte S0 = 15;
//const byte S1 = 16;
//const byte S2 = 17;
//const byte S3 = 18;
//const byte OutPut = 19;
//
//pinMode(S0, OUTPUT);
//pinMode(S1, OUTPUT);//PINS S0-S3 as OUTPUT
//pinMode(S2, OUTPUT);
//pinMode(S3, OUTPUT);
//pinMode(OutPut, INPUT);//OUT PIN from sensor as input to DUE
//
//
//
//void colorRead()
//  {
//  digitalWrite(S0,HIGH);
//  digitalWrite(S1,LOW); //setting frequency selection to 20%
//  
//  Serial.print("R=");//printing name
//  digitalWrite(S2,LOW);
//  digitalWrite(S3,LOW);//setting for RED color sensor
//  frequency = pulseIn(OutPut, LOW);//reading frequency
//  Serial.print(frequency);//printing RED color frequency
//  Serial.print("  ");
//  delay(500);
// 
//  Serial.print("B=");// printing name
//  digitalWrite(S2,LOW);
//  digitalWrite(S3,HIGH);// setting for BLUE color sensor
//  frequency = pulseIn(OutPut, LOW);// reading frequency
//  Serial.print(frequency);// printing BLUE color frequency
//  Serial.print("  ");
//  delay(500);
// 
//  Serial.print("G=");// printing name
//  digitalWrite(S2,HIGH);
//  digitalWrite(S3,HIGH);// setting for GREEN color sensor
//  frequency = pulseIn(OutPut, LOW);// reading frequency
//  Serial.print(frequency);// printing GREEN color frequency
//  Serial.print("    ");
//  delay(500);        
//}         
// 
