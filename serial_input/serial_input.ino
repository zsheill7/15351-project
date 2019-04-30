#include <Servo.h>;

Servo myservo;
int Nose = 0;
int Neck = 1;
int RShoulder = 2;
int RElbow = 3;
int RWrist = 4;
int LShoulder = 5;
int LElbow = 6;
int LWrist = 7;
int RHip = 8;
int RKnee = 9;
int RAnkle = 10;
int LHip = 11;
int LKnee = 12;
int LAnkle = 13;
int REye = 14;
int LEye = 15;
int REar = 16;
int LEar = 17;
int Background = 18;

const int totalBodyParts = 18;
char bodyPartX[totalBodyParts+1];
// char bodyPartY[totalBodyParts+1];
int xValue = 0;
int newXValue = 0;
int index = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(10);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void serialEvent()
{
  while(Serial.available())
  {
    char ch = Serial.read();
    Serial.write(ch);
    if(index < totalBodyParts && isDigit(ch))
    {
      bodyPartX[index++] = ch;
    } else {
      bodyPartX[index] = 0;                               
      newXValue = atoi(bodyPartX);                               
      if(newXValue > 0 && newXValue < 180){
         if(newXValue < xValue)                                                
             for(; xValue > newXValue; xValue -= 1) {
             myservo.write(xValue);
         }  
      else 
         for(; xValue < newXValue; xValue += 1){
             myservo.write(xValue);
          } 
      }
      bodyPartX;
      index = 0;
      xValue = newXValue;
    }
  }
}
