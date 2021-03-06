// testshapes demo for Adafruit RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x32 RGB LED matrix:
// http://www.adafruit.com/proucts/607

// Written by Limor Fried/Ladyada & Phil Burgess/PaintYourDragon
// for Adafruit Industries.
// BSD license, all text above must be included in any redistribution.

#include <Arduino.h>
#include <avr/wdt.h>  // For watchdog timer
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#define CS_PIN 10

File file;

//Pinout setup for Arduino UNO
#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

int data;

//This array can capture 3 bodies of 17 parts each
const byte byBodyCount = 2;
const byte byBodyParts = 17;
const byte byBodyLines = 14;
short int arrPartsCapture [byBodyCount][byBodyParts][2];

////These variables used for serial to array function
//const byte numChars = 3*18*2+1;  //TODO: check if this restricts length of string (It does)
//char receivedChars[numChars];
//char arrTempChars[5];
//boolean newData = false;
//boolean recvInProgress = false;

//These variables are used for serial communications with pc

const short int buffSize = byBodyCount*byBodyParts*11+2;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
short int bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;

char messageFromPC[buffSize] = {0};
int newFlashInterval = 0;
float servoFraction = 0.0; // fraction of servo range to move

//This array is used to draw up to 14 body lines for up to 3 bodies
const byte byAllBodyLines = byBodyCount * byBodyLines;
byte arrAllBodyLines [byAllBodyLines][2];

//These arrays are used to draw the heads and eyes of our bodies
byte arrHeadCenter [byBodyCount][2];
byte arrEyes [byBodyCount*2][2];

void setup() {

  Serial.begin(9600); 

  //pinMode(13, OUTPUT);
  //digitalWrite(13, LOW);
  
  matrix.begin();
  wdt_enable(WDTO_8S);
  Serial.println("<Arduino ready.>");

  //Show init on screen with blinking circle
//  for(byte i=0; i<5; i++) {
//    matrix.fillCircle(15, 15, 4, matrix.Color333(7, 7, 0));
//    delay (250);
//    matrix.fillScreen(matrix.Color333(0, 0, 0));
//    delay (125);
//  }

  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  
}

void loop() {
 
  //readSerialConsecIntegers();
  wdt_reset();
  getDataFromPC();
  
//  Serial.print(".");
      
      //drawFigure (15, 5, 15, 9, 12, 12, 8, 12,  5, 14, 15, 19);
      //drawFigure(headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
      //digitalWrite(13, HIGH);
  //    delay (25);
  //    drawFigure(headX, headY, neckX, neckY, ShouX, ShouY, rElboX, rElboY, rHandX, rHandY, pelvX, pelvY);
  //    
  
    
  
  
//  delay (50);

}

void getDataFromPC() {

    // receive data from PC and save it into inputBuffer

//  if(Serial.available() > 0) {
    while(Serial.available() > 0){ 
    char x = Serial.read();
    Serial.print(x);
      // the order of these IF clauses is significant
      
    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      assignReceivedCharToBodyParts();
//      parseData();
    }
    
    if(readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }

    if (x == startMarker) { 
      bytesRecvd = 0; 
      readInProgress = true;
      
    }
  }
}

