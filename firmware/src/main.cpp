#include <Arduino.h>
#include <Servo.h>

Servo s; 
bool flag; 

//Configurable variables 
int neutral_pos; //Neutral position to hold 
int del; //Delay 
int t1; //Target position for "On"
int t2; // Target position for "Off"

//Prototype functions 
void cw(int target);
void ccw(int target);
void neutral();

//Setup function
void setup() {
  Serial.begin(9600);
  flag = false; 
  neutral_pos = 90; 
  del=5;
  t1=80;
  t2=50;
  pinMode(3, INPUT);
  s.attach(2); 
  neutral(); 
}

//Loop function
void loop() {

  if (digitalRead(3) == 0 && !flag){
    cw(neutral_pos+t1); 
    flag = true;
    Serial.print("turn on!"); 
  } 

  if (digitalRead(3) == 0 && flag){
    ccw(neutral_pos-t2); 
    flag = false;
    Serial.print("turn off!"); 
  } 
  
  if (digitalRead(3) == 1){
    neutral();  
  }
}
//Moves the servo clockwise to the absolute target position (target > current position, 0 <= target <= 180)
void cw(int target) {
  int pos = s.read();
  for (int i=pos; i<=target; i++){
    s.write(i);
    delay(del);
  }
}
//Moves the servo counterclockwise to the absolute target position (target < current position, 0 <= target <= 180)
void ccw(int target) {
  int pos = s.read();
  for (int i=pos; i>=target; i--){
    s.write(i);
    delay(del);
  }
}

//Holds the neutral position
void neutral(){
  int pos = s.read();
  if (pos < neutral_pos){
    for (int i=pos; i<=neutral_pos; i++) {
    s.write(i);
    delay(del); 
    }
  }
  if (pos > neutral_pos){
    for (int i=pos; i>=neutral_pos; i--) {
    s.write(i);
    delay(del);
    }
  } 
}


