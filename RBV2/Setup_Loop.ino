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

  //##################### Pins for Color Sensor ##########################
  
  pinMode(25, OUTPUT);  //S0
  pinMode(26, OUTPUT);  //S1
  pinMode(17, OUTPUT);  //S2
  pinMode(18, OUTPUT);  //S3
  pinMode(19, INPUT);   //Out

  digitalWrite(25, HIGH); //S0 HIGH, S1 LOW = 20% output frequency scaling
  digitalWrite(26, LOW);  //S1
  
  //########################## Setup for Gyro ############################
 bool gyroInUse = true;
  if (gyroInUse == true)
  {
    // join I2C bus (I2Cdev library doesn't do this automatically)
    Wire.begin();
    Wire.setClock(400000); // 400kHz I2C clock.
    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

        // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

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
  
      else 
      {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
      }
 
//  gyroCalibrate(); //Settle the gyro with a ten second wait  

  
  }
  
}


void loop()
{
//  if programming failed, don't try to do anything
    if (!dmpReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) 
    {
//############################# LOOP FUNCTIONS GO HERE #########################

//        studentCode();
//        colorRead();
          Serial.println("COOL");
          
          delay(10);
//        delay(10000);
//        instructorCode();
        if (mpuInterrupt) break;
//        delay(20000);

//##############################################################################
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
       
    }
 // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & 0x10) || fifoCount == 1024) 
      {
          // reset so we can continue cleanly
          mpu.resetFIFO();
          Serial.println(F("FIFO overflow!"));
  
      // otherwise, check for DMP data ready interrupt (this should happen frequently)
      } 
    else if (mpuIntStatus & 0x02) 
      {
          // wait for correct available data length, should be a VERY short wait
          while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
  
          // read a packet from FIFO
          mpu.getFIFOBytes(fifoBuffer, packetSize);
          
          // track FIFO count here in case there is > 1 packet available
          // (this lets us immediately read more without waiting for an interrupt)
          fifoCount -= packetSize;
  //    // display Euler angles in degrees
      mpu.dmpGetQuaternion(&q, fifoBuffer);
      mpu.dmpGetGravity(&gravity, &q);
      mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
      Serial.print("yaw ");
      Serial.println(ypr[0] * 180/M_PI);
    gyro = (ypr[0] + 180) * 180/M_PI ; //yaw; the additional 180 brings the numbers to 0-360, which keeps the numbers positive when subtracting angles on left turns
  
      }
}
