// Example 54.1 - PCF8563 RTC write/read demonstration

#include "Wire.h"
#define PCF8563address 0x51

byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
String days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

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

void readPCF8563()
// this gets the time and date from the PCF8563
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

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  // change the following to set your initial time
  second = 0;
  minute = 40;
  hour = 21;
  dayOfWeek = 0;
  dayOfMonth = 29;
  month = 5;
  year = 16;
  // comment out the next line and upload again to set and keep the time from resetting every reset
  setPCF8563();
}

void loop()
{
  readPCF8563();
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
  delay(1000);
}