void assignReceivedCharToBodyParts(){


  static boolean doBodyCheck = true;
  byte i=0;
  byte j=0;
  int body;
  int part;
  int xcoord;
  int ycoord;
                
     // split the data into its parts
    
  char * strtokIndx; // this is used by strtok() as an index

//This loop is designed to parse a string of body part data with a format like b0dy-part:x,y#. For example 0-0:14,10#0-1:14,15#  
  Serial.println("*");
  Serial.println(inputBuffer);
//  Serial.println(strtokIndx = strtok(inputBuffer,"-"));
//  Serial.println(strtokIndx = strtok(NULL, ":"));
//  Serial.println(strtokIndx = strtok(NULL, ","));
//  Serial.println(strtokIndx = strtok(NULL, "#"));
//  Serial.println(strtokIndx = strtok(NULL,"-"));
//  Serial.println(strtokIndx = strtok(NULL, ":"));
//  Serial.println(strtokIndx = strtok(NULL, ","));
//  Serial.println(strtokIndx = strtok(NULL, "#"));
  while (i<byBodyCount){
    j=0;
//    Serial.print(i);
    while (j<byBodyParts){
        Serial.print("Reading");
        Serial.println(strtokIndx);
//      Serial.print(j);
        if (doBodyCheck){
          if (i+j==0) strtokIndx = strtok(inputBuffer,"-"); // get the first part - the string
          else strtokIndx = strtok(NULL,"-");
          body = atoi(strtokIndx);     // this is the uid a.k.a. the body number
        }

      Serial.println("body is:");
      Serial.println(body);
      if ((body>98 || i == body) && j<byBodyParts){
        if (doBodyCheck){
          strtokIndx = strtok(NULL, ":"); // this continues where the previous call left off
          part = atoi(strtokIndx);     // this is the body part id 
        }
        else doBodyCheck = true;
        if (j == part){
          Serial.println("part is:");
          Serial.println(j);
          strtokIndx = strtok(NULL, ","); 
          xcoord = atoi(strtokIndx);     // this is the body part x coord
        
          strtokIndx = strtok(NULL, "#"); 
          ycoord = atoi(strtokIndx);     // this is the body part y coord   
          Serial.print("XY");
          Serial.print(xcoord);
          Serial.print(ycoord);
          arrPartsCapture[i][j][1]=xcoord;
          arrPartsCapture[i][j][2]=ycoord;
          Serial.print("  : and again?  :");
          Serial.print(arrPartsCapture[i][j][1]);
          Serial.println(arrPartsCapture[i][j][2]);          
          j++;
        }
        else {
          {
            Serial.print("adding default to part: ");
            Serial.println(j);
            arrPartsCapture[i][j][1]=200;
            arrPartsCapture[i][j][2]=200;
            if (j>=byBodyParts-1){
              Serial.println("Incrementing body from adding default to part");
              body = body +1;
              i++; //TODO: Might need to update filling out the rest of the j items in the matrix if body switches before we get to j=byBodyParts
            }
            j++;
            doBodyCheck = false;
          }
        } 
      }      
      else {
        if (body==99 || part==99) doBodyCheck=false;
        if (i<byBodyCount){
          Serial.println("Incrementing body");
          i++; //TODO: Need to update filling out the rest of the j items in the matrix if body switches before we get to j=byBodyParts
        }
        j++;
      }
    }
  }  
  i=0;
  j=0;
  body=0;
  part=0;
  doBodyCheck = true;
  replyToPC();
  buildFigureArray();
}

//void parseData() {
//
//    // split the data into its parts
//    
//  char * strtokIndx; // this is used by strtok() as an index
//  
//  strtokIndx = strtok(inputBuffer,",");      // get the first part - the string
//  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC
//  
//  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
//  headX = atoi(strtokIndx);     // convert this part to an integer
//  
//  strtokIndx = strtok(NULL, ","); 
//  headY = atoi(strtokIndx);     // convert this part to a float
//
//  strtokIndx = strtok(NULL, ","); 
//  neckX = atoi(strtokIndx);     // convert this part to a float
//}

//Used for troubleshooting serial comms
void replyToPC() { 
  byte b=0;
    
  if (newDataFromPC) {
    //comment out line below line buildFigureArray function is being used
    //newDataFromPC = false;
    Serial.print("Body ");
    Serial.println(b);
    for(byte p=0; p<byBodyParts; p++){
      Serial.print("  Part ");
      Serial.print(p);
      Serial.print(" X ");
      Serial.print(arrPartsCapture[b][p][1]);
      Serial.print(" y ");
      Serial.println(arrPartsCapture[b][p][2]);
    }

  }
}

void drawSegment(int x0, int y0, int x1, int y1) {
  if (x1 + y1 + x0 + y0 <199) {
    matrix.drawLine(x0, y0, x1, y1, matrix.Color333(0, 7, 7));
  }
}


