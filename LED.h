#ifndef LED_h
#define LED_h

#include <Adafruit_NeoPixel.h>
#define ledPin 5
#define numLeds 1

int ledIndex = 0;
int R; // [0:255]
int G;
int B;

int ledMin = 20;    // brightness min
int ledMax = 255;   // brightness max
int ledDisplay;     // value to display brightness of color that is on

// int brightness;
Adafruit_NeoPixel ledStrip1(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void ledYellow(){
  int r = 100;
  int g = 100;
  int b = 0;
  ledStrip1.setPixelColor(0,r,g,b);
  ledStrip1.show();
}

void setupLED()
{
  ledStrip1.begin();
  ledStrip1.setBrightness(100); //adjust brightness here
  ledStrip1.show(); // Initialize all pixels to 'off'
  ledYellow();
  delay(100);
  ledStrip1.clear();
  ledStrip1.show();
}

#endif
