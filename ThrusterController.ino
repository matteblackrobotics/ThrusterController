// Blue robotics thruster controller
// Matt Pfeiffer 24.02.17

#include "OLED.h"
#include "Pot.h"
#include "PWM.h"
#include "LED.h"

int mode = 1;
String state;

void setup() 
{
  Serial.begin(115200); delay(200);
  Serial.println();
  Serial.println("ThrusterController.ino");
  Serial.println("github: matteblackrobotics/MBR_Pot");
  Serial.println("set pwm to middle of the pwm band to initiate BDCM");
  setupOLED();
  setupLED();
  displayFileName();
  setupPWM();
  delay(1000);
}

void loop() 
{
  switch (mode)
  {
  case 1:
    potRaw = pot1.readRaw();
    pwm = map(potRaw, potRawMin, potRawMax, pwmMin, pwmMax);
    potNorm = map(potRaw, potRawMin, potRawMax, potNormMin,potNormMax);

    if(pwm > pwmMaxDeadband){
      state = "Forward";
      int g = map(pwm, pwmMaxDeadband, pwmMax, ledMin, ledMax);
      ledStrip1.setPixelColor(0,0,g,0); // map pwm to green
      ledDisplay = g;
    }

    else if(pwm < pwmMinDeadband){
      state = "Reverse";
      int b = map(pwm, pwmMaxDeadband, pwmMin, ledMin, ledMax);
      ledStrip1.setPixelColor(0,0,0,b); // map pwm to blue
      ledDisplay = b;
    }

    else{
      state = "Stop";
      int r = ledMin;
      ledStrip1.setPixelColor(0,r,0,0);
      ledDisplay = r;
    }

    ledStrip1.show();
    writePWM();
    display1.clearDisplay();
    display1.setCursor(0,0);
    display1.print("% = "); display1.print(potNorm);
    display1.print(", "); display1.println(state);
    display1.print("pwm = "); display1.println(pwm);
    display1.print("led = "); display1.println(ledDisplay);
    display1.display();

    Serial.print("  potNorm = "); Serial.print(potNorm);
    Serial.print("  state = "); Serial.print(state);
    Serial.print("  pwm = "); Serial.print(pwm);
    Serial.print("  led = "); Serial.print(ledDisplay);
    Serial.println();
  break;
  
  default:
  break;
  }
 
}
