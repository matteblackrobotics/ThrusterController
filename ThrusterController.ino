// Blue robotics thruster controller
// Matt Pfeiffer 24.02.17

#include "OLED.h"
#include "Pot.h"
#include "ESC.h"
#include "LED.h"

int mode = 1;
String state;

void setup() 
{
  Serial.begin(115200); delay(200);
  Serial.println();
  Serial.println("ThrusterController.ino"); delay(200);
  Serial.println("github: matteblackrobotics/ThrusterController"); delay(200);
  Serial.println("Attention: Pot to mid pwm for BDCM start"); delay(1000);
  setupLED();
  setupPWM();
  setupOLED();
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

    // --------------- process ----------- //
    // check against motor deadband, set direction, set led brightness
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
    display1.print(", "); display1.println(state);
    display1.print("pwm = "); display1.print(pwm);
    display1.print(", "); display1.println(signalDamper);

    display1.display();

    // Serial Monitor
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
