#ifndef OLED_H
#define OLED_H

// https://learn.adafruit.com/monochrome-oled-breakouts/overview

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OLED_SSD1306_Chart.h>

// import variables from beyond
extern String BDCMname;
extern float signalDamper;
extern String boardType;
// extern String currentSensorName;
extern String fileName;
extern String gitHub;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// UNO:       A4(SDA), A5(SCL)
// MEGA 2560: 20(SDA), 21(SCL)
// LEONARDO:   2(SDA),  3(SCL)
// Nano:      4(SDA), 5(SCL)
// Micro:     3(SCL), 2(SDA)
// ESP8266 - Silk: D2 / GPIO: 4 (SDA), Silk D1 / GPIO: 5 (SCL)

// Note:
// OLED takes up RAM, if board doesn't have enough ram, OLED will not setup or display
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display1(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupOLED()
{
  display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0,0);
  display1.println(fileName);
  display1.println(boardType);
  //display1.println(currentSensorName);
  display1.println(BDCMname);
  display1.display();
  delay(2000);

  display1.clearDisplay();
  display1.setCursor(0,0);
  display1.println(gitHub);
  display1.display();
  delay(1000);
  
  display1.clearDisplay();
  display1.setCursor(0,0);
  display1.println(F("Pot to mid pwm..."));
  display1.println(F("for BDCM start."));
  display1.display();
  delay(2000);

  display1.clearDisplay();
  display1.setCursor((SCREEN_WIDTH/2)-28, (SCREEN_HEIGHT/2) - 5);
  display1.println(F("nice"));
  display1.display();
  delay(500);
  display1.clearDisplay();
  display1.display();
}


#endif
