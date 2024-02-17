/*
Electroinc Speed Controller (ESC)
Ardunio sends Pulse Width Modulated (PWM) signal using the Servo library
Signal goes to ESC to control power to thruster Brushless DC Motor (BDCM)
*/

#ifndef ESC_h
#define ESC_h

#include <Servo.h>
Servo ESC;

// BDCM Selector
int BDCM = 1; // 1 = GOOLRC, 2 = BlueRobotics
String BDCMname;

int pwmPin = 2;
int pwm;    // PWM signal value
int pwmMin; // min possible PWM signal
int pwmMax; // max possible PWM signal
int pwmMid; // middle pwm signal
int pwmMinDeadband; // bottom of deadband
int pwmMaxDeadband; // top of deadband

float signalDamper = .1; // power damping factor
int pwmMinLimit;    // limits signal to motor based off power damper
int pwmMaxLimit;    // limits signal to motor based off power damper

void BDCMselect(){
    if(BDCM == 1){
        BDCMname = "BDCM_GOOLRC";
        pwmMin = 1000;
        pwmMax = 2000;
        pwmMinDeadband = ((pwmMax+pwmMin)/2)-10;
        pwmMaxDeadband = ((pwmMax+pwmMin)/2)+10;
    }
    else if(BDCM == 2){
        BDCMname = "BDCM_BlueRobotics";
        pwmMin = 1100;
        pwmMax = 1900;
        pwmMinDeadband = 1460;
        pwmMaxDeadband = 1540;
    }
    // sets damper on signal to motor
    pwmMid = (pwmMax+pwmMin)/2;
    pwmMinLimit = pwmMid - ((pwmMid - pwmMin) * signalDamper);
    pwmMaxLimit = pwmMid + ((pwmMax - pwmMid) * signalDamper);
}

void writePWM(){
    ESC.writeMicroseconds(pwm);
    //pwm = map(pwm, pwmMin, pwmMax, 0, 180);
    //ESC.write(pwm);
}

void printBDCMSelect(){
    Serial.println();
    Serial.println(BDCMname);
    Serial.print("pwmMin = "); Serial.println(pwmMin);
    Serial.print("pwmMax = "); Serial.println(pwmMax);
    Serial.print("pwmMinDeadband = "); Serial.println(pwmMinDeadband);
    Serial.print("pwmMaxDeadband = "); Serial.println(pwmMaxDeadband);
    Serial.print("signalDamper = "); Serial.println(signalDamper);
    Serial.print("pwmMinLimit = "); Serial.println(pwmMinLimit);
    Serial.print("pwmMaxLimit = "); Serial.println(pwmMaxLimit);
    delay(2000);
    Serial.println();
    Serial.println();
}

void setupPWM(){
    pinMode(pwmPin, OUTPUT);
    ESC.attach(pwmPin, pwmMin, pwmMax);
    BDCMselect();
    printBDCMSelect();
    //Serial.println("setupServo");
}

#endif