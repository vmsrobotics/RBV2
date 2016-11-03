#include "I2Cdev.h"
//#include "MPU6050.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 accelgyro; // address = 0x68, the default, on MPU6050 EVB
//MPU6050 mpu(0x69); // <-- use for AD0 high

/* =========================================================================
   NOTE: In addition to connection 3.3v, GND, SDA, and SCL, this sketch
   depends on the MPU-6050's INT pin being connected to the Arduino's
   external interrupt #0 pin. On the Arduino Uno and Mega 2560, this is
   digital I/O pin 2.
 * ========================================================================= */
 
#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards

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

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high

void dmpDataReady() 
{
    mpuInterrupt = true;
}
//

int gyro; //this is the name of yaw value from the gyroscope.  It increases with right turns, and decreases with left turns.

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

void turnAngle(String turnDirection, int angle, byte speed)
{
  String left[ ] = "left";
  String right[ ] = "right";
  Serial.print("Gyro ");
  Serial.println(gyro);
  float gyroBaseReading = gyro; //gyroBaseReading = 140
  float stopAngle = (gyroBaseReading - angle);  //stopAngle = abs(140-90) = 50
  Serial.print(" Base Reading ");
  Serial.print(gyroBaseReading); //140
  Serial.print(" Base Reading, Stop Angle ");
  Serial.println(stopAngle);  //50
   
  if (turnDirection == "left")
  {
    Serial.print("Left Turn Initiated");
    float currentDiff = (gyro - stopAngle); // currentDiff = abs(140-50) = 90
        
    while (currentDiff > 0)
    {
      currentDiff = (gyro - stopAngle);
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


