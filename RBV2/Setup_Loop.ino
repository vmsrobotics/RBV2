void setup()
{
  Serial.begin(115200); //Setup serial port for debugging our code

//########################## Pins for Motors ############################
  pinMode(2, OUTPUT);//A_EN
  pinMode(3, OUTPUT);//A_RPWM
  pinMode(4, OUTPUT);//A_DIS
  pinMode(11, OUTPUT);//A_LPWM
  pinMode(8, OUTPUT);//B_EN
  pinMode(9, OUTPUT);//B_RPWM
  pinMode(7, OUTPUT);//B_DIS
  pinMode(10, OUTPUT);//B_LPWM
  
  digitalWrite(4, LOW);//A_DIS, set the DIS pins low, and the EN pins high
  digitalWrite(7, LOW);//B_DIS
  digitalWrite(2, HIGH);//A_EN
  digitalWrite(8, HIGH);//B_EN
  
  pinMode(13, OUTPUT);
  
  //########################## Pins for Sonar ############################
  
  pinMode(5, OUTPUT); // Sets the trigPin as an Output
  pinMode(6, INPUT); // Sets the echoPin as an Input
  pinMode(52, INPUT_PULLUP);
  
  //########################## Setup for Gyro ############################
    // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
  Wire.setClock(400000); // 400kHz I2C clock.
 // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();
  pinMode(INTERRUPT_PIN, INPUT);

  devStatus = mpu.dmpInitialize();

//    // supply your own gyro offsets here, scaled for min sensitivity
//    mpu.setXGyroOffset(220);
//    mpu.setYGyroOffset(76);
//    mpu.setZGyroOffset(-85);
//    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

  // make sure it worked (returns 0 if so)
  
  if (devStatus == 0) 
  {
      // turn on the DMP, now that it's ready
      Serial.println(F("Enabling DMP..."));
      mpu.setDMPEnabled(true);

      // enable Arduino interrupt detection
      Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
      attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
      mpuIntStatus = mpu.getIntStatus();

      // set our DMP Ready flag so the main loop() function knows it's okay to use it
      Serial.println(F("DMP ready! Waiting for first interrupt..."));
      dmpReady = true;

      // get expected DMP packet size for later comparison
      packetSize = mpu.dmpGetFIFOPacketSize();
  }

    else {
      // ERROR!
      // 1 = initial memory load failed
      // 2 = DMP configuration updates failed
      // (if it's going to break, usually the code will be 1)
      Serial.print(F("DMP Initialization failed (code "));
      Serial.print(devStatus);
      Serial.println(F(")"));
  }
//gyroCalibrate();    //Settle the gyro with a ten second wait
  
}

//  const byte goButton = 52; //this button will execute our functions

//  const byte goButtonPullUp = 53;
////
//  #define pinMode (goButton, INPUT);
//  #define pinMode (goButtonPullUp, OUTPUT);
//  #define digitalWrite (goButtonPullUp, HIGH);


void loop()
{
// studentCode();
//instructorCode();
Serial.println(gyroRead()-360);
//delay(10000);
} 
