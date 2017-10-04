void loop() 
{

//    instructorCode();
    studentCode();
    delay(200000);  //stop the loop for a while (200 seconds)
}

//#################### Global Variables for Servo #######################

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

//#################### Global Variables for Gyro #######################

#include "Wire.h"
#define degconvert 57.2957786 //there are approx 57 degrees in a radian.

const int MPU_addr=0x68;
double AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //These will be the raw data from the MPU6050.
uint32_t timer; //it's a timer, saved as an unsigned int.  We use it to save times 
                //from the "micros()" command and subtract the present time in microseconds 
                //from the time stored in timer to calculate the time for each loop.
                
double compAngleX, compAngleY; //These are the angles in the complementary filter

bool blinkState = false;



//************************* Flash LED *****************************************
unsigned long previousMillis = 0;        // will store last time LED was updated
int REDledState;             // ledState used to set the LED
int GREENledState;

const int RED_LED =  49;// the number of the RED LED pin
const int GREEN_LED =  29;// the number of the GREEN LED pin

void flashRED_GREEN(int interval) 
  {  unsigned long currentMillis = millis();
     if (currentMillis - previousMillis >= interval) // save the last time you blinked the LED
     { 
      previousMillis = currentMillis; 
      GREENledState = !GREENledState;
      REDledState = !REDledState;
      // if the LED is off turn it on and vice-versa:
      digitalWrite(GREEN_LED, !GREENledState);
      digitalWrite(RED_LED, !REDledState);
      }
  }
  
void setup()
{
  Serial.begin(115200); //Setup serial port for debugging our code

  myservo.attach(12);  // attaches the servo on pin 9 to the servo object
  myservo.write(0); //Zero the servo and wait to allow placement of the payload
  Serial.println("Servo Zeroed");
  delay(2000);

int REDledState = HIGH;             
int GREENledState = LOW;

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
  
  // configure LED for output
  pinMode(LED_BUILTIN, OUTPUT); //LED
  
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

 //########################### Pins for Gyro #############################
  
//  pinMode(INTERRUPT_PIN, INPUT);
  
  //########################## Setup for Gyro ############################
  
  // Set up MPU 6050:
  Wire.begin();
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
    
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(115200);
  delay(100);

  //setup starting angle
  //1) collect the data
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)     
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //2) calculate pitch and roll
  double roll = atan2(AcY, AcZ)*degconvert;
  double pitch = atan2(-AcX, AcZ)*degconvert;

  //3) set the starting angle to this pitch and roll
  double gyroXangle = roll;
  double gyroYangle = pitch;
  double compAngleX = roll;
  double compAngleY = pitch;

  //start a timer
  timer = micros();
  
  //old
  // bool gyroInUse = false;
//  if (gyroInUse == true)
//  {
//    // join I2C bus (I2Cdev library doesn't do this automatically)
//    Wire.begin();
//    Wire.setClock(400000); // 400kHz I2C clock.
//    
//    // initialize device
//    Serial.println(F("Initializing I2C devices..."));
//    mpu.initialize();
//
//
//        // verify connection
//    Serial.println(F("Testing device connections..."));
//    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));
//
//    // load and configure the DMP
//    Serial.println(F("Initializing DMP..."));
//    devStatus = mpu.dmpInitialize();
//
//    // supply your own gyro offsets here, scaled for min sensitivity
//    mpu.setXGyroOffset(220);
//    mpu.setYGyroOffset(76);
//    mpu.setZGyroOffset(-85);
//    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
//
//    // make sure it worked (returns 0 if so)
//  
//    if (devStatus == 0) 
//    {
//        // turn on the DMP, now that it's ready
//        Serial.println(F("Enabling DMP..."));
//        mpu.setDMPEnabled(true);
//  
//        // enable Arduino interrupt detection
//        Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
//        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
//        mpuIntStatus = mpu.getIntStatus();
//  
//        // set our DMP Ready flag so the main loop() function knows it's okay to use it
//        Serial.println(F("DMP ready! Waiting for first interrupt..."));
//        dmpReady = true;
//  
//        // get expected DMP packet size for later comparison
//        packetSize = mpu.dmpGetFIFOPacketSize();
//    }
//  
//      else 
//      {
//        // ERROR!
//        // 1 = initial memory load failed
//        // 2 = DMP configuration updates failed
//        // (if it's going to break, usually the code will be 1)
//        Serial.print(F("DMP Initialization failed (code "));
//        Serial.print(devStatus);
//        Serial.println(F(")"));
//      }
// 
////  gyroCalibrate(); //Settle the gyro with a ten second wait  
//
//  
//  }
  
}

