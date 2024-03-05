/*
Blue robotics thruster controller
Matt Pfeiffer 24.02.17

Notes:
- Must reset micro at right time to upload WTF
- Depower Nano then upload new code
- Make sure autoMidpoint for current sensor reads 511, 9-bit max

Update:
- Reorganize for new sensor and bring global veriables forward to main file


Global Variable:

OLED
Pot
ESC
LED
CurrentSensor_ACS
CurrenSensor_INA

pwm;
damper;
potRaw
BDCM_mA;
BDCM_watts;
BDCM_volts;
*/

#include "OLED.h"
#include "Pot.h"
#include "ESC.h"
#include "LED.h"
#include "CurrentSensor_ACS712.h"
#include "CurrentSensor_INA260.h"

String fileName = "ThrusterController.ino";
String boardType = "Arduino_Micro";
String gitHub = "github: matteblackrobotics/ThrusterController";
int mode = 1; // default mode 1

void setup() 
{
  Serial.begin(115200); delay(200);
  Serial.println();
  Serial.println("ThrusterController.ino");
  Serial.println("Arduino Micro"); delay(200);
  Serial.println("github: matteblackrobotics/ThrusterController"); delay(200);
  Serial.println("Attention: Pot to mid pwm for BDCM start"); delay(1000);
  setupLED();  
  setupPWM();
  setupCurrentSensor_ACS712();
  setupOLED();

  display1.print("autoMidpoint mA = ");
  display1.println(currentSensor.getMidPoint());
  display1.display();
  delay(1000);
}

void loop() 
{
  switch (mode)
  {
  case 1:
    // ------------- input ------------ //
    potRaw = pot1.readRaw();  // read potentiometer raw values
    pwm = map(potRaw, potRawMax, potRawMin, pwmMinLimit, pwmMaxLimit);  // map potentiometer to pwm signal for ESC for thruster motor
    potNorm = map(potRaw, potRawMax, potRawMin, potNormMin, potNormMax); // map raw potentiometer to normalized values
    readCurrentSensor_ACS712();
    // read_INA260();


    // --------------- process ----------- //
    // check against motor deadband, set direction, set led brightness
    if(pwm > pwmMaxDeadband){
      motorState = "Forward";
      int green = map(pwm, pwmMaxDeadband, pwmMax, ledMin, ledMax);
      ledStrip1.setPixelColor(0,0,green,0); // map pwm to green
      ledDisplay = green;
    }

    else if(pwm < pwmMinDeadband){
      motorState = "Reverse";
      int blue = map(pwm, pwmMin, pwmMinDeadband, ledMax, ledMin);
      ledStrip1.setPixelColor(0,0,0,blue); // map pwm to blue
      ledDisplay = blue;
    }

    else{
      motorState = "Stop";
      int red = ledMin;
      ledStrip1.setPixelColor(0,red,0,0);
      ledDisplay = red;
    }

    if(pwm == pwmMid){
      motorState = "STOP";
      int red = ledMax;
      ledStrip1.setPixelColor(0,red,0,0);
      ledDisplay = red;
    }

    // ------------ output ----------- //
    // LED
    ledStrip1.show();

    // ESC and Thruster Motor
    writePWM();

    // OLED
    display1.clearDisplay();
    display1.setCursor(0,0);
    display1.println(BDCMname);
    display1.print("% = "); display1.print(potNorm);
    display1.print(", "); display1.println(motorState);
    display1.print("pwm = "); display1.print(pwm);
    display1.print(", "); display1.println(signalDamper);
    display1.print("A = "); display1.print(motorAmps);
    display1.print(", W = "); display1.print(motorWatts);
    display1.display();

    // Serial Monitor
    Serial.print("  potNorm = "); Serial.print(potNorm);
    Serial.print("  motorState = "); Serial.print(motorState);
    Serial.print("  pwm = "); Serial.print(pwm);
    Serial.print("  led = "); Serial.print(ledDisplay);
    Serial.print("  A = "); Serial.print(motorAmps);
    Serial.print("  W = "); Serial.print(motorWatts);
    Serial.println();
  break;
  
  default:
  break;
  }
}
