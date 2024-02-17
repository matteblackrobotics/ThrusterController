#ifndef PWM_h
#define PWM_h

#include <Servo.h>
Servo ESC;

int pwmPin = 2;

int pwm;
// int pwmMin = 1100;
// int pwmMax = 1900;
int pwmMin = 1000;
int pwmMax = 2000;

int pwmMinDeadband = 1460;
int pwmMaxDeadband = 1540;

void setupPWM(){
    pinMode(pwmPin, OUTPUT);
    ESC.attach(pwmPin, pwmMin, pwmMax);
    //Serial.println("setupServo");
}

void writePWM(){
    ESC.writeMicroseconds(pwm);
    //pwm = map(pwm, pwmMin, pwmMax, 0, 180);
    //ESC.write(pwm);
}




#endif