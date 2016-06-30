/*
 * This code is tested with evive. Visit http://evive.cc for more information
 * Code developed by- Tushar Gupta (tushargupta5197@gmail.com) &  Madhukant(kantmadhu956@gmail.com) 
 * Date developed - 28/6/2016
 */
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS     48
#define TFT_RST    47  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     49

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {  
  for(int i=2;i<=6;i++)
  pinMode(i,OUTPUT);
  Serial.begin(9600);
  tft.initR(INITR_BLACKTAB);    // intialising the screen
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);     //to set the TFT screen Landscape
  tft.setTextWrap(false);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
}
bool once=true;
int k=0,arr[5]={0,0,0,0,0};
int arr1[5]={random(1,6),random(1,6),random(1,6),random(1,6),random(1,6)};
int a,j=0;
int level=1, deltaTime=500;
void loop() {
                              //printing on  the screen 
  tft.setTextSize(2);
   tft.setCursor(15,15);
 tft.print("Simon Says");
 tft.setTextSize(3);
 tft.setCursor(15,50);
 tft.print("level: ");
 tft.print(level);

  if (once==true) 
  for(int i=0;i<=4;i++)
  {digitalWrite(arr1[i]+1,HIGH);delay(deltaTime);digitalWrite(arr1[i]+1,LOW);delay(deltaTime);once=false;}
                                  //changing the pin mode to input
  for(int i=2;i<=6;i++)
    pinMode(i,INPUT);
  
  if((digitalRead(2)==HIGH)||(digitalRead(3)==HIGH)||(digitalRead(4)==HIGH)||(digitalRead(5)==HIGH)||(digitalRead(6)==HIGH))
  {
                                  //debouncing the switch
    if(digitalRead(2)==HIGH)
   //Serial.println("2");
    a=2;
    else if(digitalRead(3)==HIGH)
   // Serial.println("3");
  a=3;
    else if(digitalRead(6)==HIGH)
    a=6;//Serial.println("6");

    else if(digitalRead(4)==HIGH)
    a=4;//Serial.println("4");

    else if(digitalRead(5)==HIGH)
    a=5;

    arr[j]=a-1;
  }
  else a=0;
if(arr[j]!=0&&j<5&&a==0)
{
  j++;
}
Serial.println(j);

if(j==5)
{
  for(int g=2;g<=6;g++)
    {
      pinMode(g,OUTPUT);
    }
  for(int i=0;i<5;i++)
  {
    Serial.print(arr[i]);
    Serial.print(" ");
  }
  Serial.println();
  for(int i=0;i<5;i++)
  {
    Serial.print(arr1[i]);
    Serial.print(" ");
  }
  Serial.println();
  for(k=0;k<5;k++)
  {
   if( arr[k]==arr1[k])
   continue;
   else break;
  }

                                                              // level completed next level

  if(k==5) 
  {
    for(int g=2;g<=6;g++)
    {
      digitalWrite(g,HIGH);
      delay (100);
      digitalWrite(g,LOW);
    }
      for(int i=2;i<=6;i++)
  pinMode(i,OUTPUT);
  
   once=true;;
   k=0;
   for(int i=0;i<5;i++)
   {
      arr[i]=0;
      arr1[i]=random(1,6);
   }
   a=0;j=0;
   level++;
   deltaTime=deltaTime-50;
  }
  else 
  {
    for(int g=2;g<=6;g++)
    {
      digitalWrite(g,HIGH);
    }
    tft.fillScreen(ST7735_BLACK);
    tft.setCursor(5,50);
    tft.print("Game Over");

    delay(3000);
  }
}
}
