#include <analogWrite.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_VL53L0X.h"


// Screen Size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

// Reset Pin
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Motor Directions
#define RF 18
#define RB 5
#define LF 16
#define LB 17

//left Sensor(LSP) on analogPin 34
//right Sensor(RSP) on analogPin 39
int leftSensorPin = 34;
int RightSensorPin = 39;

void setup() {
   // Set up Serial Monitor
  Serial.begin(115200);
  
  // Sensor pins are INPUT
  pinMode(leftSensorPin, INPUT);
  pinMode(RightSensorPin, INPUT);

  //Motor pins are OUTPUT
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);

  // Set up display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  //display.clearDisplay();

  // Wait until the serial port opens for native USB devices
  while (!(Serial))
  {
    delay(1000);
  }

  if (!(lox.begin()))
  {
    Serial.println(F("Failed to boot VL53L0X"));

    while (true);
  }

  delay(1000);
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  lineFollowing();

}


void lineFollowing(){
  
int leftSensor = digitalRead(leftSensorPin);
int RightSensor = digitalRead(RightSensorPin);

  //check if both sensors are on white
  if (leftSensor == 0 && RightSensor == 0 )
  {
      analogWrite(RF, 150);//150
      analogWrite(LF, 165);//165
      analogWrite(RB, 0);
      analogWrite(LB, 0);
      display.println("Forward");
      delay(20);
  }
  
  else if (leftSensor == 0 && RightSensor == 1)
  {
      analogWrite(RF, 120);//120
      analogWrite(LF, 0);
      analogWrite(RB, 0);
      analogWrite(LB, 105);//105
      display.println("Turn to the left");
      display.display(); 
  }
  //Check if right sensor is on black
  else if (leftSensor == 1 && RightSensor == 0)
  {
      analogWrite(RF, 0);
      analogWrite(LF, 120);//120
      analogWrite(RB, 105);//105
      analogWrite(LB, 0);
      display.println("Turn to the right");
      delay(20);
   
  }
  
  else if (leftSensor == 1 && RightSensor == 1)
  {
  analogWrite(RF, 0);
  analogWrite(LF, 0);
  analogWrite(RB, 0);
  analogWrite(LB, 0);
  display.println("Stop");
  display.display();
  }
}


//void stopMotor() {
//  analogWrite(RF, 0);
//  analogWrite(LF, 0);
//  analogWrite(RB, 0);
//  analogWrite(LB, 0);
//  display.println("Stop");
//  display.display();
//}
//
//void turnRight(){
//      analogWrite(RF, 0);
//      analogWrite(LF, 120);//120
//      analogWrite(RB, 105);//105
//      analogWrite(LB, 0);
//      display.println("Turn to the right");
//      display.display();
//}
//
//void turnLeft(){
//      analogWrite(RF, 120);//120
//      analogWrite(LF, 0);
//      analogWrite(RB, 0);
//      analogWrite(LB, 105);//105
//      display.println("Turn to the left");
//      display.display();
//}
//
//void forward(){
//      analogWrite(RF, 150);//150
//      analogWrite(LF, 165);//165
//      analogWrite(RB, 0);
//      analogWrite(LB, 0);
//      display.println("Forward");
//      display.display();
//}
