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

void setup() {

  matrix.begin();


  // fill the screen with 'black'
  matrix.fillScreen(matrix.Color333(0, 0, 0));

}

void loop() {


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
drawFigure (15, 5, 15, 9, 12, 12, 8, 12,  5, 14, 15, 19);
delay (25);
drawFigure (15, 5, 15, 9, 12, 12, 10, 11, 6, 10, 15, 19);
delay (25);
drawFigure (16, 5, 16, 9, 13, 11, 9, 8,   7, 5,  15, 19);
delay (25);
for (int i = 0; i < 5; i++){
  drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  9, 3,  15, 19);
  delay (10);
  drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  8, 4,  15, 19);
  delay (10);
  drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  7, 5,  15, 19);
  delay (10);
  drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  6, 6,  15, 19);
  delay (10);
  drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  7, 5,  15, 19);
  delay (10);
  drawFigure (16, 5, 16, 9, 13, 11, 10, 8,  8, 4,  15, 19);
  delay (10);
}
delay (500);

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

// Function to read a text file one field at a time.
//


/*
 * Read a file one field at a time.
 *
 * file - File to read.
 *
 * str - Character array for the field.
 *
 * size - Size of str array.
 *
 * delim - String containing field delimiters.
 *
 * return - length of field including terminating delimiter.
 *
 * Note, the last character of str will not be a delimiter if
 * a read error occurs, the field is too long, or the file
 * does not end with a delimiter.  Consider this an error
 * if not at end-of-file.
 *
 */
size_t readField(File* file, char* str, size_t size, char* delim) {
  char ch;
  size_t n = 0;
  while ((n + 1) < size && file->read(&ch, 1) == 1) {
    // Delete CR.
    if (ch == '\r') {
      continue;
    }
    str[n++] = ch;
    if (strchr(delim, ch)) {
        break;
    }
  }
  str[n] = '\0';
  return n;
}
//------------------------------------------------------------------------------
#define errorHalt(msg) {Serial.println(F(msg)); while(1);}
//------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);

  // Initialize the SD.
  if (!SD.begin(CS_PIN)) errorHalt("begin failed");

  // Create or open the file.
  file = SD.open("READTEST.TXT", FILE_WRITE);
  if (!file) errorHalt("open failed");

  // Rewind file so test data is not appended.
  file.seek(0);

  // Write test data.
  file.print(F(
    "field_1_1,field_1_2,field_1_3\r\n"
    "field_2_1,field_2_2,field_2_3\r\n"
    "field_3_1,field_3_2\r\n"           // missing a field
    "field_4_1,field_4_2,field_4_3\r\n"
    "field_5_1,field_5_2,field_5_3"     // no delimiter
    ));

  // Rewind the file for read.
  file.seek(0);

  size_t n;      // Length of returned field with delimiter.
  char str[20];  // Must hold longest field with delimiter and zero byte.

  // Read the file and print fields.
  while (true) {
    n = readField(&file, str, sizeof(str), ",\n");

    // done if Error or at EOF.
    if (n == 0) break;

    // Print the type of delimiter.
    if (str[n-1] == ',' || str[n-1] == '\n') {
      Serial.print(str[n-1] == ',' ? F("comma: ") : F("endl:  "));

      // Remove the delimiter.
      str[n-1] = 0;
    } else {
      // At eof, too long, or read error.  Too long is error.
      Serial.print(file.available() ? F("error: ") : F("eof:   "));
    }
    // Print the field.
    Serial.println(str);
  }
  file.close();
}
//------------------------------------------------------------------------------
void loop() {
}