//Uses byDataFromPC array to draw figure head and body segments on 32 x 32 array
void buildFigureArray(){
int headSize;
int headX;
int headY;

    
  if (newDataFromPC) {
    
    newDataFromPC = false;
    matrix.fillScreen(matrix.Color333(0, 0, 0));
    Serial.print("Drawing Body ");
    for(byte b=0; b<byBodyCount; b++){
      //Draw head
      if (arrPartsCapture[b][0][1]+arrPartsCapture[b][0][2]<199){
        headX = arrPartsCapture[b][0][1];
        headY = arrPartsCapture[b][0][2];
      }
      else {
        headX = 45;
        headY = 45; 
      }
      if (arrPartsCapture[b][0][1]+arrPartsCapture[b][0][2]+arrPartsCapture[b][1][1]+arrPartsCapture[b][1][2]<199) {
        headSize = floor( sqrt( (((arrPartsCapture[b][1][2]-arrPartsCapture[b][0][2])*(arrPartsCapture[b][1][2]-arrPartsCapture[b][0][2])) - ((arrPartsCapture[b][1][1]-arrPartsCapture[b][0][1])*(arrPartsCapture[b][1][1]-arrPartsCapture[b][0][1]))*((arrPartsCapture[b][1][2]-arrPartsCapture[b][0][2])*(arrPartsCapture[b][1][2]-arrPartsCapture[b][0][2]))) ));
      }
      else {
        headSize = 2;
      }
      matrix.fillCircle(headX, headY, headSize, matrix.Color333(7, 7, 0));

      //Draw shoulders
      drawSegment(arrPartsCapture[b][1][1],arrPartsCapture[b][1][2],arrPartsCapture[b][2][1],arrPartsCapture[b][2][2]);
      drawSegment(arrPartsCapture[b][1][1],arrPartsCapture[b][1][2],arrPartsCapture[b][5][1],arrPartsCapture[b][5][2]);
      //Draw Left Arm
      drawSegment(arrPartsCapture[b][2][1],arrPartsCapture[b][2][2],arrPartsCapture[b][3][1],arrPartsCapture[b][3][2]);
      drawSegment(arrPartsCapture[b][3][1],arrPartsCapture[b][3][2],arrPartsCapture[b][4][1],arrPartsCapture[b][4][2]);
      //Draw Right Arm
      drawSegment(arrPartsCapture[b][5][1],arrPartsCapture[b][5][2],arrPartsCapture[b][6][1],arrPartsCapture[b][6][2]);
      drawSegment(arrPartsCapture[b][6][1],arrPartsCapture[b][6][2],arrPartsCapture[b][7][1],arrPartsCapture[b][7][2]);
      //Draw Body
      drawSegment(arrPartsCapture[b][1][1],arrPartsCapture[b][1][2],arrPartsCapture[b][8][1],arrPartsCapture[b][8][2]);
      //Draw Hips
      drawSegment(arrPartsCapture[b][8][1],arrPartsCapture[b][8][2],arrPartsCapture[b][9][1],arrPartsCapture[b][9][2]);
      drawSegment(arrPartsCapture[b][8][1],arrPartsCapture[b][8][2],arrPartsCapture[b][12][1],arrPartsCapture[b][12][2]);
      //Draw Left Leg
      drawSegment(arrPartsCapture[b][9][1],arrPartsCapture[b][9][2],arrPartsCapture[b][10][1],arrPartsCapture[b][10][2]);
      drawSegment(arrPartsCapture[b][10][1],arrPartsCapture[b][10][2],arrPartsCapture[b][11][1],arrPartsCapture[b][11][2]); 
      //Draw Right Leg
      drawSegment(arrPartsCapture[b][12][1],arrPartsCapture[b][12][2],arrPartsCapture[b][13][1],arrPartsCapture[b][13][2]);
      drawSegment(arrPartsCapture[b][13][1],arrPartsCapture[b][13][2],arrPartsCapture[b][14][1],arrPartsCapture[b][14][2]);  

      //Draw Eyes
      if (arrPartsCapture[b][15][1]+arrPartsCapture[b][15][2] < 199) {
        matrix.drawPixel(arrPartsCapture[b][15][1], arrPartsCapture[b][15][2], matrix.Color333(0, 0, 0));
      }
      if (arrPartsCapture[b][16][1]+arrPartsCapture[b][16][2] < 199) {
        matrix.drawPixel(arrPartsCapture[b][16][1], arrPartsCapture[b][16][2], matrix.Color333(0, 0, 0));
      }
    }
  } 
}
