/*
Blue robotics thruster controller
Matt Pfeiffer 24.02.17

Notes:
- Must reset micro at right time to upload WFT
- Depower Nano then upload new code
*/

#include "OLED.h"
#include "Pot.h"
#include "ESC.h"
#include "LED.h"
#include "CurrentSensor.h"

String fileName = "ThrusterController.ino";
String boardType = "Micro";
String gitHub = "github: matteblackrobotics/ThrusterController";
int mode = 1;

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
  setupOLED();
  setupCurrentSensor();
}

void loop() 
{
  switch (mode)
  {
  case 1:
    // ------------- input ------------ //
    potRaw = pot1.readRaw();  // read potentiometer raw values
    pwm = map(potRaw, potRawMin, potRawMax, pwmMinLimit, pwmMaxLimit);  // map potentiometer to pwm signal for ESC for thruster motor
    potNorm = map(potRaw, potRawMin, potRawMax, potNormMin, potNormMax); // map raw potentiometer to normalized values
    readCurrentSensor();

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
      int blue = map(pwm, pwmMaxDeadband, pwmMin, ledMin, ledMax);
      ledStrip1.setPixelColor(0,0,0,blue); // map pwm to blue
      ledDisplay = blue;
    }

    else{
      motorState = "Stop";
      int red = ledMin;
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
