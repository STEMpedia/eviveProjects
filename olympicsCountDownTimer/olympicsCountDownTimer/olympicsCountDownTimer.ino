/*
 * Olympics Countdown Timer
 * Developed by: Madhukant, Tushar Gupta and Dhrupal
 * Date: 2016/08/05
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

#include "bitmaps.h"
#include "bitmapsLarge.h"

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

byte secondOlympics = 0, minuteOlympics = 0, hourOlympics = 15;

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

void setup(){ 
  //*************************clock setup*****************
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

	tft.fillScreen(ST7735_BLACK);

  tft.setRotation(1);
  tft.setTextWrap(false); // Allow text to run off right edge
  //tft.fillScreen(ST7735_BLACK);
  //***************clock setup end **********************
  Wire.begin();
  Serial.begin(9600);
  pinMode(alarmOnOff,INPUT);

  //Change the following to set your initial time
  second = 0;					//0-59
  minute = 25;					//0-59
  hour = 9;						//0-23
  dayOfWeek = 5;			//0-6
  dayOfMonth = 5;			//1-31 (includes Leap year correction by having 29th Feb)
  month = 8;					//1-12
  year = 16;						//0-99
  
  //Comment out the next line and upload again to set and keep the time from resetting every reset
  //setPCF8563();
	
  // int alarmpot=A9;
  //pinMode(39,INPUT);
  pinMode(buzzerPin,OUTPUT);
	
	//Case 2: Multi Colored Images/Icons
  int h = 66,w = 160, row, col, buffidx=0;
  for (row=0; row<h; row++) { // For each scanline...
    for (col=0; col<w; col++) { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, pgm_read_word(olympicsLogo + buffidx));
      buffidx++;
    } // end pixel
  }
	
	tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN,ST7735_BLACK);
	//print digital clock
  tft.setCursor(tft.width()/2-45,tft.height()/2+7);
	tft.print("Countdown Timer");
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
void drawClock(int hour,int minute, int second, int date, int month,int year,String week)
{
	tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE,ST7735_BLACK);
	//print digital clock
  tft.setCursor(tft.width()/2-40,tft.height()/2+40);
	tft.print("GMT ");
  tft.print(((hour%12)/10?(String)(hour%12):(" "+(String)(hour%12))));
	tft.print(":");
	tft.print((String)minute);
	tft.print(":");
	tft.print((second/10?(String)second:(" "+(String)second)));
	tft.print(" ");
	tft.print(hour/12?"PM ":"AM ");
	
	//print date and day
	tft.setCursor(tft.width()/2-30,tft.height()/2+50);
	tft.setTextColor(ST7735_CYAN);
	tft.print(date);
	tft.print("-");
	tft.print(month);
	tft.print("-");
	tft.print(year);
	tft.print(" ");
	tft.print(week);
}
//*******************clock function end*************************

void countDownClock(int hour,int minute, int second)
{
	tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW,ST7735_BLACK);
	//print digital clock
  tft.setCursor(tft.width()/2-50,tft.height()/2+20);

  tft.print((((hourOlympics-hour-1%12))/10?(String)((hourOlympics-hour-1)%12):(" "+(String)((hourOlympics - hour-1)%12))));
	tft.print(":");
	tft.print((String)(minuteOlympics+60-minute));
	tft.print(":");
	tft.print((secondOlympics+60-second/10?(String)(secondOlympics+60-second):(" "+(String)(secondOlympics+60-second))));

}
//*******************Countdown function end*************************

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

  drawClock(hour,minute,second,dayOfMonth,month,year,days[dayOfWeek]);
	countDownClock(hour,minute,second);
  delay(1000);
}
