/*
 * Scientific Calculator using evive
 * Developed by: Madhukant (kantmadhu956@gmail.com) and Tushar Gupta (tushargupta5197@gmail.com)
 * Date: 2016/06/23
  */
#include <Keypad.h>
#include <Wire.h> 
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#define buzzer 46
#define TFT_CS     48
#define TFT_RST    47  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     49

Adafruit_ST7735 lcd = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

int conti=0;
double first = 0;
double second = 0;
double total = 0;

char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {11,10,9,8}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
//*****************scientific buttons******************
int sine=25;
int cosine=27;
int tangent=23;
int logue=22;
int arcsin=24;
int arccos=26;
int arctan=14;
int root=15;

//*****************************************************
void setup()
{
  pinMode(sine,INPUT);
  pinMode(cosine,INPUT);
  pinMode(tangent,INPUT);
  pinMode(logue,INPUT);
  pinMode(arcsin,INPUT);
  pinMode(arccos,INPUT);
  pinMode(arctan,INPUT);
  pinMode(root,INPUT);
  pinMode(13,OUTPUT);
  
  Serial.begin(9600);
  
  lcd.initR(INITR_BLACKTAB);
  lcd.fillScreen(ST7735_BLACK);
  lcd.setRotation(1);
  lcd.setCursor(0,0);
  lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);
  lcd.setTextSize(2);
}
void printhistory(double first,double second,char sign){
  lcd.setTextSize(1);
  lcd.setCursor(0,100);
  lcd.setTextColor(ST7735_YELLOW,ST7735_BLACK);
  lcd.print("Previous---------------------------");
  lcd.setCursor(0,110);
  lcd.setTextColor(ST7735_CYAN,ST7735_BLACK);
  lcd.print(first);
  lcd.print(" ");
  lcd.print(sign);
  lcd.print(" ");
  lcd.print(second);
  lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);
  lcd.setTextSize(2);
}

bool isDecimal1=false;
float decimals1=10.0;
bool isDecimal2=false;
float decimals2=10.0;

