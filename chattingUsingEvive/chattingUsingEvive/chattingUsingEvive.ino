/*
 * evive programming 
 * 
 */
void setup()
{
    Serial.begin(9600);
    Serial3.begin(115200);
    Serial2.begin(14400);
    Serial3.println("AT+RST");
    delay(100);
    Serial3.println("AT+CWMODE=2");
       
}
int chating=0,f=0,c=0;
int ipd=0,cal=0;
void loop()
{  
  
   
    if (Serial3.available()){
        while (Serial3.available()&&f==0&&chating==0) {
            Serial.write((char)Serial3.read());
      }
      
      if(chating==1&&Serial3.available())
      { 
          int i;
          while(ipd==0&&Serial3.available()){
            while(Serial3.available())
            {
              Serial2.write(c); 
              char c=(char)Serial3.read();
              if(c==':')
                { long t=millis();
                  
                  ipd=1;
                  while(!Serial3.available())
                    {  
                      if(millis()>t+900) 
                         { ipd=0;
                           break;
                         }  
                    }
                  break;
                }   
            }
            
          }
          
          while(ipd==1&&Serial3.available()){
            if(cal==0)
              {  Serial.print("other-->");
                  cal=1;
                  
              }
              if(!Serial.available())
            {
              delay(10);
              if(!Serial.available())
                ipd=0;  
          }
            while(Serial3.available())
              Serial.write(Serial3.read());
            Serial.println("");  
            
                    
          }
          
          
      }
     
      if(f>0)
      {   
           //Serial3.println("you-->");
           while (Serial3.available()) {
            Serial2.write(Serial3.read());
        }
        f--;
      }
     
        cal=0;
    }
    if (Serial.available()){
      delay(1000);
      cal=0;
      
      String command="";
      while (Serial.available()) {
        command+=(char)Serial.read();
      }
      
      if(chating==1)  
        {
          Serial3.print("AT+CIPSEND=0,");
          Serial3.println(command.length()+10);
          //Serial3.println('\r');
          delay(500);
          Serial3.print("*OTHER*-->");  // 5 TAB SPACE 
          Serial3.println(command);
          Serial3.write(10);
          Serial.print("*you*-->");
          Serial.println(command);
          f=40;
        }
      else  
        Serial3.println(command);
      
      if(command=="AT+CIPSERVER=1,1338")     //START GHE CHATTING THIS MAKE NO NEED OF WRITING CIPSEND CMD
        { chating=1;
        Serial3.println(command);
          Serial.println("started");  
      }
      

  }

}

