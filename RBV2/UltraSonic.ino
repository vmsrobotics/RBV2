//    VCC to +5V
//    GND to GROUND
//    Trig to pin 22
//    Echo to pin 23

const int trigPin = 5;  // Arduino pin tied to trigger pin on the ultrasonic sensor.
const int echoPin = 6;  // Arduino pin tied to echo pin on the ultrasonic sensor.

long duration;
int distance;

void sonarTurnRight(int bumpDistance, int turnDuration, byte speed, int turns) 
  { 
    int counter = 0;
    leftMotorF(speed);
    rightMotorF(speed);
    Serial.println("Initial delay");
    delay(500);
//    Serial.println("Initial delay complete");
    
    while (counter < turns)
      {
        sonar();
        Serial.print("Sensing....");
              
        if (distance > bumpDistance)
        {
          Serial.print("Forward, distance ");
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
          delay(500);
        }
      }
      stop();
  }

int sonar() 
{
  int oldDistance = distance;
  digitalWrite(trigPin, LOW);  // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);  // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // Reads the echoPin, returns the sound wave travel time in microseconds
  distance= duration*0.0067;  // Calculating the distance
  delay(50);
  if (distance != 0) 
    { 
      distance = (oldDistance + distance)/2; //averaging to smooth values
      return distance;
    }
  else
    {
      distance = oldDistance;
      return distance;
    }
}
  
void sonarSerial()
{
    int counter = 0;
    while (counter < 10000)
      {
      sonar();
      Serial.println(distance);
      counter++;
      delay(50);
      }
}

void sonarForwardAvoid(int bumpDistance, byte speed) 
  { 
    leftMotorF(speed);
    rightMotorF(speed);
    Serial.println("Initial delay");
    delay(500);
//    Serial.println("Initial delay complete");
    
    while (distance > bumpDistance)
      {
        sonar();
        Serial.print("Sensing....");
              
        if (distance > bumpDistance)
        {
          Serial.print("Forward, distance ");
          Serial.println(distance);
        }
        else
        {
          Serial.print("Stop at distance ");
          Serial.println(distance);
          stop();
        }
      }
  }