void loop()
{
  customKey = customKeypad.getKey();
//******************************sin, cos, tan, logarithm and inverse******************  
   if(digitalRead(logue)==HIGH)
  {  delay(250);
  if(digitalRead(logue)==HIGH)
    { Serial.println("log 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=log(first);
    else 
      first=-999999999999999; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }    //log ends 
  
  if(digitalRead(sine)==HIGH)
  {  delay(250);
  if(digitalRead(sine)==HIGH)
    { Serial.println("sine 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=sin(first);
    else 
      first=0; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }    //sine ends 
  
 if(digitalRead(cosine)==HIGH)
  {  delay(250);
  if(digitalRead(cosine)==HIGH)
    { Serial.println("cosine 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=cos(first);
    else 
      first=1; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }     
   if(digitalRead(tangent)==HIGH)
  {  delay(250);
  if(digitalRead(tangent)==HIGH)
    { Serial.println("tangent 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=tan(first);
    else 
      first=0; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }   

  if(digitalRead(arcsin)==HIGH)
  {  delay(250);
  if(digitalRead(arcsin)==HIGH)
    { Serial.println("asin 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=asin(first);
    else 
      first=0; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }    //asine ends 
  
 if(digitalRead(arccos)==HIGH)
  {  delay(250);
  if(digitalRead(arccos)==HIGH)
    { Serial.println("arccos 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=acos(first);
    else 
      first=1.57; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }     
   if(digitalRead(arctan)==HIGH)
  {  delay(250);
  if(digitalRead(arctan)==HIGH)
    { Serial.println("arctan 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=atan(first);
    else 
      first=0; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }   

     if(digitalRead(root)==HIGH)
  {  delay(250);
  if(digitalRead(root)==HIGH)
    { Serial.println("root 1");
      tone(buzzer,5000,100);
      if(first!=0)
       first=sqrt(first);
    else 
      first=0; 
    lcd.setCursor(0,0);
    lcd.print(first);
    }
  }   
//************************sin, cos, tan, logarithm and inverse end************************ 

 if(digitalRead(17)==HIGH)
 {
  delay(250);
  if(digitalRead(17)==HIGH)
  { tone(buzzer,5000,100);
    isDecimal1=true;
  }
 }
  if(customKey!=NO_KEY){
    tone(buzzer,5000,100);
  Serial.println(isDecimal1);  
  switch(customKey) 
  {
  case '0' ... '9': // This keeps collecting the first value until a operator is pressed "+-*/"
    if (isDecimal1==false)
    {
      lcd.setCursor(0,0);
    first = first * 10 + (customKey - '0');
    lcd.print(first);
    }
  else
  {
    lcd.setCursor(0,0);
    first=first+(customKey - '0')/decimals1;
    decimals1=decimals1*10;
    lcd.print(first);
  }
      break;
  case '+':
    first = (total != 0 ? total : first);
    A:
    lcd.setCursor(0,20);
    lcd.print("+");
    second = SecondNumber(); // get the collected the second number
    total = first + second;
    lcd.setCursor(0,60);
    lcd.setTextColor(ST7735_RED,ST7735_BLACK);
    lcd.print("---------------");
    lcd.setCursor(0,80);
    lcd.setTextColor(ST7735_GREEN,ST7735_BLACK);
    lcd.print(total);
    lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);
    delay(500);
    lcd.fillScreen(ST7735_BLACK);
    printhistory(first,second,'+');
    first = total, second = 0; // reset values back to zero for next use
    lcd.setCursor(0,0);
    lcd.print(first);
     if(conti==1)
      goto A;
    else if(conti==2)  
      goto B;
    else if(conti==3)
      goto C;
    else if(conti==4)
      goto D;
    total=0;
    break;

  case '-':
    first = (total != 0 ? total : first);
    B:
    lcd.setCursor(0,20);
    lcd.print("-");
    second = SecondNumber();
    total = first - second;
    lcd.setCursor(0,60);
    lcd.setTextColor(ST7735_RED,ST7735_BLACK);
    lcd.print("---------------");
    lcd.setCursor(0,80);
    lcd.setTextColor(ST7735_GREEN,ST7735_BLACK);
    lcd.print(total);
    lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);
    delay(500);
    lcd.fillScreen(ST7735_BLACK);
    printhistory(first,second,'-');
    first = total, second = 0; // reset values back to zero for next use
    lcd.setCursor(0,0);
    lcd.print(first);
    if(conti==1)
      goto A;
    else if(conti==2)  
      goto B;
    else if(conti==3)
      goto C;
    else if(conti==4)
      goto D;    
    total=0;
    break;

  case '*':
    first = (total != 0 ? total : first);
    C:
    lcd.setCursor(0,20);
    lcd.print("*");
    second = SecondNumber();
    total = first * second;
    lcd.setCursor(0,60);
    lcd.setTextColor(ST7735_RED,ST7735_BLACK);
    lcd.print("---------------");
    lcd.setCursor(0,80);
    lcd.setTextColor(ST7735_GREEN,ST7735_BLACK);
    lcd.print(total);
    lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);
    delay(500);
    lcd.fillScreen(ST7735_BLACK);
    printhistory(first,second,'*');
    first = total, second = 0; // reset values back to zero for next use
    lcd.setCursor(0,0);
    lcd.print(first);
     if(conti==1)
      goto A;
    else if(conti==2)  
      goto B;
    else if(conti==3)
      goto C;
    else if(conti==4)
      goto D;
    total=0;  
    break;

  case '/':
    first = (total != 0 ? total : first);
    D:
    lcd.setCursor(0,20);
    lcd.print("/");
    second = SecondNumber();
    lcd.setCursor(0,60);

    second == 0 ? lcd.print("Invalid") : total = (float)first / (float)second;
    
    if(second!=0)
      {
         lcd.setTextColor(ST7735_RED,ST7735_BLACK);
    lcd.print("---------------");
    lcd.setCursor(0,80);
    lcd.setTextColor(ST7735_GREEN,ST7735_BLACK);
    lcd.print(total);
    lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);
    delay(500);
    lcd.fillScreen(ST7735_BLACK);
    printhistory(first,second,'/');
    first = total, second = 0; // reset values back to zero for next use
    lcd.setCursor(0,0);
    lcd.print(first);
     if(conti==1)
      goto A;
    else if(conti==2)  
      goto B;
    else if(conti==3)
      goto C;
    else if(conti==4)
      goto D;
    total=0; 
      }
    break;

  case 'C':
    total = 0;
    lcd.fillScreen(ST7735_BLACK);
    first=0;
    second=0;
    isDecimal1=false;
    isDecimal2=false;
    decimals1=10;
    decimals2=10;
    break;
    
  }
 } 
}

double SecondNumber()
{
  while( 1 )
  {
    customKey = customKeypad.getKey();
     if(digitalRead(17)==HIGH)
 {
  delay(250);
  if(digitalRead(17)==HIGH)
  { tone(buzzer,5000,100);
    isDecimal2=true;
  }
 }
 if(customKey!=NO_KEY)
    {   
        tone(buzzer,5000,100);
        Serial.println(isDecimal2);
    }
 if(customKey >= '0' && customKey <= '9')
    {
 if (isDecimal2==false)
    {
    lcd.setCursor(0,40);
    second = second * 10 + (customKey - '0');
    lcd.print(second);
    }
  else
  {
    lcd.setCursor(0,40);
    second=second+(customKey - '0')/decimals2;
    decimals2=decimals2*10;
    lcd.print(second);
  }
    }

 if(customKey == '=') 
  { 
    conti=0;
    isDecimal1=false;
    isDecimal2=false;
    decimals1=10;
    decimals2=10;
     break;  //return second;
        
      }
    else if(customKey == '+')
      {  conti=1;
         break;
      }
    else if(customKey=='-') 
     {  conti=2;
         break;
      } 
      else if(customKey=='*') 
     {  conti=3;
         break;
      } 
      else if(customKey=='/') 
     {  conti=4;
         break;
      } 
  } 
 return second;
   
}
