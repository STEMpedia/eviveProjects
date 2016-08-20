/*
 * Line Follower robot using Smartphone, evive and 1Sheeld
 * Date: 2016, Aug 20
 * Developed by Dhrupal R Shah
 * Reference 1Sheeld example
 */
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_COLOR_DETECTOR_SHIELD
#include <OneSheeld.h>

unsigned long white = 0xFFFFFF;

//Pin mapping for dual channel motor driver in evive
int motor1PWM = 44;
int motor1DIR1 = 28;
int motor1DIR2 = 29;
int motor2PWM = 45;
int motor2DIR1 = 30;
int motor2DIR2 = 31;
int flag = 0;

void setup() {
  OneSheeld.begin();
  ColorDetector.setOnSelected(&selected);
  pinMode(motor1PWM, OUTPUT);
  pinMode(motor1DIR1, OUTPUT);
  pinMode(motor1DIR2, OUTPUT);
  pinMode(motor2PWM, OUTPUT);
  pinMode(motor2DIR1, OUTPUT);
  pinMode(motor2DIR2, OUTPUT);  
  
  digitalWrite(motor1DIR2, LOW);
  digitalWrite(motor1DIR1, HIGH);
  digitalWrite(motor2DIR2, LOW);
  digitalWrite(motor2DIR1, HIGH);  
}

void loop() {  
}

void selected()
{
  ColorDetector.setPalette(_3_BIT_RGB_PALETTE);
  ColorDetector.enableFullOperation();
  ColorDetector.setCalculationMode(MOST_DOMINANT_COLOR);
  ColorDetector.setOnNewColor(&newColor);
}

void newColor(Color one,Color two,Color three,Color four,Color five,Color six,Color seven,Color eight,Color nine)
{

  if (three == white && one == white)
  {    moveForward();
  //The following conditions helps in remembering history for undershoot case of line following,
  //i.e. robot was not able to turn towards line and escapes line
  //if below code is uncommented, then comment out the "moveForward()" command above
//    if(flag == -1)  moveLeft();
//    else if (flag == 1) moveRight();
//    else if ( two !=white){
//      moveForward();
//      flag = 0;
    }
  }
  else if (three == white && one != white)
  { moveLeft();
    flag = -1;
  }
  else if (one == white && three != white)
  { moveRight();
    flag = 1;
  }
}

void moveForward()
{
  analogWrite(motor1PWM, 200);
  analogWrite(motor2PWM, 200);
  }

void moveRight()
{
  analogWrite(motor1PWM, 250);
  analogWrite(motor2PWM, 100);
  }

void moveLeft()
{
  analogWrite(motor1PWM, 100);
  analogWrite(motor2PWM, 250);
  }
