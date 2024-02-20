// the local header file handles the library and contains project specific, sensor specific code

#ifndef CurrentSensor_h
#define CurrentSensor_h

#include <ACS712.h> // referencing documents/Arduino/library
#include <MBR_MovingAverage.h>

//  Arduino UNO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A

// ACS712(uint8_t analogPin, float volts = 5.0, uint16_t maxADC = 1023, float mVperAmpere = 100);
const int currentSensorPin = A4;
int currentMin = 0; // mA
int currentMax = 10000;
int mA; // current mA

// BDCM
float motorAmps;
float motorVolts = 12.0;
float motorWatts;

// raw
// voltage decreases when current increases
float Vcc = 5.0;
float vRaw;
float vAdjust; // remove 2.5v
float mARaw;
float vOffset = Vcc/2.0;

MBR_MovingAverage currentSensorAvg(20);

ACS712  currentSensor(currentSensorPin, 5.0, 1023, 185);

//  ESP 32 example (might requires resistors to step down the logic voltage)
//  ACS712  ACS(25, 3.3, 4095, 185);

// setup current sensor
void setupCurrentSensor(){
    Serial.println("current Sensor: ACS712");
    pinMode(currentSensorPin, INPUT);
    currentSensor.autoMidPointDC();
    Serial.print("autoMidpoint mA");
    Serial.println(currentSensor.getMidPoint());
}


// bound
int bound(int input, int min, int max){
    if(input < min){
        input = min;
    }
    if(input > max){
        input = max;
    }
    return input;
}


// checkMin
int checkMin(){
    if(mA < currentMin){
        currentMin = mA;
    }
    return currentMin;
}


float readvRaw(){
    vRaw = analogRead(A0) * (5.0/1023.0);
    return vRaw;
}

void readCurrentSensor(){
  mA = currentSensor.mA_DC();               // read current
  mA = bound(mA, currentMin, currentMax);    // bound
  mA = currentSensorAvg.movingAverage(mA);  // find moving average
  motorAmps = mA / 1000.0;
  motorWatts = motorAmps * motorVolts;
}
#endif