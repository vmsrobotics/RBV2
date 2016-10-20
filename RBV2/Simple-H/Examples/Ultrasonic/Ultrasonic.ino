//http://www.instructables.com/id/Non-blocking-Ultrasonic-Sensor-for-Arduino/step2/Software/

#include "HC_SR04.h"

#define TRIG_PIN 2
#define ECHO_PIN 3
#define ECHO_INT 0

HC_SR04 sensor(TRIG_PIN, ECHO_PIN, ECHO_INT);

void setup(){  
  sensor.begin();
  Serial.begin(9600); 
  while(!Serial) continue;
}

void loop()
{
  
}

void sonarTurnRight(int bumpDistance, byte speed, int turnDuration, byte turns)
  {
    byte counter = 0;
    while (counter < turns)
    {
      sensor.start();
      while(!sensor.isFinished()) continue;
    
      if (sensor.getRange(INCH) < bumpDistance)
        {
          //turn right, ++turn counter
        }
      
        else 
        {
          //go forward
        }
    }
  
  Serial.print(sensor.getRange(INCH));
  Serial.println("in");
  delay(100);
}
