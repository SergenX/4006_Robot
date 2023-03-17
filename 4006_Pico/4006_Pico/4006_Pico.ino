#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h> //(not used) 22 21 I2C0 //(used 1 ı2c 2 device) 4 5 I2C1 
#include <Adafruit_GFX.h>
UART Serial2(4,5); //UART 4 , 5 UART //UART 0 NOT USED
//****************************OLED SCREEN****************************//
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET   -1  
#define SCREEN_ADDRESS 0x3C
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
unsigned long TimeRepair = 0; //4000 hours 
//****************************RTC**********************************//
//**************************Pin Const***********************************//
const int  Buzzer = 6,IN1 = 10,IN2 = 11,IN3 = 12,IN4 = 13,S1 = 14,S2= 15,S3 = 18,S4 = 19; bool ControlActive;  char Snap = 'S';
//Timing Task Variables
  unsigned long currentMilis = 0; unsigned long PreviousMilis = 0;
  unsigned long task_20msn = 1; uint8_t  task  = 1; 
  uint16_t delay_S1,delay_S2,delay_S3,delay_S4; 
void setup() {
   if (!mpu.begin())                                  
        Serial2.println("Failed to find Gyro chip");
        buzzer(5);
    else
    {
        Serial2.println("Gyro Begin...."); 
       
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);   // set accelerometer range to +-8G 
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);        // set gyro range to +- 500 deg/s  
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);     // set filter bandwidth to 21 Hz
    }
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { Serial2.println(F("Oled failed")); buzzer(3);}
  Serial2.begin(9600);
  delay_S1 = 1500, delay_S2 = 2500;
  Servo();
  //MotorControl
  for(int i = 0 ; i <= 100; i++) {
    motorControl(-i,i);
  }
  for(int i = 0 ; i <= 100; i++) {
    motorControl(i,-i);
  }
  pinMode(Buzzer,OUTPUT);
  pinMode(S1,OUTPUT); pinMode(S2,OUTPUT); pinMode(S3,OUTPUT); pinMode(S4,OUTPUT); 
  pinMode(IN1,OUTPUT); pinMode(IN2,OUTPUT); pinMode(IN3,OUTPUT); pinMode(IN4,OUTPUT);
  buzzer(1);
  delay(50);
  display.clearDisplay(); display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);display.setCursor(40,30);             
  display.println("System Ready!"); display.display();
}
void loop() {
timingControl();
  if(Serial2.available()>0){
    char gelen;
    gelen = Serial2.read();
    if(ControlActive == 1) {
    if(gelen == 'F')
        motorControl(255,255);
    if(gelen == 'B')
        motorControl(-255,-255);
    if(gelen == 'R')
        motorControl(-255,255);
         delay_S3 = 1500;
    if(gelen == 'L')
        motorControl(255,-255);
        delay_S3 = 2500;
    if(gelen == 'S')
        motorControl(0,0);
    //Servo Controls
    if(gelen == 'D') { //box
        ControlActive = 0;
          delay_S1 = 2500; 
      }
    if(gelen == 'd') {
      ControlActive = 0;
          delay_S1 = 1500;
      }
    if(gelen == 'U') { //legs
    ControlActive = 0;
        delay_S2 = 2500;
     }
    if(gelen == 'u') { //legs
    ControlActive = 0;
        delay_S2 = 1500;
     }
    }
     if(gelen == '0') {
      ControlActive = 0;
       buzzer(2);
      } 
        if(gelen == '1') {
       buzzer(1);
       ControlActive = 1;
      }
    }
    else 
    return;
}
void timingControl(){
  if( ( unsigned long )( currentMilis - PreviousMilis ) >= 20 ) {
     if( task_20msn++ == 20 ) {//20*50 = 1second 200MS OLED control 
       if(mpu.begin()) {
         Gyro();
       }
    } 
     if(task_20msn++ == 50) {
       if(display.begin()) {
         FaceControl(Snap);
       }
       TimeRepair++;
       if(TimeRepair == 15552000) {//4320 hours
        Snap = 'R';
        ControlActive = 0;
      }
    }
   Servo();
  currentMilis = PreviousMilis;
 }
}