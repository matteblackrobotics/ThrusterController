#ifndef SERVOMOTOR_H
#define SERVOMOTOR_H


// Mechancially attach the servo lever beyond its mechancial 0 point 
// Then set the offest to tighten it up at higher resolution to actual 0

#include <Servo.h>
Servo servo1;
const int servoPin = 2;
const int degMin = 0;
// const int degMax = 180;
const int degMax = 120;
int deg = 0;
int degTarget = 0; // need to deal with targetting
int degLast = 0;
int step = 1;

int servoMosfetPin = 3;
bool servoPowerState = 0;

void servoOn(){
  digitalWrite(servoMosfetPin, HIGH);
  servoPowerState = 1;
}

void servoOff(){
  digitalWrite(servoMosfetPin, LOW);
  servoPowerState = 0;
}

void setupServo()
{
  pinMode(servoMosfetPin, OUTPUT);
  servoOn();
  servo1.attach(servoPin);
  Serial.println("setupServo");
}

void writeServoDeg(float input)
{
  deg = map(input, 0, 100, degMin, degMax);
  servo1.write(deg);
  //Serial.print(" deg: "); Serial.print(deg);
}

void sweepServo(int deg1, int deg2, int delay1)
{
  int dir;
  int delta = deg2-deg1;
  if(deg2 > deg1) {dir = 1;}
  else(dir = -1);
  Serial.print("deg1: "); Serial.print(deg1);
  Serial.print("  deg2: "); Serial.print(deg2);
  Serial.print("  delta: "); Serial.print(delta);
  Serial.print("  dir: "); Serial.println(dir);
  for(int i = deg1; i <= abs(delta) && i >= 0; i = i + 1*dir)
  {
    servo1.write(i);
    Serial.println(i);
    delay(delay1);
  }
  Serial.println("sweep end");
}

void motionSweep(){
  servoOn();
  sweepServo(degMin, degMax, 100);
  servoOff();
  delay(2000);
  servoOn();
  sweepServo(degMax, degMin, 100);
  servoOff();
  delay(2000);
}


int stepInput(int current, int target, int step){
  degLast = current;
  if(target > current){
    current = current + step;
  }
  else if(target < current){
    current = current - step;
  }
  else{
    current = target;
  }
  return current;
}
#endif
