#include <Keypad.h>
#include <Servo.h> 

Servo servo1; 
int solenoidPin = 4;
const int ROW_NUM = 4; 
const int COLUMN_NUM = 3; 

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte pin_rows[ROW_NUM] = {13, 12, 11, 10}; 
byte pin_column[COLUMN_NUM] = {9, 8, 7}; 

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

const String password = "1961"; 
String input_password;

void setup(){
  Serial.begin(9600);
  input_password.reserve(32); 
  servo1.attach(5);
  servo1.write(0);
  pinMode(solenoidPin, OUTPUT);
}
void loop(){
  char key = keypad.getKey();
  if (key){
    Serial.println(key);
    if(key == '*') {
      input_password = ""; 
    } else if(key == '#') {
      if(password == input_password) {
        Serial.println("password is correct");
        digitalWrite(solenoidPin, HIGH);
        delay(10000); 
        servo1.write(180); 
        delay(5000); 
        servo1.write(0);
        delay(5000);
        digitalWrite(solenoidPin, LOW);
      } else {
        Serial.println("password is incorrect, try again");
      }
      input_password = ""; 
    } else {
 input_password += key; 
 }
 }
}