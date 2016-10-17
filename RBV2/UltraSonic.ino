#include <NewPing.h>

#define TRIGGER_PIN  22  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     23  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void sonarTurnRight(int bumpDistance, byte speed, int turnDuration) 
{ 
  int distance = sonar.ping_in();
  int counter = 0;
  leftMotorF(speed);
  rightMotorF(speed);
  
  delay(50);
  while (counter < 4)
  {
    distance = sonar.ping_in();
//    delay(50);
    leftMotorF(speed);
    rightMotorF(speed);
    Serial.print("Distance ");
    Serial.print(distance);
    Serial.println(" in");
    
    while (distance < bumpDistance) 
        {
          Serial.print("Distance ");
          Serial.print(distance);
          Serial.println(" in");
          stop();
          delay(200);
          turnRight(turnDuration, 100);
          distance = sonar.ping_in();
          counter++;
          Serial.print("#of turns ");
          Serial.print(counter);
           
      }
  }
}

void sonarSerial()
{
    int counter = 0;
    while (counter < 1000)
      {
      int distance = sonar.ping_in();
      Serial.print("Distance ");
      Serial.print(distance);
      Serial.println(" in");
      delay(100);
      counter++;
      }
}


