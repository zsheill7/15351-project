// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

// If your 32x32 matrix has the SINGLE HEADER input,
// use this pinout:
#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
// If your matrix has the DOUBLE HEADER input, use:
//#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
//#define LAT 9
//#define OE  10
//#define A   A3
//#define B   A2
//#define C   A1
//#define D   A0
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int data;

//int headX;
//int headY;
//int neckX;
//int neckY;
//int rShouX;
//int rShouY;
//int rElboX;
//int rElboY;
//int rHandX;
//int rHandY;
//int pelvX;
//int pelvY;

int headX = 15;
int headY = 5;
int neckX = 15;
int neckY = 9;
int rShouX = 12;
int rShouY = 12;
int rElboX = 8;
int rElboY = 12;
int rHandX = 5;
int rHandY = 14;
int pelvX = 15;
int pelvY = 19;

void setup() {
  Serial.begin(9600);
  matrix.begin();
  

  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

}

void loop() {
  while(Serial.available())
  {
    headX = Serial.readStringUntil('\n').toInt();
    headY = Serial.readStringUntil('\n').toInt();
    neckX = Serial.readStringUntil('\n').toInt();
    neckY = Serial.readStringUntil('\n').toInt();
    rShouX = Serial.readStringUntil('\n').toInt();
    rShouY = Serial.readStringUntil('\n').toInt();
    rElboX = Serial.readStringUntil('\n').toInt();
    rElboY = Serial.readStringUntil('\n').toInt();
    rHandX = Serial.readStringUntil('\n').toInt();
    rHandY = Serial.readStringUntil('\n').toInt();
    pelvX = Serial.readStringUntil('\n').toInt();
    pelvY = Serial.readStringUntil('\n').toInt();
    //Serial.println("reading serial");
    //Serial.println(nose);
    //Serial.println(neck);
    //Serial.println(rShoulder);
    drawFigure(headX, headY, neckX, neckY, rShouX, rShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
    
    
    //drawFigure(headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
    //digitalWrite(13, HIGH);
//    delay (25);
//    drawFigure(headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
//    
  }
  //drawFigure(headX, headY, neckX, neckY, rShouX, rShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
  delay(500);
  //matrix.fillScreen(matrix.Color333(0, 0, 0));
}

void drawFigure (int headX, int headY, int neckX, int neckY, int rShouX, int rShouY, int rElboX, int rElboY, int rHandX, int rHandY, int pelvX, int pelvY){

  // draw figure 1
  //Head
  matrix.fillCircle(headX, headY, 2, matrix.Color333(7, 7, 0));
  //Body
  matrix.drawLine(neckX, neckY, pelvX, pelvY, matrix.Color333(0, 0, 7));
  matrix.drawLine(neckX-1, neckY, pelvX-1, pelvY, matrix.Color333(0, 0, 7));
  matrix.drawLine(neckX+1, neckY, pelvX+1, pelvY, matrix.Color333(0, 0, 7));
  //matrix.fillRect(14, 9, 3, 10, matrix.Color333(0, 0, 7));
  //Right arm
  matrix.drawLine(rHandX, rHandY, rElboX, rElboY, matrix.Color333(7, 3, 3));
  matrix.drawLine(rElboX, rElboY, rShouX, rShouY, matrix.Color333(0, 7, 7));
  matrix.drawLine(rShouX, rShouY, neckX, neckY+2, matrix.Color333(0, 0, 7));
  //matrix.drawLine(16, 14, 2, 10, matrix.Color333(0, 7, 7));
  //Right hand
  matrix.fillCircle(rHandX, rHandY, 1, matrix.Color333(7, 7, 0)); 
  delay(300);

  // fill the screen with 'black'
  //matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay (25);
}
