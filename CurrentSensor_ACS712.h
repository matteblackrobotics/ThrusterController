#ifndef CurrentSensor_ACS712_h
#define CurrentSensor_ACS712_h

#include <ACS712.h> // referencing documents/Arduino/library
#include <MBR_MovingAverage.h>

//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A
int currentSensorSelect = 2; // 1 = 5A, 2 = 20A
String currentSensorName = "ACS712-20A";
int currentSensorPin = A4;
float mVperA = 100;

// doesn't work, class instance compiles first and doesn't read mVperA in time
void currentSensorSelector(){
    if (currentSensorSelect == 1){
        currentSensorName = "ACS712 5A";
        mVperA = 185;
    }
    else if(currentSensorSelect == 2){
        currentSensorName = "ACS712 20A";
        mVperA = 100;
    }
    Serial.print("currentSensorSelect = "); Serial.println(currentSensorSelect);
    Serial.print("currentSensorName = "); Serial.println(currentSensorName);
    Serial.print("mVperA = "); Serial.println(mVperA);
}


// ACS712(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023, float mVperAmpere = 100);
int currentMin = 0; // mA
int currentMax = 10000;
int mA; // current mA

// Power Sensor Stuff
float motorAmps;
float motorVolts;
float motorWatts;

// raw
float Vcc = 5.0;
float vRaw;
float vAdjust; // remove 2.5v
float mARaw;
float vOffset = Vcc/2.0;

MBR_MovingAverage currentSensorAvg(30);
ACS712  currentSensor(currentSensorPin, 5.0, 1023, mVperA);

//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

// setupCurrentSensor
void setupCurrentSensor_ACS712(){
    Serial.print("currentSensorName = "); Serial.println(currentSensorName);
    Serial.print("mVperA = "); Serial.println(mVperA);
    pinMode(currentSensorPin, INPUT);
    currentSensor.autoMidPointDC();
    Serial.print("autoMidpoint mA = ");
    Serial.println(currentSensor.getMidPoint());
}


// bound
int bound(int input, int min, int max){
    if(input < min){input = min;}
    if(input > max){input = max;}
    return input;
}


// checkMin
int checkMin(){
    if(mA < currentMin){currentMin = mA;}
    return currentMin;
}


// readCurrentSensor
void readCurrentSensor_ACS712(){
  mA = currentSensor.mA_DC();               // read current
  mA = bound(mA, currentMin, currentMax);    // bound
  mA = currentSensorAvg.movingAverage(mA);  // find moving average
  motorAmps = mA / 1000.0;
  motorWatts = motorAmps * motorVolts;
}
#endif