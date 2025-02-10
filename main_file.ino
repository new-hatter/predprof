#include "AccelStepper.h"

const int dirPin = 3;
const int stepPin = 2;

#define motorInterfaceType 1

AccelStepper myStepper(motorInterfaceType, stepPin, dirPin);

int trigPin = 7; 
int echoPin = 6;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C LCD(0x27,16,2);

#include "SPI.h"
#include "MFRC522.h"

#define RST_PIN 9 
#define SS_PIN  10 

MFRC522 mfrc522(SS_PIN, RST_PIN); 

byte readCard[4];
String cardID = "AC283C2"; 
String tagID = "";
void setup() {
  LCD.init();
  LCD.backlight();
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  myStepper.setMaxSpeed(1000);
  myStepper.setSpeed(200);
  myStepper.moveTo(200000);
  LCD.display();
  LCD.setCursor(1, 0);
  LCD.print("Attach");
  LCD.setCursor(8, 1);
  LCD.print("Card");
  pinMode(10, OUTPUT);
}
void loop() {
  while (getID()) {
    if (tagID == cardID) {
      Serial.println("Access Granted!");
      LCD.setCursor(1, 0);
      LCD.print("Access");
      LCD.setCursor(8, 1);
      LCD.print("Granted");
      myStepper.run();
      delay(5000);
      LCD.clear();
      myStepper.moveTo(-myStepper.currentPosition());
      myStepper.run();
    }
    else {
      Serial.println("Access Denied!");
      LCD.setCursor(1, 0);
      LCD.print("Access");
      LCD.setCursor(8, 1);
      LCD.print("Denied!");
      delayMicroseconds(2000);
      LCD.clear();
    }
    Serial.print("ID: ");
    Serial.println(tagID);
    delay(2000);
    LCD.display();
    LCD.setCursor(1, 0);
    LCD.print("Attach");
    LCD.setCursor(8, 1);
    LCD.print("Card");
  }
}
boolean getID() {
  int duration, cm; 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 

  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH); 

  cm = duration / 58; 

  Serial.print(cm); 
  Serial.println(" cm");

  delay(1000);

  if (! 
mfrc522.PICC_IsNewCardPresent()) 
{
    return false;
  }

  if (! 
mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  tagID = "";
  
  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  if(cm>2&&cm<15){
    tagID.toUpperCase();
    mfrc522.PICC_HaltA();
    return true;
  }
}
