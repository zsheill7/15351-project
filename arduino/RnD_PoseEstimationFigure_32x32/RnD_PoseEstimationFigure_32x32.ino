// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/products/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#define CS_PIN 10

File file;

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

int headX;
int headY;
int neckX;
int neckY;
int ShouX;
int ShouY;
int rElboX;
int rElboY;
int rHandX;
int rHandY;
int pelvX;
int pelvY;

//This array can capture 3 bodies of 17 parts each
const byte byBodyCount = 3;
const byte byBodyParts = 17;
const byte byBodyLines = 14;
short int arrPartsCapture [3][18][2];

//These variables used for serial to array function
const byte numChars = 3*18*2+1;  //TODO: check if this restricts length of string (It does)
char receivedChars[numChars];
boolean newData = false;

//This array is used to draw up to 14 body lines for up to 3 bodies
const byte byAllBodyLines = byBodyCount * byBodyLines;
short int arrAllBodyLines [byAllBodyLines][2];

//These arrays are used to draw the heads and eyes of our bodies
short int arrHeadCenter [byBodyCount][2];
short int arrEyes [byBodyCount*2][2];

void setup() {

  Serial.begin(9600);
  Serial.println("Arduino ready.");
  //pinMode(13, OUTPUT);
  //digitalWrite(13, LOW);
  
  matrix.begin();


  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

}

void loop() {
 
//readSerialConsecIntegers();
assignSerialToBodyParts();
showNewData();    
    //drawFigure (15, 5, 15, 9, 12, 12, 8, 12,  5, 14, 15, 19);
    //drawFigure(headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
    //digitalWrite(13, HIGH);
//    delay (25);
//    drawFigure(headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
//    

  


delay (500);

}

void readSerialConsecIntegers() {
   while(Serial.available())
  {
    headX = Serial.readStringUntil('\n').toInt();
    headY = Serial.readStringUntil('\n').toInt();
    neckX = Serial.readStringUntil('\n').toInt();
    neckY = Serial.readStringUntil('\n').toInt();
    ShouX = Serial.readStringUntil('\n').toInt();
    ShouY = Serial.readStringUntil('\n').toInt();
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
  }
}


void assignSerialToBodyParts() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
    int iReadToComma;
    byte i=0;
    byte j=0;

    Serial.println("start assignSerialToBodyParts()"); //Debug
 
    while (Serial.available() > 0 && newData == false) {
            
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
              while (i<byBodyCount){
                Serial.print("inside first while loop i = "); //Debug
                Serial.println(i);                            //Debug
                receivedChars[ndx] = rc;
                iReadToComma = Serial.readStringUntil(',').toInt();              
                if (iReadToComma == i){
                    Serial.print("before second while loop i = "); //Debug
                    Serial.println(i);                            //Debug
                    Serial.println(iReadToComma);
                      while (j<byBodyParts){
                        Serial.print("inside second while loop j = "); //Debug
                        Serial.println(j);                            //Debug                        
                        if (Serial.readStringUntil(',').toInt() == j){
                          Serial.println("Writing to array");
                          arrPartsCapture [i][j][Serial.readStringUntil(',').toInt(), Serial.readStringUntil('\n').toInt()];
                          Serial.print("Array: ");
                          Serial.print(i);
                          Serial.print(j);
                          Serial.print(arrPartsCapture [i][j][1]);
                        }
                        else arrPartsCapture [i][j][200,200];
                        j++;
                      } 
                    }
                else i++;{    
                }    
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
              }
            }
            else{    
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
    byte i=0;
    byte j=0;
    
    if (newData == true) {
        matrix.fillScreen(matrix.Color333(0, 0, 0));
        matrix.setCursor(1, 0);    // start at top left, with one pixel of spacing
        matrix.setTextSize(1);     // size 1 == 8 pixels high
        matrix.setTextWrap(true); // wrap text

        matrix.setTextColor(matrix.Color333(7,7,7));
        //matrix.print("D:");
        //matrix.println(receivedChars);
              
        //Serial.print("This just in ... ");
        Serial.println(receivedChars);
        while (i<byBodyCount){
          while (j<byBodyParts){
          Serial.print(arrPartsCapture[i][j][1]);
          Serial.print(arrPartsCapture[i][j][1]);
          j++;
          }
        i++;  
        }
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
