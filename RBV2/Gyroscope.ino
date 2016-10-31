#include "I2Cdev.h"
//#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
MPU6050 accelgyro; // address = 0x68, the default, on MPU6050 EVB
//MPU6050 mpu(0x69); // <-- use for AD0 high

/* =========================================================================
   NOTE: In addition to connection 3.3v, GND, SDA, and SCL, this sketch
   depends on the MPU-6050's INT pin being connected to the Arduino's
   external interrupt #0 pin. On the Arduino Uno and Mega 2560, this is
   digital I/O pin 2.
 * ========================================================================= */
 
#define INTERRUPT_PIN 14  // use pin 2 on Arduino Uno & most boards

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

void dmpDataReady() 
{
    mpuInterrupt = true;
}

void gyroCalibrate() 
{
    //10 second calibration period to settle the Gyro
    Serial.print("Calibrating Gyroscope");
    for (int x = 0; x < 10; x++)
    {
      Serial.print(".");
      delay(500);
    }  
  
}

int gyroRead()
{
// if programming failed, don't try to do anything
//    if (!dmpReady) return;

// wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) 
      {
        // other program behavior stuff here
        // .
        // .
        // .
        // if you are really paranoid you can frequently test in between other
        // stuff to see if mpuInterrupt is true, and if so, "break;" from the
        // while() loop to immediately process the MPU data
        // .
        // .
        // .
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
        }

//    // display Euler angles in degrees
    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
//    Serial.print("yaw ");
//    Serial.println(ypr[0] * 180/M_PI);
  int gyro = (ypr[0] + 180) * 180/M_PI ; //yaw; the additional 180 brings the numbers to 0-360, which keeps the numbers positive when subtracting angles on left turns
  return gyro;
}

int gyro;

void turnAngle(String turnDirection, int angle, byte speed)
{
  bool startUp = true;
  String left[ ] = "left";
  String right[ ] = "right";
  gyroRead();
  Serial.print("Gyro ");
  Serial.println(gyroRead());
  float gyroBaseReading = gyroRead(); //gyroBaseReading = 140
  float stopAngle = (gyroBaseReading - angle);  //stopAngle = abs(140-90) = 50
  Serial.print(" Base Reading ");
  Serial.print(gyroBaseReading); //140
  Serial.print(" Base Reading, Stop Angle ");
  Serial.println(stopAngle);  //50
   
  if (turnDirection == "left")
  {
    Serial.print("Left Turn Initiated");
    float currentDiff = (gyroRead() - stopAngle); // currentDiff = abs(140-50) = 90
        
    while (currentDiff > 0)
    {
      gyroRead();
      currentDiff = (gyroRead() - stopAngle);
      Serial.print("Current Difference ");
      Serial.println(currentDiff);
      float percentRemain = (currentDiff / angle)*100;
      float speedFactorFloat = (((speed-75) * percentRemain)/100)+75;  //speedfactor = (speed - 50 * x/angle) + 50; max speed will be user-defined, min speed 50
      int speedFactor = speedFactorFloat;
      Serial.print("Speed Factor ");
      Serial.println(speedFactor);
      leftMotorR(speedFactor);
      rightMotorF(speedFactor);
    }
    stop();
//    delay(20000);
  }

  //if the angle is greater than zero (right turn)
  else
  {
    Serial.print("Right Turn Initiated");
  }
}


