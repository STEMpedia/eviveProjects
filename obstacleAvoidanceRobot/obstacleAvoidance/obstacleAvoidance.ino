
/*
 *date-2/6/2016
 *developed by- Madhukant (kantmadhu956@gmail.com) & Tushar Gupta(tushargupta5197@gmail.com )
 */
 #include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>    // Hardware-specific library
#include <SPI.h>

#define TFT_CS     48
#define TFT_RST    47           // you can also connect this to the Arduino reset
                                // in which case, set this #define pin to 0!
#define TFT_DC     49

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


#include <Servo.h>

#include <motor.h>

Motor left(29,28,44);
Motor right(30,31,45);

  int i;
  int meanspeed=220;
  int speedleft=meanspeed;
  int speedright=meanspeed;
  
#define trigPin 3                // pins for ultrasonic sensor
#define echoPin 2

int limit=20;
int factor=30;

Servo servo;                     // declare your servo as an object

void setup() {
  Serial.begin (9600);
  servo.attach(9);               // telling the ide that the servo is at pin 9
  pinMode(40,INPUT);             // Setting a slideswitch of evive as on/off button
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  tft.setCursor(0,0);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
   tft.setTextColor(ST7735_YELLOW,ST7735_BLACK);    
}
int leftd,rightd;               // to store distances towards left and right
int dist()                      // to find the distance via the ultrasonic sensor
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2);        // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10);       // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  tft.setCursor(0,0);
  tft.print(distance);
  return distance;
}
int turn;
int scan()                      // scanning the left and right sides before turning
{
  servo.write(60);
  delay(300);
  leftd=dist(); 
  tft.setCursor(50,0);
  tft.print(leftd);
  servo.write(120);
  delay(300);
  rightd=dist(); 
  tft.print(rightd);
  if(leftd>rightd)               // emptier in left
  return -1;
  else return 1;                 // emptier in right
}
void loop() {
if(digitalRead(40)==HIGH)       //On/off switch  
  {
  int forward;
 forward=dist();
 Serial.println(forward);
 tft.setCursor(0,0);
 tft.print(forward);
  left.moveMotor(speedleft);
  right.moveMotor(speedright);
  //delay(1000);
  while(dist()<limit)                     // for stopping whenever distance become less than a limit 
  {
    left.stopMotor();         
    right.stopMotor();
    turn= scan();
Serial.println(turn);
  if(turn==-1)      //turn right
    {
      speedleft=meanspeed;
      speedright=0;
       left.moveMotor(speedleft);
      right.moveMotor(speedright);
      delay(800);
    }
    else if(turn==1)       //turn left
    {
      speedright=meanspeed;
      speedleft=0;
       left.moveMotor(speedleft);
      right.moveMotor(speedright);
      delay(800);
    }
    
  }

speedleft=meanspeed;
      speedright=meanspeed;
// printing the values on tft screen      
      tft.setCursor(0,20);
      tft.print(speedleft);
      tft.print("  ");
      tft.print(speedright);
      left.moveMotor(speedleft);
      right.moveMotor(speedright);
      
      servo.write(90);
      
  delay(15);
} 
else       //when slideswitch is off
  {
    left.stopMotor();
    right.stopMotor();
      tft.fillScreen(ST7735_BLACK);

  }
}
