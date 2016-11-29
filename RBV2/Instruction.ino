void instructorCode()
 {
  
//    forward(1000, 150);
//    digitalWrite(13, HIGH);
//reverse(1000, 100);
//    sonarSerial();
//    sonarTurnRight(12, 850, 100, 4);
//delay(1000);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//sonarForwardAvoid(12, 150);
//turnAngle("left", 90, 150);
//   turnRight(1000, 150);
//  leftMotorF(100);
//  delay(3000);
//  stop();
//  delay(2000);
  
//  for (int x=0; x<1000; x++)
//  {
//    gyroRead();
//
//  }
//  Serial.println(gyroRead());
//  turnAngle("left", 90, 150);
//  forward(1000, 150);
//  turnAngle("left", 180, 150);
//  delay(1000000);

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
forwardColorChange(100, 250);
turnRight(750, 150);
forwardColorChange(100, 250);
turnLeft(750, 150);
forwardColorChange(100, 250);
turnRight(750, 150);
forwardColorChange(100, 250);
turnRight(750, 150);
forwardColorChange(100, 250);
if (red() < blue())
{
  Serial.println("Predominantly red");
  turnRight(750, 150);
  forwardColorChange(100, 250);
}

else
{
  Serial.print("Predominantly blue");
  turnLeft(750, 150);
  forwardColorChange(100, 250);
}
//delay(10000);
 }


