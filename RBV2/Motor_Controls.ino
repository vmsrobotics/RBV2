void setup()
{
  Serial.begin(115200); //Setup serial port for debugging our code
  studentCode();
}

void loop()
{

//

} 

  //  const byte goButton = 52; //this button will execute our functions

//  const byte goButtonPullUp = 53;
////
//  #define pinMode (goButton, INPUT);
//  #define pinMode (goButtonPullUp, OUTPUT);
//  #define digitalWrite (goButtonPullUp, HIGH);

// These are the pin connections for the motor controllers, they won't change.
#if (oldMotorController == false)

  const byte A_EN = 2;    //right wheel
  const byte A_RPWM = 3;    //(forward)
  const byte A_DIS = 4;    
  const byte A_LPWM = 11;   //(reverse)
  
  const byte B_EN = 8;   //left wheel
  const byte B_RPWM = 9;   //(forward)
  const byte B_DIS = 7;   
  const byte B_LPWM = 10;  //(reverse)
  const byte goButton = 52; 
  
  #define pinMode(A_EN, OUTPUT);
  #define pinMode(A_DIS, OUTPUT);
  #define pinMode(B_EN, OUTPUT);
  #define pinMode(B_DIS, OUTPUT);
    /** PWM pin configurate */
  #define pinMode(A_RPWM, OUTPUT);
  #define pinMode(A_LPWM, OUTPUT);
  #define pinMode(B_RPWM, OUTPUT);
  #define pinMode(B_LPWM, OUTPUT);
  #define pinMode(goButton, INPUT_PULLUP);
    
 
  void forward (int duration, byte speed)
  {
    Serial.println("Forward");
    leftMotorF(speed);
    rightMotorF(speed);
    delay (duration);
    stop();
  }
  
  void reverse (int duration, byte speed)
  {
    Serial.println ("Reverse");
    leftMotorR(speed);
    rightMotorR(speed);
    delay (duration);
    stop();
  }
  
  void stop()
  {
    Serial.println ("Stop");
    digitalWrite(A_EN, LOW);
    digitalWrite(B_EN, LOW);
    digitalWrite(A_RPWM, HIGH);
    digitalWrite(A_LPWM, HIGH);
    digitalWrite(B_RPWM, HIGH);
    digitalWrite(B_LPWM, HIGH);
    delay(100);
    digitalWrite(A_EN, HIGH);
    digitalWrite(B_EN, HIGH);
  }
  
  void turnRight(int duration, int speed)   //add gyro code later angle = seconds of turn
  {
    Serial.println ("turnRight");
    leftMotorF (speed);
    rightMotorR (speed);
    delay(duration);
    stop();
  }
  
  void turnLeft(int duration, int speed)   //add gyro code later angle = seconds of turn
  {
    Serial.println ("turnLeft");
    leftMotorR (speed);
    rightMotorF (speed);
    delay(duration);
    stop();
  }
  
  void leftMotorF(byte speed)
  {
    Serial.println ("leftMotorF");
    digitalWrite(A_RPWM, HIGH); //left motor forward
    analogWrite(A_LPWM, 255-speed);
  }
  
  void rightMotorF (byte speed)
  {
    Serial.println ("rightMotorF");
    digitalWrite(B_LPWM, HIGH);  //right motor forward
    analogWrite(B_RPWM, 255-speed);
  }
  
  void leftMotorR(byte speed)
  {
    Serial.println ("leftMotorR");
    analogWrite(A_RPWM, (255-speed)); //left motor reverse
    digitalWrite(A_LPWM, HIGH);
  }
  
  void rightMotorR(byte speed)
  {
    Serial.println ("rightMotorR");
    digitalWrite(B_RPWM, HIGH);  //right motor reverse
    analogWrite(B_LPWM, (255-speed));
  }
  
 void wait()
  {
    while  (digitalRead(goButton) == HIGH);
    {
      stop();
    }
  }

  
  
  
  /*
  Channel A
  EN pin 2
  RPWM pin 3
  DIS pin 4
  LPWM pin 11
  
  Channel B
  EN pin 8
  RPWM pin 9
  DIS pin 7
  LPWM pin 10
  
  Rotate forward: EN = HIGH, RPWM = PWM, LPWM = HIGH, DIS = vacant
  Rotate reverse: EN = HIGH, RPWM = HIGH, LPWM = PWM, DIS = vacant
  Stop and brake: EN = HIGH, RPWM = HIGH, LPWM = HIGH, DIS = vacant
  Stop but not brake: EN = 0, RPWM = HIGH, LPWM = HIGH, DIS = vacant
  Prohibit : EN = X, RPWM = X, LPWM = X, DIS = HIGH
  
  */



