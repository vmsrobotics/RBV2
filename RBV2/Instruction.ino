//https://www.tinkercad.com/things/cvAfXfpwYFH-super-habbi/editel?tenant=circuits
//global variables go here:
int limit = 8;

void instructorCode()
 {
/*Iterative development is a way of breaking down the 
 *software development of a large application into 
 *smaller chunks. In iterative development, feature code 
 *is designed, developed and tested in repeated cycles.
 */
 
//*************** Serial Port ****************
//Serial port speed = 115200
//digitalWrite(13, HIGH);
Serial.println ("Hello Students!");
//sends the message between quotes to the serial port
//Serial.println ("Hello Students!");
//sends the message between quotes to the serial port and 
//adds a hard return (returns to new line)

//**************** Variables *****************
//variable scope, where do you want it to work?
//declaring variables
int x; //no value assigned
int i = 10; //no decimals, -32,768 to 32,768
byte b = 255; //0-255; 256 = 0
float f = 1.123456; //3.4028235E+38 to -3.4028235E+38
float fa = 1.0; //you have to have a decimal point



//***************** for loop *****************
for (x=1; x < 10; x++)
{
  Serial.println (x);
//  //testing variables
// if (x >> limit)
// {
//  Serial.println ("limit reached");
// }
  delay(1000);
}

//************* Driving Commands *************
//leftMotorF(100);
//forward(1000, 150); //((int)duration, (byte)speed)
//reverse(1000, 100);
//turnRight(1000, 150);
//turnLeft(750, 150);

//**************** while loop ****************
//while (digitalRead(waitButton == LOW)
//{
//  //do nothing until the wait button is pushed
//  flashRED_GREEN(500); //(int) interval

//}

//************** Sonar Commands **************
//sonarSerial();
//sonarTurnRight(12, 850, 100, 4);
//delay(1000);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);


//delay(3000);
//stop();
//delay(2000);
//  
//for (int x=0; x<1000; x++)
//  {
//    gyroRead();
//
//  }
//  Serial.println(gyroRead());
//  turnAngle("left", 90, 150);
//  forward(1000, 150);
//  turnAngle("left", 180, 150);
//  delay(1000000);
//
//if (red() < blue())
//{
//  Serial.println("Predominantly red");
//}
//
//else
//{
//  Serial.print("Predominantly blue");
//}
//    
//    Serial.print("red =  ");
//    Serial.print(red());
//    Serial.print(" blue =  ");
//    Serial.println(blue());
//forwardColorChange(100, 250);
//forwardColorChange(100, 250);

//forwardColorChange(100, 250);
//turnRight(750, 150);
//forwardColorChange(100, 250);
//turnRight(750, 150);
//forwardColorChange(100, 250);
//if (colorRed() < colorBlue())
//{
//  Serial.println("Predominantly red");
//  turnRight(750, 150);
//  forwardColorChange(100, 250);
//}
//
//else
//{
//  Serial.print("Predominantly blue");
//  turnLeft(750, 150);
//  forwardColorChange(100, 250);
//}
//delay(10000);
 }


