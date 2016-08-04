/*
 * Alarm clock using evive
 * Developed by: Madhukant and Tushar Gupta
 * Date: 2016/05/30
 * 
 * NOTE: After uploading this code once to set time-date-day-etc, comment out the 
 * line number 124 (setPCF8563();) and upload again. The calender data will be stored 
 * in RTC (real time clock: PCF8563) even after reset.
 * 
 * Tutorial link: http://www.instructables.com/id/Alarm-Clock-With-Evive/
 * Vidoe Link: https://www.youtube.com/watch?v=oMFPtdQXw4E&feature=youtu.be
 */

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
// TFT is internally connected to Arduino MEGA in evive
#define TFT_CS     48
#define TFT_RST    47
#define TFT_DC     49

//initialize a tft variable
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

//********************alarm clock initiasation***********************
#include "Wire.h"
#define PCF8563address 0x51

#define alarmOnOff	40
#define alarmHand		A9
#define buzzerPin 	46
// calender function variables
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
String days[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT" };

// Bell icon size: 16W*16H
const unsigned char bell [] PROGMEM = {
0x01, 0x80, 0x03, 0xc0, 0x0f, 0xf0, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8, 0x3f, 0xfc, 0x3f, 0xfc, 
0x3f, 0xfc, 0x3f, 0xfc, 0x3f, 0xfc, 0x7f, 0xfe, 0x7f, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0x3f, 0xfc, 
};

byte bcdToDec(byte value)
{
  return ((value / 16) * 10 + value % 16);
}

byte decToBcd(byte value){
  return (value / 10 * 16 + value % 10);
}

void setPCF8563()
// this sets the time and date to the PCF8563
{
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.write(decToBcd(second));           //second
  Wire.write(decToBcd(minute));           //minute
  Wire.write(decToBcd(hour));             //hour
  Wire.write(decToBcd(dayOfMonth));       //date
  Wire.write(decToBcd(dayOfWeek));        //day of week see_the_above array
  Wire.write(decToBcd(month));            //month
  Wire.write(decToBcd(year));             //year
  Wire.endTransmission();
}

// Gets the time and date from the PCF8563
void readPCF8563()
{
  Wire.beginTransmission(PCF8563address);
  Wire.write(0x02);
  Wire.endTransmission();
  Wire.requestFrom(PCF8563address, 7);
  second     = bcdToDec(Wire.read() & B01111111); // remove VL error bit
  minute     = bcdToDec(Wire.read() & B01111111); // remove unwanted bits from MSB
  hour       = bcdToDec(Wire.read() & B00111111); 
  dayOfMonth = bcdToDec(Wire.read() & B00111111);
  dayOfWeek  = bcdToDec(Wire.read() & B00000111);  
  month      = bcdToDec(Wire.read() & B00011111);  // remove century bit, 1999 is over
  year       = bcdToDec(Wire.read());
}

//Initialize angles of clock hands
float hangle=0;
float mangle=0;
float sangle=0;
float aangle=0,paangle=0;

int i=0;

void setup()
{ 
  //*************************clock setup*****************
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

	tft.fillScreen(ST7735_BLACK);
	//Draw clock dial and hour markings
  tft.drawCircle(tft.width()/2,tft.height()/2,60,ST7735_WHITE);
  for(i=0;i<12;i++)
  {
		tft.drawLine(tft.width()/2+55*sin(i*30*3.14/180),tft.height()/2+55*cos(i*30*3.14/180),tft.width()/2+60*sin(i*30*3.14/180),tft.height()/2+60*cos(i*30*3.14/180),ST7735_WHITE);
  }
  Serial.println("init");
  tft.setRotation(1);
  tft.setTextWrap(false); // Allow text to run off right edge
  //tft.fillScreen(ST7735_BLACK);
  //***************clock setup end **********************
  Wire.begin();
  Serial.begin(9600);
  pinMode(alarmOnOff,INPUT);

  //Change the following to set your initial time
  second = 0;					//0-59
  minute = 0;					//0-59
  hour = 0;						//0-23
  dayOfWeek = 0;			//0-6
  dayOfMonth = 1;			//1-31 (includes Leap year correction by having 29th Feb)
  month = 1;					//1-12
  year = 0;						//0-99
  
  //Comment out the next line and upload again to set and keep the time from resetting every reset
  setPCF8563();
	
  // int alarmpot=A9;
  //pinMode(39,INPUT);
  pinMode(buzzerPin,OUTPUT);
}

//**************variables for tone*******************************
 int songLength = 18;
char notes[] = "cdfda ag cdfdg gf ";
int beats[] = {1,1,1,1,1,1,4,4,2,1,1,1,1,1,1,4,4,2};
int tempo = 113;
int pressbutton=1;
//********************tone function*********************************
int frequency(char note) 
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.

  int i;
  const int numNotes = 8;  // number of notes we're storing

  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}