#else  //old motor controller code

    //declaring the pins for the IN pins on the L298N
  const int rightEnablePin = 3;  //Enable A
  const int rightForwardPin = 4; //IN2
  const int rightBackwardPin = 2; //IN1
  const int leftEnablePin = 5;  //Enable B
  const int leftBackwardPin = 7; //IN4
  const int leftForwardPin = 8; //IN3
    
  //Stating that the pins are OUTPUT
  pinMode(rightEnablePin, OUTPUT);
  pinMode(rightForwardPin, OUTPUT);
  pinMode(rightBackwardPin, OUTPUT);
  pinMode(leftEnablePin, OUTPUT);
  pinMode(leftForwardPin, OUTPUT);
  pinMode(leftBackwardPin, OUTPUT);

//  void wait()
//  {
//      while  (digitalRead(goButton) == LOW);
//    {
//      stop();
//    }
//  }
  
  void forward(int duration, byte speed){
    Serial.println("Drive Forward");
    
    digitalWrite(rightForwardPin, HIGH);
    digitalWrite(rightBackwardPin, LOW);
    digitalWrite(leftForwardPin, HIGH);
    digitalWrite(leftBackwardPin, LOW);
    analogWrite(rightEnablePin, speed); 
    analogWrite(leftEnablePin, speed);
    delay(duration);
  }
    
  //Setting the wheels to go backward by setting the backward pins to HIGH
  void reverse(int duration, byte speed){
    Serial.println("Drive Backwards");
    digitalWrite(rightForwardPin, LOW);
    digitalWrite(rightBackwardPin, HIGH);
    digitalWrite(leftForwardPin, LOW);
    digitalWrite(leftBackwardPin, HIGH);
    analogWrite(rightEnablePin, speed); 
    analogWrite(leftEnablePin, speed);
    delay(duration);
  }
  
  //Setting the wheels to go right by setting the rightBackwardPin and leftForwardPin to HIGH
  void turnRight(int duration, byte speed){
    Serial.println("Turn Right");
    digitalWrite(rightForwardPin, LOW);
    digitalWrite(rightBackwardPin, HIGH);
    digitalWrite(leftForwardPin, HIGH);
    digitalWrite(leftBackwardPin, LOW);
    analogWrite(rightEnablePin, speed); 
    analogWrite(leftEnablePin, speed);
    delay(duration);
  }
  
  //Setting the wheels to go left by setting the rightForwardPin and leftBackwardPin to HIGH
  void turnLeft(int duration, byte speed){
    Serial.println("Turn Left");
    digitalWrite(rightForwardPin, HIGH);
    digitalWrite(rightBackwardPin, LOW);
    digitalWrite(leftForwardPin, LOW);
    digitalWrite(leftBackwardPin, HIGH);
    analogWrite(rightEnablePin, speed); 
    analogWrite(leftEnablePin, speed);
    delay(duration);
  }
  
  //Setting the wheels to go stop by setting all the pins to LOW
  void stop(){
    Serial.println("Stop");
    digitalWrite(rightEnablePin, LOW); 
    digitalWrite(leftEnablePin, LOW);
    digitalWrite(rightForwardPin, LOW);
    digitalWrite(rightBackwardPin, LOW);
    digitalWrite(leftForwardPin, LOW);
    digitalWrite(leftBackwardPin, LOW);
    delay(100);
  }

#endif
