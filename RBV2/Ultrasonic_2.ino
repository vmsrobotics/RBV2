//http://www.instructables.com/id/Non-blocking-Ultrasonic-Sensor-for-Arduino/step2/Software/

#include "HC_SR04.h"

#define TRIG_PIN 22
#define ECHO_PIN 23
#define ECHO_INT 0

HC_SR04 sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);

//void setup(){  
//  sensor.begin();
//  Serial.begin(9600); 
//  while(!Serial) continue;
//}

void sonarTurnRight(int bumpDistance, byte speed, int turnDuration, byte turns) //bumpDistance in inches, speed is 100-150, turnDuration is how long to turn, # of turns 
                                                                                //dictates the shape of your path (3=triangle, 4=square, etc.)
  {
    sensor.begin(); //initiate the sensor
    byte counter = 0;
    while (counter < turns)
      {
        sensor.start(); //start using the ultrasonic sensor to take measurements
        while(!sensor.isFinished()) continue; //keep going through the loop until the sensor sends a response (echo pin goes high)

        if (sensor.isFinished())
        {
          byte range = sensor.getRange(INCH);
          Serial.print(range);
          Serial.println("in");
                  
          if (range < bumpDistance) //in range of obstacle, time to turn
            {
              //turn right, ++counter
              Serial.println("Bump, turning right");
              stop(); //stop and wait a bit
              delay(200);
              turnRight(turnDuration, 100); //turn right for user-specified duration, at speed 100 (a good turn speed)
              counter++;
              Serial.print("Turn number ");
              Serial.println(counter);
            }
          
          else //nothing but open road in front of us, still in the loop looking for turns though
            {
              //go forward
              leftMotorF(speed);  //drive forward 
              rightMotorF(speed);
            }
            
            delay(250); 
            sensor.start();
          }      
      }
    stop(); //enough turns, time to stop
    
  
  Serial.print(sensor.getRange(INCH));
  Serial.println("in");
  delay(100);
}
