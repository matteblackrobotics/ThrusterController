#ifndef OLED_H
#define OLED_H

// https://learn.adafruit.com/monochrome-oled-breakouts/overview

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern String BDCMname;
extern float signalDamper;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
// On an arduino Nano:      4(SDA), 5(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void showDisplay1()
{
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0,0);
}

void setupOLED()
{
  display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0,0);
  display1.println("ThrusterController.ino");
  display1.display();
  delay(500);

  display1.clearDisplay();
  display1.setCursor(0,0);
  display1.println("github: matteblackrobotics/ThrusterController");
  display1.display();
  delay(500);
  
  display1.clearDisplay();
  display1.setCursor(0,0);
  display1.println("Pot to mid pwm...");
  display1.println("for BDCM start.");
  display1.display();
  delay(2000);

  display1.clearDisplay();
  display1.setCursor((SCREEN_WIDTH/2)-28, (SCREEN_HEIGHT/2) - 5);
  display1.println("fuck yea");
  display1.display();
  delay(50);
}


#endif
