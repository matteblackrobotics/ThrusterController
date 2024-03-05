#ifndef CurrentSensor_INA260_h
#define CurrentSensor_INA260_h

#include <Adafruit_INA260.h>

Adafruit_INA260 ina260 = Adafruit_INA260();

void setupINA260(){
  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    // while (1);
  }
  Serial.println("Found INA260 chip");  
}

void read_INA260(){
   // mA = ina260.readCurrent();
    // volt = ina260.readBusVoltage();
    // power = ina260.readPower();
}

#endif

