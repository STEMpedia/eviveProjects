/*
 * Developed by- Madhukant (kantmadhu956@gmail.com) & Tushar Gupta(tusharg5197@gmail.com)
 * Date modified - 29/6/2016
 */
#include <motor.h>

#define limit1 500
#define limit2 900
Motor pump(29,28,44);
int speedg =250;
int soilpin=A4;
int msgflag=0;
void setup() {
Serial.begin(9600);
Serial3.begin(115200);
Serial3.println("AT+CWMODE=2");
delay(500);
}
int flag=0;
long t=millis();
String reading="";
void loop() {
  int moisture=map(analogRead(soilpin),0,1023,0,9);
 if (Serial3.available()){
    while (Serial3.available()){
      char c=Serial3.read();
      Serial.write(c);
    }
 }
if (Serial.available()){
    delay(1000);
    String command="";
    while (Serial.available()){
      command+=(char)Serial.read();
    }
    Serial3.println(command);
    if(command=="AT+CIPSERVER=1,1338")
    flag=1;
    
  }
  while(flag==1)
    {
      reading="\b\b";
      if(msgflag==1)
        reading+=(String)moisture;
      reading=reading+" \n";
      Serial3.print("AT+CIPSEND=0,");
      Serial3.println(reading.length());
      delay(400);   
      Serial3.println(reading);
      Serial.println(analogRead(A4));
    }
    if(millis()>t+2000){
if(analogRead(A4)>limit2)
  { pump.moveMotor(speedg);
    msgflag=1;
    //digitalWrite(28,HIGH);
  }
else if(analogRead(A4)<limit1)
 { pump.stopMotor();
   if(msgflag=1)
     { reading="Your plant has been watered !!  ";
       msgflag=0;
     }
   //digitalWrite(28,LOW);
 }
}

}
