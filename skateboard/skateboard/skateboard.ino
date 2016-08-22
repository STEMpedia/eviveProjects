/*
 * Developed by - Madhukant and Tushar Gupta
 * Proximity sensor code developed by Dhrupal R Shah
 * Email id's :- kantmadhu956@gmail.com or contact@evive.cc
 * Dated: August 22, 2016
 * 
 * Notes: Tested with evive, HC-05 as Bluetooth module
 * Android App: Arduino Bluetooth Controller
 * https://play.google.com/store/apps/details?id=eu.jahnestacado.arduinorc&hl=en
 * Set the following values for keys in RC controller menu in App:
 * * Up = "1" start or increase speed
 * * Down = "3" decrease speed
 * * Right = "f" emergency stop
 * * Left = "0" for start smoothly
 * * Trianlge = "l" for starting lights ro increasing brightness of lights //letter L in small letters
 * * Cross = "o" for decreasing brightness of lights
 */

//Motor.h library can be downloaded from https://github.com/evivetoolkit/eviveProjects/tree/master/skateboard/motor
#include <motor.h>
// include the SPI library:
#include <SPI.h>

//Since the output of proximity is 0 or 12V, evive's sensing channel at ProbeV (has range of -30V to +30V) is used 
int SPI_ADC_SS = 35;    // SPI ADC SS
int ADC_RDY = 32;      // ADC Ready pin
#define ADC_SPIMaxSpeed 5600000
#define ADC_SPIMode SPI_MODE3
#define ADC_SPIDataOrder MSBFIRST
#define ADE791X_REG_V1WV           0x01    /* Instantaneous value of Voltage V1 */
#define ADE791X_MUL_V1WV           0.006485
#define ADE791X_OFFSET_V1WV        362760   
#define ADE791X_READ    0x04

SPISettings ADCSetting(ADC_SPIMaxSpeed,ADC_SPIDataOrder,ADC_SPIMode);

Motor mymotor(28,29,44);
Motor lights(30,31,45);
void setup() {
  ade791x_init();
  delay(100);
  Serial3.begin(9600);
  mymotor.stopMotor();
  Serial.begin(9600);
}
int speedMotor=-90;
int brightness=0;
String inputString="";
int junk;

void ade791x_init(void)
{
  pinMode(SPI_ADC_SS, OUTPUT);
  pinMode(ADC_RDY, INPUT);
  // take the SS pin high to de-select the chip:
  digitalWrite(SPI_ADC_SS, HIGH);
  // initialize SPI:
  SPI.begin();
}


///////////////////////////////////////////////////////////////////////////////
// function name: ade791x_read_v1()
// inputs: none
// outputs: 4 byte / signed long value read from ADC V1WV register
// Description: function that reads ADE791x ADC V1WV register over SPI
// interface. 
///////////////////////////////////////////////////////////////////////////////

long ade791x_read_v1(void)
{
  unsigned char addr = ADE791X_REG_V1WV;
  long value = 0;  // stores value to return
  long tempValue1 = 0, tempValue2 = 0 , tempValue3 = 0;  
  unsigned char opcode; // stores opcode
  
  addr = addr << 3;  // left shift address by 3 bits
  opcode = (addr | ADE791X_READ);     // forms opcode byte
//  Serial.print ("opcode: ");    // for debug only
//  Serial.println(opcode, BIN);  // for debug only

  SPI.beginTransaction(ADCSetting);
  // take the SS pin low to select the chip:
//  digitalWrite(SPI_ADC_SS, LOW);  // bring SS2 pin low
  PORTC &= ~_BV(PC2);
  SPI.transfer(opcode);        // send out opcode
//  value  = SPI.transfer(0xFF) * 0x10000;  // read MS Byte
////  tempValue1=value;  
//  value |= SPI.transfer(0xFF) * 0x100;  // read mid Byte
////  tempValue2=value;  
//  value |= SPI.transfer(0xFF);  // LS Byte

  tempValue1 = SPI.transfer(0xFF);  // read MS Byte
//  tempValue1=value;  
  tempValue2 = SPI.transfer(0xFF);  // read mid Byte
//  tempValue2=value;  
  tempValue3 = SPI.transfer(0xFF);  // LS Byte

  // take the SS pin high 
//
//to de-select the chip:
  //digitalWrite(SPI_ADC_SS, HIGH);  
  PORTC |= _BV(PC2);
  
  SPI.endTransaction();  

  tempValue1  = tempValue1 * 0x10000;
  tempValue2 = tempValue1 | tempValue2 * 0x100;
  value = tempValue2 | tempValue3;
    
  value = value <<8;        // sign extends value to 32 bit
  value = value / 0x100;    // converts back value to 24 bit but now sign extended
  value = (value - 362760.0)*0.006485; //ADE791X_MUL_V1WV;

  #ifdef __DEBUG__  
//  Serial.print ("V1: ");
//  Serial.println (value);
  #endif  
  return value;
}

void loop() {
  //if value is greater than 6000, stop skateboard.
 int proxyVal = ade791x_read_v1 ();
  if(proxyVal>3000)
   {
      mymotor.stopMotor();
   }
  Serial.println(proxyVal);
 if(Serial3.available()){
  while(Serial3.available())
    {
      char inChar = (char)Serial3.read(); //read the input
      inputString += inChar;        //make a string of the characters coming onSerial3
    }
   Serial3.println(inputString);
   Serial3.println(123);
    while (Serial3.available() > 0)  
    { junk =Serial3.read() ; }      // clear the serial buffer
    
    if(inputString == "0"){         //in case of 'a' turn the LED on
      mymotor.startSmoothly(speedMotor);
    }
    else if(inputString=="9")
    {
      lights.startSmoothly(brightness);
    }
    else if(inputString=="1")
      {
        if(speedMotor<225)
        mymotor.moveMotor(speedMotor=speedMotor+30);
      }
    else if(inputString=="3"){
        if(speedMotor>-225)
         mymotor.moveMotor(speedMotor=speedMotor-30);
    }
    else if(inputString=="l"){
      
      lights.moveMotor(brightness=brightness+60);
    }
    else if(inputString=="o"){
      if(brightness>-195)
      lights.moveMotor(brightness=brightness-60);
    }
    else if(inputString=="f"){
      mymotor.stopMotor();
    }
    
    inputString = "";
  }

}
