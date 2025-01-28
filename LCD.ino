#include <Keypad.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
 {'1','2','3', 'A'},
 {'4','5','6', 'B'},
 {'7','8','9', 'C'},
 {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);

  pinMode(9, INPUT);          
  digitalWrite(9, HIGH);
  pinMode(8, INPUT);          
  digitalWrite(8, HIGH); 
  pinMode(7, INPUT);          
  digitalWrite(7, HIGH); 
  pinMode(6, INPUT);          
  digitalWrite(6, HIGH); 
  pinMode(5, INPUT);          
  digitalWrite(5, HIGH); 
  pinMode(4, INPUT);          
  digitalWrite(4, HIGH); 
  pinMode(3, INPUT);          
  digitalWrite(3, HIGH);  
  pinMode(2, INPUT);          
  digitalWrite(2, HIGH); 
}

void loop(){
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
 }
}