//*******************clock function********************************
float pmangle=0,phangle=0,psangle=0;
void drawClock(int hour,int minute, int second, int date, int month,int year,String week)
{
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
	//print digital clock
  tft.setCursor(tft.width()/2-40,tft.height()/2+20);
  tft.print(((hour%12)/10?(String)(hour%12):(" "+(String)(hour%12))));tft.print(":");tft.print((String)minute);tft.print(":");tft.print((second/10?(String)second:(" "+(String)second)));tft.print(" ");tft.print(hour/12?"PM":"AM");
	
  mangle=-6*minute*3.14/180+3.14;
  hangle=-(30*hour+0.5*minute)*3.14/180+3.14;
  sangle=-6*second*3.14/180+3.14;
	//erase previous hands
  tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+50*sin(pmangle),tft.height()/2+50*cos(pmangle),ST7735_BLACK);
	tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+30*sin(phangle),tft.height()/2+35*cos(phangle),ST7735_BLACK);
	tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+55*sin(psangle),tft.height()/2+55*cos(psangle),ST7735_BLACK);

	pmangle=mangle;
	phangle=hangle;
	psangle=sangle;
	//draw new hands
  tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+50*sin(mangle),tft.height()/2+50*cos(mangle),ST7735_MAGENTA);
	tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+30*sin(hangle),tft.height()/2+35*cos(hangle),ST7735_GREEN);
	tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+55*sin(sangle),tft.height()/2+55*cos(sangle),ST7735_RED);

	//print date and day
	tft.setTextColor(ST7735_CYAN);
	tft.setTextSize(1);
	tft.setCursor(140,15);
	tft.print(week);
	tft.setCursor(115,5);
	tft.print(date);tft.print("-");tft.print(month);tft.print("-");tft.print(year);
}
//*******************clock function end*************************
long t=millis();

void loop()
{ readPCF8563();
	//send calender variables on serial port
  Serial.print(days[dayOfWeek]); 
  Serial.print(" ");  
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/20");
  Serial.print(year, DEC);
  Serial.print(" - ");
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute < 10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");  
  if (second < 10)
  {
    Serial.print("0");
  }  
  Serial.println(second, DEC); 
	//draw alarm hand
  aangle=-((1-analogRead(alarmHand)/1023.0)*6.28);
  tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+30*sin(paangle),tft.height()/2+28*cos(paangle),ST7735_BLACK);
  tft.drawLine(tft.width()/2,tft.height()/2,tft.width()/2+30*sin(aangle),tft.height()/2+28*cos(aangle),ST7735_YELLOW);
  drawClock(hour,minute,second,dayOfMonth,month,year,days[dayOfWeek]);
  paangle=aangle;
  delay(1000);
  //***********************alarm tone****************************************************
	//subtract 2*pi from hour hand angle after 12 hours
	if(hangle<(-6.28))
	hangle=hangle+6.28;
	Serial.println(digitalRead(alarmOnOff));
	
	//draw bell icon if alarm is on
	if (digitalRead(alarmOnOff) == 1)	tft.drawBitmap(140,108,bell,16,16,ST7735_YELLOW);
	else tft.drawBitmap(140,108,bell,16,16,ST7735_BLACK);
	
	//play tone
  if(abs(hangle-aangle)<=0.05&&digitalRead(alarmOnOff)==1)		//do the alarm and hour hands match? and is the alarm on?
    {
      int i, duration;
      tone(buzzerPin,1000,1000);
			for (i = 0; i < songLength; i++) 												// step through the song arrays
			{
				duration = beats[i] * tempo;  												// length of note/rest in ms
				if (notes[i] == ' ')          												// is this a rest? 
				{
					delay(duration);            												// then pause for a moment
				}
				else                          												// otherwise, play the note
				{
					tone(buzzerPin, frequency(notes[i]), duration);
					delay(duration);            												// wait for tone to finish
				}
			delay(tempo/10);              													// brief pause between notes
		}
  }
}
