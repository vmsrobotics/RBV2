//#include <NewPing.h>
//
//#define TRIGGER_PIN  22  // Arduino pin tied to trigger pin on the ultrasonic sensor.
//#define ECHO_PIN     23  // Arduino pin tied to echo pin on the ultrasonic sensor.
//#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
//
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
//
//void sonarAvoid(byte Speed, int bumpDistance) 
//{ 
//  int distance = sonar.ping_in();
//  
//  delay(50);
//  
//  while (distance > bumpDistance) 
//      {
//        forward (Speed);
//        distance = sonar.ping_in();
//        delay(50);
//        Serial.print("Distance ");
//        Serial.print(distance);
//        Serial.println(" in");
//      }
//
//  while (distance < bumpDistance)
//      {    
//        stopCar();
//        delay (250);
//        backward();
//        delay(500);
//        right();
//        delay(750);
//        distance = sonar.ping_in();
//        delay(50);
//        Serial.print("Turning Distance ");
//        Serial.print(distance);
//        Serial.println(" in");
//        
//      }
