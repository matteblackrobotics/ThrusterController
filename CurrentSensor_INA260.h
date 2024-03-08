#ifndef CurrentSensor_INA260_h
#define CurrentSensor_INA260_h

#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260();
String powerSensorName = "INA260";
float INA_voltage; // [V]
float INA_current;  // [A]
float INA_power;  // [W]


// moving average
#include <MBR_MovingAverage.h>
MBR_MovingAverage avgCurrent(25);
MBR_MovingAverage avgVoltage(25);
MBR_MovingAverage avgPower(25);


void setupINA260(){
  if (!ina260.begin()) {
    Serial.println(F("Couldn't find INA260 chip"));
    // while (1);
  }
  Serial.println(F("Found INA260 chip"));  
}

void read_INA260(){
  int counter = 0;
  int counterMax = 100;

  INA_current = 0.0f;
  INA_voltage = 0.0f;
  INA_power = 0.0f;

  while (counter < counterMax) {
   INA_current += ina260.readCurrent();
   INA_voltage += ina260.readBusVoltage();
   INA_power += ina260.readPower();
   counter++;
   delay(1);
  }

  INA_current /= (float)counter;
  INA_voltage /= (float)counter;
  INA_power /= (float)counter;

  // convert from mUnits
  INA_current = INA_current / 1000.0;
  INA_voltage = INA_voltage / 1000.0;
  INA_power = INA_power / 1000.0;
}

void read_INA260_MovingAverage(){
  INA_current = avgCurrent.movingAverage(ina260.readCurrent())/ 1000.0; // divide after
  INA_voltage = avgVoltage.movingAverage(ina260.readBusVoltage())/ 1000.0;  // divide after
  INA_power = avgPower.movingAverage(ina260.readPower()/ 1000.0); // divide before moving average
}

#endif
