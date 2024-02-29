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
int BDCM = 2; // 1 = GOOLRC, 2 = BlueRobotics
String BDCMname;
String motorState;

int pwmPin = 4;
int pwm;    // PWM signal value
int pwmMin; // min possible PWM signal
int pwmMax; // max possible PWM signal
int pwmMid; // middle pwm signal
int pwmMinDeadband; // bottom of deadband
int pwmMaxDeadband; // top of deadband

float signalDamper; // power damping factor
int pwmMinLimit;    // limits signal to motor based off power damper
int pwmMaxLimit;    // limits signal to motor based off power damper

void BDCMselector(){
    if(BDCM == 1){
        BDCMname = "BDCM_GoolRC";
        pwmMin = 1000;
        pwmMax = 2000;
        signalDamper = .1;
        pwmMinDeadband = ((pwmMax+pwmMin)/2)-10;
        pwmMaxDeadband = ((pwmMax+pwmMin)/2)+10;
    }
    else if(BDCM == 2){
        BDCMname = "BDCM_BlueRobotics";
        pwmMin = 1100;
        pwmMax = 1900;
        pwmMinDeadband = 1490;
        pwmMaxDeadband = 1510;
        signalDamper = 1;
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

void printBDCMSelector(){
    Serial.println();
    Serial.print("BDCM = ");Serial.println(BDCMname);
    Serial.print("pwmMin = "); Serial.println(pwmMin);
    Serial.print("pwmMax = "); Serial.println(pwmMax);
    Serial.print("pwmMid = "); Serial.println(pwmMid);
    Serial.print("pwmMinDeadband = "); Serial.println(pwmMinDeadband);
    Serial.print("pwmMaxDeadband = "); Serial.println(pwmMaxDeadband);
    Serial.print("signalDamper = "); Serial.println(signalDamper);
    Serial.print("pwmMinLimit = "); Serial.println(pwmMinLimit);
    Serial.print("pwmMaxLimit = "); Serial.println(pwmMaxLimit);
    delay(1000);
    Serial.println();
    Serial.println();
}

void setupPWM(){
    pinMode(pwmPin, OUTPUT);
    ESC.attach(pwmPin, pwmMin, pwmMax);
    BDCMselector();
    printBDCMSelector();
    //Serial.println("setupServo");
}

#endif