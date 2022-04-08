#include <WiFi.h>
#include <analogWrite.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Adafruit_VL53L0X.h"
#include <Wire.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>
#include <sstream>

//WI-FI
const char* ssid = "Sambal";
const char* pass = "";

//set web server
WiFiServer server (80); 

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

//left Sensor pin(LSP) on analogPin 34
//right Sensor pin(RSP) on analogPin 39
int LSP = 34;
int RSP = 39;




void setup() {
   // Set up Serial Monitor
  Serial.begin(115200);
   
  // Sensor pins are INPUT
  pinMode(LSP, INPUT);
  pinMode(RSP, INPUT);

  //Motor pins are OUTPUT
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);

    // Set up display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

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
  
  //connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


  String payload="";
  int payloadInt= payload.toInt(); //convert payload string to int

void loop() {
  
  VL53L0X_RangingMeasurementData_t measure;
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!
  
//   Check the current connection
  if ((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin("https://battlebot.000webhostapp.com/api.php"); // The URL
    int httpCode = http.GET(); 
    
    if (httpCode > 0) { // Check for the returning code 
        
       
       payloadInt= payload.toInt();
       payload = http.getString();
       //Serial.println("hTTP CODE IS BELOW");
       Serial.println(httpCode);
       //Serial.println("payload IS BELOW");
       Serial.println(payload);
    }
    else 
    {
      Serial.println("Error on HTTP request");
    }
  }
  
      
    switch(payloadInt){
           case 1:
           lineFollowing();
           break;
          
            case 2:
            route();
            break;
      
            case 3:
            stopMotor();
            break;
      
            default:
            stopMotor();
            break;
    }
     //lineFollowing();
}//end of loop

void stopMotor() {
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  digitalWrite(RB, LOW);
  digitalWrite(LB, LOW);
  display.println("Stop");
  display.display();
}

void turnLeft() {
  digitalWrite(RF, HIGH);//120
  digitalWrite(LF, LOW);
  digitalWrite(RB, LOW);
  digitalWrite(LB, HIGH);//105
  display.println("Turn to the left");
  display.display();
  
}

void turnRight() {
  digitalWrite(RF, LOW);
  digitalWrite(LF, HIGH);//120
  digitalWrite(RB, HIGH);//105
  digitalWrite(LB, LOW);
  display.println("Turn to the right");
  display.display();
  
}

void forward() {
  digitalWrite(RF, HIGH);//150
  digitalWrite(LF, HIGH);//165
  digitalWrite(RB, LOW);
  digitalWrite(LB, LOW);
  display.println("Forward");
  display.display();
}

void backward() {
  digitalWrite(RB, HIGH);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(LF, LOW);
  display.println("Backward");
  display.display();
}

//first task, follow the black line
  void lineFollowing(){

    //Read sensor data and store it
      int leftSensor = digitalRead(LSP);
      int RightSensor = digitalRead(RSP);
      
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
      delay(20);
  }
  //Check if right sensor is on black
  else if (leftSensor == 1 && RightSensor == 0)
  {
      analogWrite(RF, 0);
      analogWrite(LF, 120);//120
      analogWrite(RB, 105);//105
      analogWrite(LB, 0);
      display.println("Turn to the right");
      display.display();
   
  }
  
  else if (leftSensor == 1 && RightSensor == 1)
  {
  stopMotor();
  }
  
}


//second task pre-defined route
void route(){
  stopMotor();
  delay(1000);
  forward();//fw
  delay(600);
  turnLeft();
  delay(220);
  forward();
  delay(150);
  stopMotor();
  delay(2000);//fw
  turnLeft();//tl
  delay(200);
  stopMotor();
  delay(2000);//tl
  forward();//fw
  delay(600);
  turnLeft();
  delay(220);
  forward();
  delay(150);
  stopMotor();
  delay(2000);//fw
  turnRight();//tr
  delay(150);
  stopMotor();
  delay(2000);//tr
  forward();//fw
  delay(600);
  turnLeft();
  delay(220);
  forward();
  delay(150);
  stopMotor();
  delay(4000);//fw
  backward();//bw
  delay(600);
  stopMotor();
  delay(2000);//bw
  turnLeft();//tl
  delay(220);
  stopMotor();
  delay(2000);//tl
  backward();//bw
  delay(600);
  stopMotor();
  delay(2000);//bw
  turnRight();//tr
  delay(220);
  stopMotor();
  delay(2000);//tr
  backward();
  delay(600);
  stopMotor();
  delay(2000);//bw
} 
