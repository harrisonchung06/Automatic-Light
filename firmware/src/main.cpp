#include <Arduino.h>
#include <Servo.h>

Servo s; 
bool flag; 
int neutral_pos;

void cw(int target);
void ccw(int target);
void neutral();

void setup() {
  Serial.begin(9600);
  flag = false; 
  neutral_pos = 90; 
  pinMode(3, INPUT);
  s.attach(2); 
  neutral(); 
}

void loop() {

  if (digitalRead(3) == 0 && !flag){
    cw(neutral_pos+40); 
    flag = true;
    Serial.print("turn on!"); 
  } 

  if (digitalRead(3) == 0 && flag){
    ccw(neutral_pos-60); 
    flag = false;
    Serial.print("turn off!"); 
  } 
  
  if (digitalRead(3) == 1){
    neutral();  
  }
}

void cw(int target) {
  int pos = s.read();
  for (int i=pos; i<=target; i++){
    s.write(i);
    delay(5);
  }
}

void ccw(int target) {
  int pos = s.read();
  for (int i=pos; i>=target; i--){
    s.write(i);
    delay(5);
  }
}

void neutral(){
  int pos = s.read();
  if (pos < neutral_pos){
    for (int i=pos; i<=neutral_pos; i++) {
    s.write(i);
    delay(5); 
    }
  }
  if (pos > neutral_pos){
    for (int i=pos; i>=neutral_pos; i--) {
    s.write(i);
    delay(5);
    }
  } 
}