void servoMove(byte pos)
{
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500);    
}



//    static int    SubLoop, Demand;
//    static byte   Moving, CMDBuff[256], CurrentCMD;
//    static float  Heading,HeadingTgt;
//    static byte Command;
//    float Reduction;
//    int i;
//    SubLoop++;
//
//      
//    // if programming failed, don't try to do anything
//    if (!dmpReady) return;
//
//    // *********************************************************************
//    // ** 100Hz Fast Loop                                                 **
//    // *********************************************************************
//    
//    // wait for MPU interrupt or extra packet(s) available
//    while (!mpuInterrupt && fifoCount < packetSize) 
//    {
//       
//    }
//    
////    ButtonSounder(&Command);                                          // @SM clear cmd msg here when done
//    GetHeading(&Heading,&HeadingTgt, Moving);                         // Get heading
//    if((CurrentCMD == LEFT) || (CurrentCMD == RIGHT) || (CurrentCMD == GO) )    // We seem to need more gain when the robot is moving? and less when stationary.
//      Reduction = .3; // lower gain required
//    else
//      Reduction=1; 
//      
//    PID(Heading,HeadingTgt,&Demand,Reduction * 15,Reduction * .08,0,Moving);  // If not moving zero integral
//  
//
//    // *********************************************************************
//    // ** 10Hz Loop                                                      **
//    // *********************************************************************
//    if((SubLoop % 2) == 0)
//    {
//        // Get user command
////        DecodeUserSwitch(&Command,Moving,&CurrentCMD);      // @SM read ADC allways & decode to an integer; if driving this is lost else it's compiled.
//                                                            // Elsewhere it's turned to a sound.  Allways writes to Command                                                            
//        //Get system gen commands
//        CheckIMU(&Command,Heading);                         // Look to see when the IMU has warmed up, issue a CMD when it has otherwise prevent start
//        CrashDetect(CurrentCMD, Moving, &Command);         // detect a crash with IR sensor
//        
//        // store / recall commands
////        CompileUserCommands(CMDBuff,Command,&Moving);       // if not moving then compile. set moving when asked append  as last CMD
//                                                            // [#CMDS] [CMD1] [CMD2] ..... [GO]  (go allways at end)
//                                                            //HDG is +/- 180
//                                                            
////        PullNextUserCommand(CMDBuff, Moving, &CurrentCMD);  // @SM if moving then execute next command 
//
//        //Execute commads
////        ExecuteCommand(&CurrentCMD,&Moving,&HeadingTgt,Demand,Command);// @SM takes several seconds to move the robot with a state machine
//                                                            // read CMD , then execute CMD in background.  For turn this is a modification of the TGT then a wait
//                                                            // when a CMD has executed set it to NEXT_CMD so above code pulls next CMD
//                                                            // For FWD the Auto head demands are offset FWD or back.  
//                                                            // The Last CMD is allways "END" which which turns off motors and clears moving 
//                                                            // drivemotors allways does auto HDG when Moving!!                                                                 
//    }//END 10HZ
//
//    // blink LED to indicate activity
//    if((SubLoop % 100) == 0)
//    {   
//        blinkState = !blinkState;
//        digitalWrite(LED_BUILTIN, blinkState);
//    }
//    
//}//END Loop
//
////
//
//void CheckIMU(byte *Command, float  Heading)
//{
//  static int Init=1,Count;
//  static float oHeading;
//  
//  if(Init)
//  {
//      //If IMU not stable don't allow the robot to start navigating.
//      if(*Command == GO)
//        *Command = NONE;
//      
//      Count++;
//      if(Count==100)
//      {
//        Count = 0; 
//        if(abs(Heading - oHeading) < 1)
//        {
//          Init = 0;    
//           *Command = IMU_WARM;
//        }
//        else
//          oHeading = Heading;
//      }  
//  }
//}//END Check IMU
//
//
//// Read in range finder, if crash likely cancel comamnd and alert user
//void CrashDetect(byte CurrCMD, byte Moving, byte *Command)
//{
//  static int DetectCount;
////Serial.println(  analogRead(1)  );
//  // detect crash only when fwd though!
//  if(Moving && (CurrCMD == UP))
//  {
//    if( analogRead(1) > 550 )
//      DetectCount++;
//    else
//      DetectCount =0;
//  }
//  else
//    DetectCount=0;
//
//  if(DetectCount > 2)
//  {
//    *Command = CRASH;  //Beepola - sim btn press, execute gets this as well so it know to zero the motor demands
//  }
//  
//}//END 
//
////
//// This routine executes the command in *CurrentCMD then zeroes it when done.
//// This only occurs if we are moving otherwise we are in standby.
//
////void ExecuteCommand(byte *CurrentCMD,byte *Moving,float *HeadingTgt,float Demand,byte Command)
////{
////  static byte state;
////  static int ForeDmd,Time;
////  const int ExecuteDelay=80;
////  
////  if(*Moving)
////  {
////    // @@@@@@@@@@ CMD Init @@@@@@@@@@@@@@@@@@@@@@
////    if(state==0) 
////    {
////     
////      switch(*CurrentCMD)
////      {
////        case UP:    ForeDmd = 500;
////                    Time = ExecuteDelay * .7 ;
////                    state++;
////                    break;
////        case DN:    ForeDmd = -400;
////                    Time = ExecuteDelay * .7 ;
////                    state++;
////                    break;
////        case LEFT:  *HeadingTgt -= 90;
////                    Time = ExecuteDelay;
////                    state++;
////                    if(*HeadingTgt < 0) *HeadingTgt += 360;
////                    break;
////        case RIGHT: *HeadingTgt += 90;
////                    Time = ExecuteDelay;
////                    state++;
////                    if(*HeadingTgt > 360) *HeadingTgt -= 360;
////                    break;
////        case GO:    state++;
////                    Time = ExecuteDelay;
////
////                    break;
////        case NONE:
////                    break;  
////      }//END switch
////              
////    }//END IF  
////    // @@@@@@@@@@ CMD Execute @@@@@@@@@@@@@@@@@@@@
////    else 
////    {
////        if(Command == CRASH)
////          ForeDmd=0;
////          
////        // count down them move back to CMD execution state
////        Time--;
////                 
////        if((Time==0) )
////        {
////          //we've reached the end of the program!
////          if(*CurrentCMD == GO)
////          {
////            Serial.println("Go found");
////            *Moving = 0;
////          } 
////          state=0;
////          *CurrentCMD = NONE;
////          ForeDmd = 0;
////        }
////    } 
////    // @@@@@@@@@@ ----------- @@@@@@@@@@@@@@@@@@@@
////    
////  }
////  else
////  {
////     //idle waiting for go cmd
////     state = 0;
////    //NOT Moving
////    ForeDmd = 0;
////  }
////  DriveMotors( (Demand * -1) + ForeDmd,  Demand + ForeDmd, *Moving);
////}//END ExecuteCommand
////
////     
////
//// Pull a command from the buffer if the current command has been executed and 
//// we are moving.
////
////void PullNextUserCommand(byte CMDBuff[],byte Moving, byte *CurrentCMD)  // @SM if moving then execute next command 
////{
////  static byte ptr;
////
////  if(Moving) 
////  {
////    if((*CurrentCMD==NONE) || (*CurrentCMD==CRASH))
////    {    
////        //need a new CMD...
////        if(ptr <= CMDBuff[0])
////        {
////
////           //CMDs still in there
////           *CurrentCMD = CMDBuff[ptr];  
////           CMDBuff[ptr] = 0; // clear to make debugging easier
////           ptr++;
////        }
////        else
////          CMDBuff[0] = 0; //Empty buffer
////    }
////  }//END IF Moving
////  else
////    ptr=1; //set ptr to 1st cmd
////    
////} //END PullNextUserCommand
////
////
////
//// Check to see if the IMU has settled down and is giving a steady heading.  
//// If it hasn't disable the go button.
//
//
//
////
//// A PID implementation; control an error with 3 constants and
//// of 350 as a result of the motor tests.  If not moving do nothing.
//
//void  GetHeading(float *Heading,float *HeadingTgt, byte Moving)               
//{
//
//  {
//      //calc heading from IMU
//      // reset interrupt flag and get INT_STATUS byte
//      mpuInterrupt = false;
//      mpuIntStatus = mpu.getIntStatus();
//
//      // get current FIFO count
//      fifoCount = mpu.getFIFOCount();
//
//      // check for overflow (this should never happen unless our code is too inefficient)
//      if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
//        // reset so we can continue cleanly
//        mpu.resetFIFO();
//        Serial.println(F("FIFO overflow!"));
//
//        // otherwise, check for DMP data ready interrupt (this should happen frequently)
//      } 
//      else if (mpuIntStatus & 0x02) 
//      {
//          // wait for correct available data length, should be a VERY short wait
//          while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
//
//          // read a packet from FIFO
//          mpu.getFIFOBytes(fifoBuffer, packetSize);
//        
//          // track FIFO count here in case there is > 1 packet available
//          // (this lets us immediately read more without waiting for an interrupt)
//          fifoCount -= packetSize;
//          
//          // display Euler angles in degrees
//          mpu.dmpGetQuaternion(&q, fifoBuffer);
//          mpu.dmpGetGravity(&gravity, &q);
//          mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
//          //Serial.print("ypr\t");
//          *Heading = (ypr[0] * 180/M_PI) + 180;
//  
//      }//done
//  }
//  
//  if(!Moving)
//  {     
//      *HeadingTgt=*Heading;
//  } 
//}//END GetHeading
//
//void PID(float Hdg,float HdgTgt,int *Demand, float kP,float kI,float kD, byte Moving)                                                 
//{
//  static unsigned long lastTime; 
//  static float Output; 
//  static float errSum, lastErr,error ; 
//
//  // IF not moving then 
//  if(!Moving)
//  {
//        errSum = 0;
//        lastErr = 0;
//        return;
//  }
//
//  //error correction for angular overlap
//  error = Hdg-HdgTgt;
//  if(error<180)
//    error += 360;
//  if(error>180)
//    error -= 360;
//  
//      
//  //http://brettbeauregard.com/blog/2011/04/improving-the-beginners-pid-introduction/
//
//  /*How long since we last calculated*/
//  unsigned long now = millis();    
//  float timeChange = (float)(now - lastTime);       
//  /*Compute all the working error variables*/
//  //float error = Setpoint - Input;    
//  errSum += (error * timeChange);   
//
//  //integral windup guard
//  LimitFloat(&errSum, -300, 300);
//
//  float dErr = (error - lastErr) / timeChange;       
//
//  /*Compute PID Output*/
//  *Demand = kP * error + kI * errSum + kD * dErr;       
//  /*Remember some variables for next time*/
//  lastErr = error;    
//  lastTime = now; 
//
//  //limit demand 
//  LimitInt(Demand, -400, 400);
//
//}//END PID
//
////
//// Build up a list of commands from the user via the keyboard then
//// when asked initiate the 'moving' sequence.  A cancel command deletes all
//// commands.
//
////void CompileUserCommands(byte CMDBuff[],byte Command,byte *Moving)
////{
////    if(*Moving == 0)
////    {
////      // When static build up an array of commands.  1st byte is # of commands
////      // GO btn executes or can CANCEL commands.  When we get a go then start moving
////      if(Command >= CANCEL )
////      {
////        CMDBuff[0]++;
////        CMDBuff[ CMDBuff[0] ] = Command;
////
////        if(Command == GO)
////        {
////           *Moving = 1;  
////        }
////
////        if(Command == CANCEL)
////        {
////           CMDBuff[0] = 0;
////        }
////      }//END IF
////    }//END IF
////}//END CompileUserCommands
////
//////
////// Use the onboard speaker to issue beepy noises when the user hits
////// buttons.  A noise is also generated by the Bee Bot when the IMU
////// has warmed up
////
////void ButtonSounder(byte *Command)
////{
////    static int state;
////
////    // was a CMD issued?
////    if(*Command > NONE)
////    {
////      if(*Command==CANCEL)
////        state=300;
////      else if (*Command==IMU_WARM)
////        state=100;
////      else if (*Command==CRASH)
////        state=20;
////      else
////        state+=10;
////      
////      *Command = NONE;
////    }
////
////    // toggle DO to make noise
////    if(state>0)
////    {
////      state--;
////      if(state % 2)
////       digitalWrite(12, 1);
////      else
////       digitalWrite(12, 0); 
////    }
////}//END ButtonSounder
//
////
//// Use the IMU to get the curreent heading.  This is 0-360 degrees.
//// It's not relative to North but where the robot was pointing when the
//// GO button was pressed.
//
//
//
//
////
//// Decode the analog keyboard
//
//void DecodeUserSwitch(byte *Command,byte Moving,byte *CurrentCMD)
//{
//    static byte state = 0;
//    static int relcount = 0;
//    static int Anal[5], LastAnal;
//
//    if(Moving)
//      return;
//      
//    Anal[4] = Anal[3];
//    Anal[3] = Anal[2];
//    Anal[2] = Anal[1];
//    Anal[1] = Anal[0];  
//    Anal[0] = analogRead(0);
//
///*  144 dn 6
//    327 up 5
//    0 R 8
//    500 L 7
//    740 Go 9
//    */
//    *Command = NONE;
//    if(state == 0)
//    {
//      relcount=0;
//      //detect btn press by user - try and get rid of mis-read btns
//      if ( InRange(60, -20, Anal[0], Anal[1], Anal[2]) )
//        *Command = RIGHT;
//      else if ( InRange(155, 120, Anal[0], Anal[1], Anal[2]))
//        *Command = DN;
//      else if (InRange(350, 310, Anal[0], Anal[1], Anal[2]))
//        *Command = UP;
//      else if (InRange(520, 480, Anal[0], Anal[1], Anal[2]))
//        *Command = LEFT;
//      else if (InRange(760, 700, Anal[0], Anal[1], Anal[2]))
//        state = 1; //go
//        
//      //normal command entry
//      if(*Command > NONE)
//      {                         //Serial.println("got CMD");
//        state = 2;
//      }
//    }
//    else if(state == 1)
//    {
//      // go/cancel detect, hold btn to cancel else it's a go cmd
//      relcount++; //used as timer
//      //Serial.println(relcount);
//      if(relcount > 200)
//      {
//        *Command=CANCEL;     
//        state=2;
//      }
//
//      if(Anal[0]>800)
//      {
//        *Command=GO;
//        state = 2;
//        *CurrentCMD=NONE; //tells pull to start pulling
//      }
//    }
//    else if(state == 2)
//    {
//      //wait release
//      if(Anal[0] > 800)
//        relcount++;
//      else
//        relcount=0;
//
//      //firm rel
//      if(relcount>10)
//        state=0;
//    }
//
//}//END DecodeUSerSwitch
//
////
////  LimitInt
////  Clamp an int between a min and max.  
//
//void LimitInt(int *x,int Min, int Max)
//{
//  if(*x > Max)
//    *x = Max;
//  if(*x < Min)
//    *x = Min;
//
//}//END LimitInt
//
////
//// Clamp a float between a min and max.  Note doubles are the same 
//// as floats on this platform.
//
//void LimitFloat(float *x,float Min, float Max)
//{
//  if(*x > Max)
//    *x = Max;
//  if(*x < Min)
//    *x = Min;
//
//}//END LimitInt
//
//
////
//// Drive port / stbd motors fwd or backwards using PWM.
//// A breakout calc is needed to linearise the response since
//// torque is proportional to voltage on a DC mottor the wheels
//// don't move on the lower 25% range.
//// 
//// A L9110 IC controls the motors and 2 PWMs are used.  2 DOs control 
//// direction.
//// 
//// IA(DO) IB(PWM) Motor State 
//// L      L       Off 
//// H      L       Forward 
//// L      H       Reverse 
//// H      H       Off 
////
//// Inputs
//// -----
//// DriveVal    +/-1000  
////
//// Note
//// ----
//// Demand>     0  100 200 300 400 500 600 700 800 900 1000
//// Distance>  33  70  93  110 128 140 151 164* 168 168 168
////
//// Motor demands are linear ish up to 700 with AAA hybrio batteries.
//// For PID Distance = 400 and PID gets 300
////
//void DriveMotors(int PDrive,int SDrive,byte Moving)
//{
//  int Mag;
//
//  if(!Moving)
//  {
//    PDrive = 0;
//    SDrive = 0;
//  }
//  
//  LimitInt(&PDrive, -1000,1000);
//  LimitInt(&SDrive, -1000,1000);
//
//  // ========= Port drive =========
//  Mag = abs(PDrive) * .205 + 45;
// if(PDrive == 0) Mag = 0;
//  
//  if(PDrive < 0)
//  {
//    // fwds
//    digitalWrite(9, HIGH);
//    analogWrite(3, 255 - Mag);
//  }
//  else
//  {
//    // backwards
//    digitalWrite(9, LOW);
//    analogWrite(3, Mag);
//  } 
//
//  // ========= Stbd drive =========
//  Mag = abs(SDrive) * .205 + 45;
//  if(SDrive == 0) Mag = 0;
//  
//  if(SDrive < 0)
//  {
//    // 
//    digitalWrite(10, HIGH);
//    analogWrite(11, 255 - Mag); //you haave to do this; look at the truth table
//  }
//  else
//  {
//    // fwd
//    digitalWrite(10, LOW);
//    analogWrite(11, Mag);
//  }  
//}//END DriveMotors
//
////
//// Check if a b & c are in range
//// This is a comparisson function for cleaning up analog inputs
//
//byte InRange(int hi, int lo, int a, int b, int c)
//{
//  if(a<hi && a>lo)
//    if(b<hi && b>lo)
//      if(c<hi && c>lo)
//        return(1);
//
//  return(0);
//}//END InRange
