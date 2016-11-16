//    VCC to +5V
//    GND to GROUND
//    Trig to pin 5
//    Echo to pin 6

const int trigPin = 5;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int echoPin = 6;  // Arduino pin tied to echo pin on the ultrasonic sensor.


int sonar() 
{
    long duration;
    int distance;
  
    digitalWrite(trigPin, LOW);  // Clears the trigPin
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
    distance = duration * 0.0067;  // Calculating the distance in inches
    delay(25);
    
//    if (reading != 0) 
//      { 
//        (reading += oldReading) / 2; //averaging to smooth values
//      }
//    else
//      {
//        reading = oldReading;
//      }
//  }
 
  return distance;
}//end int sonar()
  

void sonarTurnRight(int bumpDistance, int turnDuration, byte speed, int turns) 
  { 
    int distance = sonar();
    if (distance > 2)
    {
    Serial.println("Sonar Turn Right Initiated, Drive Forward, wait for bump");
    int counter = 0;
    leftMotorF(speed);
    rightMotorF(speed);
    Serial.println("Initial delay");
//    delay(50);
//    Serial.println("Initial delay complete");
    
    while (counter < turns)
      {
        distance = sonar();
        Serial.print("Sensing....");
              
        if (distance > bumpDistance)
        {
          Serial.print("Driving forward, distance detected ");
          Serial.print(distance);
          Serial.print(";   Remaining turns = ");
          Serial.println(turns - counter);
        }
  
        else
        {
          stop();
          counter++;
          Serial.print("BUMP AT ");
          Serial.print(distance);
          Serial.print(" inches, ");
          turnRight(turnDuration, 100);
          Serial.print(";   Turn # ");
          Serial.print(counter);
          Serial.println("complete");
          delay(500);
          leftMotorF(speed);
          rightMotorF(speed);
          delay(50);
        }
      }
      stop();
    }//end (if sonar())
    
    else
    {
      Serial.println("No Sonar Response " + String(distance));
    }
  }//end sonarTurnRight


void sonarSerial()
{
    
    int counter = 0;
    while (counter < 10000)
      {
      int distance = sonar();
      Serial.println(distance);
      counter++;
      }
}//end sonarSerial

void sonarForwardAvoid(int bumpDistance, byte speed) 
  {
    int distance = sonar();
    if (distance > 2)
    {
    Serial.print("Sonar Forward Avoid Initiated, Drive Forward, stop at distance of ");
    Serial.println(bumpDistance);
    leftMotorF(speed);
    rightMotorF(speed);
    
      while (distance > bumpDistance)
        {
            Serial.print("Running Sonar Forward Avoid, distance not reached, distance detected ");
            Serial.println(distance);
            distance = sonar();
        }
        
            stop();
            Serial.print("Stopped at distance ");
            Serial.println(distance);
          
    }//end if (distance > 2)
    
    else
    {
      Serial.println("No Sonar Response " + String(distance));
      
    }
  }//end sonarForwardAvoid
