#ifndef LED_h
#define LED_h

#include <Adafruit_NeoPixel.h>
#define ledPin 5
#define numLeds 1

int ledIndex = 0;
int R; // [0:255]
int G;
int B;

int ledMin = 20;
int ledMax = 255;
int ledDisplay;

// int brightness;
Adafruit_NeoPixel ledStrip1(numLeds, ledPin, NEO_GRB + NEO_KHZ800);

void setAll(int R, int G, int B)
{
  for(int i=0; i<numLeds; i++) {ledStrip1.setPixelColor(i,R,G,B);}  
}

void ledOff()
{
  ledStrip1.clear();
  //for(int i=0; i<numLeds; i++) {ledStrip1.setPixelColor(i, 0, 0,0);}
  //ledStrip1.show();
}

void ledRed()
{
  ledOff();
  setAll(50,0,0);
  ledStrip1.show();
}

void ledGreen()
{
  ledOff();
  setAll(0,50,0); 
  ledStrip1.show();
}

void ledBlue()
{
  ledOff();
  setAll(0,0,50);
  ledStrip1.show();
}

void ledLightBlue()
{
  ledOff();
  setAll(0,30,50); 
  ledStrip1.show();
}

void ledWhite()
{
  ledOff();
  setAll(5,50,50); 
  ledStrip1.show();
}

void ledYellow()
{
  ledOff();
  setAll(50,50,0); 
  ledStrip1.show();
}

void ledPurple()
{
  ledOff();
  setAll(50,0,50);
  ledStrip1.show();
}

void ledBrown()
{
  ledOff();
  setAll(102, 51,0);
  ledStrip1.show();
}

void setupLED()
{
  ledStrip1.begin();
  ledStrip1.setBrightness(100); //adjust brightness here
  ledStrip1.show(); // Initialize all pixels to 'off'
  ledRed(); delay(100);
  ledOff();
}

#endif
