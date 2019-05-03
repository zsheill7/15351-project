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

void setup() {

  Serial.begin(9600);
  Serial.println("<Arduino is ready>");
  
  matrix.begin();
  

  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

}

void loop() {

  recvWithStartEndMarkers();
  showNewData();

//          head   neck   Shou    Elbo     Hand    Pelv
//drawFigure (15, 5, 15, 9, 12, 12, 10, 12, 6, 14, 15, 19);
//delay (25);
//drawFigure (15, 6, 15, 10, 12, 13, 11, 11, 7, 10, 17, 19);
//delay (25);
//drawFigure (15, 7, 15, 11, 12, 14, 11, 10, 8, 7, 20, 19);
//delay (25);
//drawFigure (15, 8, 16, 12, 13, 15, 12, 9, 10, 5, 22, 20);
//delay (500);

//          head   neck    Shou    Elbo   Hand    Pelv
//drawFigure (15, 5, 15, 9, 12, 12, 8, 12,  5, 14, 15, 19);
//delay (25);
//drawFigure (15, 5, 15, 9, 12, 12, 10, 11, 6, 10, 15, 19);
//delay (25);
//drawFigure (16, 5, 16, 9, 13, 11, 9, 8,   7, 5,  15, 19);
//delay (25);
//for (int i = 0; i < 5; i++){
  //drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  9, 3,  15, 19);
  //delay (10);
  //drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  8, 4,  15, 19);
  //delay (10);
  //drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  7, 5,  15, 19);
  //delay (10);
  //drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  6, 6,  15, 19);
  //delay (10);
  //drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  7, 5,  15, 19);
  //delay (10);
  //drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  8, 4,  15, 19);
  //delay (10);
//}
//delay (500); 
  
}
const byte numChars = 32;  //TODO: check if this restricts length of string
char receivedChars[numChars];

boolean newData = false;

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
 // if (Serial.available() > 0) {
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setCursor(1, 0);    // start at top left, with one pixel of spacing
        matrix.setTextSize(1);     // size 1 == 8 pixels high
        matrix.setTextWrap(true); // wrap text

        matrix.setTextColor(matrix.Color333(7,7,7));
        //matrix.print("D:");
        matrix.println(receivedChars);
              
        //Serial.print("This just in ... ");
        Serial.println(receivedChars);
        newData = false;
    }
}

void drawFigure (int headX, int headY, int neckX, int neckY, int rShouX, int rShouY, int rElboX, int rElboY, int rHandX, int rHandY, int pelvX, int pelvY){

  // draw figure 1
  //Head
  matrix.fillCircle(headX, headY, 4, matrix.Color333(7, 7, 0));
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
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay (25);
}
