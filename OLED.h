#ifndef OLED_H
#define OLED_H

// https://learn.adafruit.com/monochrome-oled-breakouts/overview

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// import variables from beyond
extern String BDCMname;
extern float signalDamper;
extern String boardType;
extern String currentSensorName;
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


// chart OLED
char actualThickness;
OLED_SSD1306_Chart display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupOLED()
{
  display1.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  display1.clearDisplay();
  display1.setTextSize(1);
  display1.setTextColor(WHITE);
  display1.setCursor(0,0);
  display1.println(fileName);
  display1.println(boardType);
  display1.println(currentSensorName);
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
  display1.println("Pot to mid pwm...");
  display1.println("for BDCM start.");
  display1.display();
  delay(2000);

  display1.clearDisplay();
  display1.setCursor((SCREEN_WIDTH/2)-28, (SCREEN_HEIGHT/2) - 5);
  display1.println("nice");
  display1.display();
  delay(500);
  display1.clearDisplay();
  display1.display();
}

void displayChart(){
  display1.setChartCoordinates(0, 60);      //Chart lower left coordinates (X, Y)
  display1.setChartWidthAndHeight(123, 55); //Chart width = 123 and height = 60
  display1.setXIncrement(5);                //Distance between Y points will be 5px
  display1.setYLimits(50, 100);             //Ymin = 0 and Ymax = 100
  display1.setYLimitLabels("50", "100");    //Setting Y axis labels
  display1.setYLabelsVisible(true);
  display1.setAxisDivisionsInc(12, 6);    //Each 12 px a division will be painted in X axis and each 6px in Y axis
  display1.setPlotMode(SINGLE_PLOT_MODE); //Set single plot mode
  // display.setPointGeometry(POINT_GEOMETRY_CIRCLE);
  actualThickness = NORMAL_LINE;
  display1.setLineThickness(actualThickness);
  display1.drawChart(); //Update the buffer to draw the cartesian chart
  display1.display();
}

#endif
