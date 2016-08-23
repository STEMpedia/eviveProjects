/*
 * Tweet from ESP via taking text from keypad
 * Taken help from - http://community.thingspeak.com/tutorials/arduino/update-twitter-with-thingtweet-and-arduino-ethernet-shield/
 * Developed by Madhukant(kantmadhu956@gmail.com) & Tushar Gupta (tushargupta5197@gmail.com)
 * Date modified - 7/3/2016
 */
#include <Wire.h>
#include <Keypad.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define TFT_CS     48
#define TFT_RST    47  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     49

Adafruit_ST7735 lcd = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


// definations
#define DEBUG true

#define APIKEY "9Y26X3INFNTUIIP5" //  your thingspeak twitter api key 
#define TARGET_IP "api.thingspeak.com" // direction IP thingspeak
#define TARGET_PORT "80" // port 80
#define ID "Jarvis"  // name of wireless access point to connect to 
#define PASS "wehavehulk"  // wifi password    

boolean tweet = false;
//*******************text variables*******************************
char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};
byte rowPins[ROWS] = {3,2,5,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,9,10,11}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 
//*****************scientific buttons******************

int curx=0,cury=0;
char msg[140];
int space=7;
int spacey=10;

int waittime=500;

int times[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long timelapse=millis();
int index=0;
//*****************************************************
void text(){
  while(1){
      char c;
  
  customKey = customKeypad.getKey();
  if(customKey!=NO_KEY)
  {
    if(customKey=='=')
      break;
  switch(customKey)
  {
     case '1':
    if(times[1]==0)
      { c='@';
        msg[index]=c;
        index++;
        times[1]=1;
        timelapse=millis();
      }
    else if(times[1]==1)
    {
      index--;
      c='#';
      msg[index]=c;
      index++;
      curx-=space;
      times[1]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='.';
      msg[index]=c;
      index++;
      curx-=space;
      times[1]=0;
      timelapse=0;
    }
    break;


    
    case '2':
    if(times[2]==0)
      { c='a';
        msg[index]=c;
        index++;
        times[2]=1;
        timelapse=millis();
      }
    else if(times[2]==1)
    {
      index--;
      c='b';
      msg[index]=c;
      index++;
      curx-=space;
      times[2]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='c';
      msg[index]=c;
      index++;
      curx-=space;
      times[2]=0;
      timelapse=0;
    }
    break;

    
    case '3':
    if(times[3]==0)
      { c='d';
        msg[index]=c;
        index++;
        times[3]=1;
        timelapse=millis();
      }
    else if(times[3]==1)
    {
      index--;
      c='e';
      msg[index]=c;
      index++;
      curx-=space;
      times[3]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='f';
      msg[index]=c;
      index++;
      curx-=space;
      times[3]=0;
      timelapse=0;
    }
    break;

        case '4':
    if(times[4]==0)
      { c='g';
        msg[index]=c;
        index++;
        times[4]=1;
        timelapse=millis();
      }
    else if(times[4]==1)
    {
      index--;
      c='h';
      msg[index]=c;
      index++;
      curx-=space;
      times[4]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='i';
      msg[index]=c;
      index++;
      curx-=space;
      times[4]=0;
      timelapse=0;
    }
    break;


            case '5':
    if(times[5]==0)
      { c='j';
        msg[index]=c;
        index++;
        times[5]=1;
        timelapse=millis();
      }
    else if(times[5]==1)
    {
      index--;
      c='k';
      msg[index]=c;
      index++;
      curx-=space;
      times[5]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='l';
      msg[index]=c;
      index++;
      curx-=space;
      times[5]=0;
      timelapse=0;
    }
    break;


            case '6':
    if(times[6]==0)
      { c='m';
        msg[index]=c;
        index++;
        times[6]=1;
        timelapse=millis();
      }
    else if(times[6]==1)
    {
      index--;
      c='n';
      msg[index]=c;
      index++;
      curx-=space;
      times[6]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='o';
      msg[index]=c;
      index++;
      curx-=space;
      times[6]=0;
      timelapse=0;
    }
    break;

            case '7':
    if(times[7]==0)
      { c='p';
        msg[index]=c;
        index++;
        times[7]=1;
        timelapse=millis();
      }
    else if(times[7]==1)
    {
      index--;
      c='q';
      msg[index]=c;
      index++;
      curx-=space;
      times[7]=2;
      timelapse=millis();  
    }
    else if(times[7]==2)
    {
      index--;
      c='r';
      msg[index]=c;
      index++;
      curx-=space;
      times[7]=3;
      timelapse=millis();
    }
       else
    {
      index--;
      c='s';
      msg[index]=c;
      index++;
      curx-=space;
      times[7]=0;
      timelapse=0;
    }
    break;

            case '8':
    if(times[8]==0)
      { c='t';
        msg[index]=c;
        index++;
        times[8]=1;
        timelapse=millis();
      }
    else if(times[8]==1)
    {
      index--;
      c='u';
      msg[index]=c;
      index++;
      curx-=space;
      times[8]=2;
      timelapse=millis();  
    }
    else
    {
      index--;
      c='v';
      msg[index]=c;
      index++;
      curx-=space;
      times[8]=0;
      timelapse=0;
    }
    break;


                case '9':
    if(times[9]==0)
      { c='w';
        msg[index]=c;
        index++;
        times[9]=1;
        timelapse=millis();
      }
    else if(times[9]==1)
    {
      index--;
      c='x';
      msg[index]=c;
      index++;
      curx-=space;
      times[9]=2;
      timelapse=millis();  
    }
    else if(times[9]==2)
    {
      index--;
      c='y';
      msg[index]=c;
      index++;
      curx-=space;
      times[9]=3;
      timelapse=millis();
    }
       else
    {
      index--;
      c='z';
      msg[index]=c;
      index++;
      curx-=space;
      times[9]=0;
      timelapse=0;
    }
    break;
    case 'C':
    {
      if(curx!=0)
        curx=curx-space;
      else 
        {
          curx=133;
          int tempy=cury;
          cury-=spacey;
          
        }
      msg[index-1]='\0';
      if(index>0)
      index--;
      
      c=' ';
      //lcd.setCursor(curx,cury);
      //lcd.print(".");
    }
    break;
    case '0':
    c=' ';
    msg[index]=c;
    index++;
    curx+=space;
    break;
  }
  lcd.setCursor(curx,cury);
  if(c<='z'&&c>='a'||c==' '||c=='@'||c=='#'||c=='.')
  {  lcd.print(c);
      if(c!=' ')
      curx+=space;
  }
  Serial.println(msg);
  Serial.println(index);

  
  }
 if(millis()>timelapse+waittime)
  setallzero(); 
  if(curx>=140&&millis()>timelapse+waittime){
    curx=0;
    cury+=spacey;
  }
  }
  tweet=true;
}
void setup()
{
	Serial.begin(115200); // debug serial port
  Serial3.begin(115200); // esp serial port
 pinMode(38,INPUT);
    lcd.initR(INITR_BLACKTAB);  
  lcd.fillScreen(ST7735_BLACK);
  lcd.setRotation(1);     //to set the TFT screen Landscape
  lcd.setTextWrap(false);
  lcd.setTextColor(ST7735_WHITE,ST7735_BLACK);

  delay(1000); // initial delay

  sendData("AT+RST\r\n",1000,DEBUG); // reset ESP8266

    sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure ESP8266 mode 
   	
   	// connect to internet via wireless network  
    String cmd="AT+CWJAP=\"";  
    cmd+=ID;
    cmd+="\",\"";
    cmd+=PASS;
    cmd+="\"";      
	sendData( cmd+"\r\n",1000,DEBUG); 
    
    delay(1000);

    sendData("AT+CIPMUX=0\r\n",1000,DEBUG); // Configure server connection type 
    
}
 
void loop()
{ 
    text();
   	String  twitter_status = msg;
    lcd.fillScreen(ST7735_BLACK);
    lcd.setCursor(0,0);
    lcd.print("Message Recieved press button to tweet");
    delay(1000);
   	if(digitalRead(38) == true && !tweet){
   		tweet = true;
      lcd.fillScreen(ST7735_BLACK);
      lcd.setCursor(0,0);
      lcd.print("Preparing Tweet");
   	}

   	if(tweet){
	    String connection_command = "AT+CIPSTART=\"TCP\",\""; 
	    connection_command += TARGET_IP;
	    connection_command += "\",80\r\n";         
     
	    sendData(connection_command,1000,DEBUG);        

	    // Create HTTP POST Data             
	    String tsData = "api_key=" APIKEY "&status=" + twitter_status ;    
	     
	    String tweet_request = "POST /apps/thingtweet/1/statuses/update HTTP/1.1\n";
	    tweet_request += "Host: api.thingspeak.com\n";
	    tweet_request += "Connection: close\n";
	    tweet_request += "Content-Type: application/x-www-form-urlencoded\n";
	    tweet_request += "Content-Length: ";
	    tweet_request += tsData.length();
	    tweet_request += "\n\n";
	    tweet_request += tsData;
	       
	      
		String send_request = "AT+CIPSEND=";     
		send_request += tweet_request.length();
		send_request +="\r\n";     
		  
		sendData(send_request,1000,DEBUG);
		sendData(tweet_request,1000,DEBUG);   

		// close server connection after tweet            
		sendData("AT+CIPCLOSE=0\r\n",1500,DEBUG);
		     
		delay(2000); // thingspeak delay
    
    lcd.fillScreen(ST7735_BLACK);
    lcd.setCursor(0,0);
    lcd.print("Twitter Status- ");
    //lcd.setCursor(0,20);
    lcd.print("Updated");

    delay(8000); // thingspeak delay
		tweet = false; 
 	}
}
 
// send AT command function 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    Serial3.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(Serial3.available())
      {
        // The esp has data so display its output to the serial window 
        char c = Serial3.read(); // read the next character.
        response += c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
void setallzero(){
  int i;
  for(i=0;i<14;i++)
    times[i]=0;
}
