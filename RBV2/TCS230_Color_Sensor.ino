///*  http://circuitdigest.com/microcontroller-projects/arduino-color-sensor-tcs3200
//    VDD to +5V
//    GND to GROUND
//    OE (output Enable) to GND
//    S0 to UNO pin 25
//    S1 to UNO pin 26
//    S2 to UNO pin 17
//    S3 to UNO pin 18
//    OUT to UNO pin 19
//
//    The color which needs to be sensed by the color sensor is selected by two pins S2 and S3. With these two pins logic control we can tell sensor which color 
//    light intensity is to be measured.  
//    
//    Say we need to sense the RED color intensity we need to set both pins to LOW. Once that is done the sensor detects the 
//    intensity and sends the value to the control system inside the module.
//    S2          S3          Photodiode Type
//    L           L           Red
//    L           H           Blue
//    H           L           Clear (no filter)
//    H           H           Green
//
//    The light intensity measured by array is sent to current to frequency converter. What it does is, it puts out a square wave whose frequency is in relation 
//    to current sent by ARRAY.
//
//    So we have a system which sends out a square wave whose frequency depends on light intensity of color which is selected by S2 and S3.
// 
//    The signal frequency sent by module can be modulated depending on use. We can change the output signal frequency bandwidth.
//    
//    S0          S1          Output Frequency Scaling (f0)
//    L           L           Power Down
//    L           H           2%
//    H           L           20%
//    H           H           100%
//    
//The frequency scaling is done by two bits S0 and S1. For convenience we are going to limit the frequency scaling to 20%. This is done by setting S0 to high and 
//S1 to LOW. This feature comes in handy when we are using the module on system with low clock.
//
//Although different colors have different sensitivity, for a normal use it won’t make much difference.
//The DUE here sends a signal to the module to detect colors and the data received by the module is shown in the serial monitor.
//
//The DUE detects three color intensities separately and shows them on serial output.
//
//The DUE can detect the signal pulse duration by which we can get the frequency of square wave sent by module. With the frequency at hand we can match it with color on sensor.
//
//Int frequency = pulseIn(19, LOW);
// 
//As by above condition the DUE reads pulse duration on 19th pin of DUE and stores it value in “frequency” integer.
//We are going to do this for all three colors for color recognition. All three color intensities are shown by frequencies on 16x2 LCD.
// 
// */

const byte S0 = 25;
const byte S1 = 26;
const byte S2 = 17;
const byte S3 = 18;
const byte Output = 19;

int red()
  {
  unsigned int frequency; 
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);//setting for RED color sensor
  frequency = pulseIn(Output, LOW);//reading frequency
  delay(25);
  return frequency;
  }
  
int green()
  {
  unsigned int frequency; 
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);// setting for GREEN color sensor
  frequency = pulseIn(Output, LOW);// reading frequency
  delay(25); 
  return frequency;    
  }
 
int blue()
  {
  unsigned int frequency; 
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);// setting for BLUE color sensor
  frequency = pulseIn(Output, LOW);// reading frequency
  delay(25);
  return frequency;
  }        

void forwardColorChange(byte speed, int factor)
{
    Serial.print("Forward Color Change Initiated, Drive Forward, stop at change of color reading ");
    int blueRead = blue();
    int redRead = red();
    while (blueRead + redRead > factor)
    {
      blueRead = blue();
      redRead = red();
      leftMotorF(speed);
      rightMotorF(speed);
      Serial.println(blueRead + redRead);
    }
    
      stop();
      Serial.println("Color change detected");
      Serial.print("red =  ");
      Serial.print(redRead);
      Serial.print(" blue =  ");
      Serial.println(blueRead);
      Serial.println(blueRead + redRead);
    
}
 
