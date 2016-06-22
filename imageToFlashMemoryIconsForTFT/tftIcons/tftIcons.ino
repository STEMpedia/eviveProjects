//Checked with evive / Arduino Mega
//Compatible with SPI based TFT (user can modify TFT codes and library)
//Date: 20160623
//Developer: Dhrupal R Shah

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#include "bitmaps.h"
#include "bitmapsLarge.h"

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     48
#define TFT_RST    47  // you can also connect this to the Arduino reset
                      // in which case, set this #define pin to 0!
#define TFT_DC     49

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setup() {
	tft.initR(INITR_BLACKTAB);
	tft.setRotation(1);
	tft.fillScreen(ST7735_BLACK);

//Case 1: Monochrome Bitmaps 
//	tft.drawBitmap(0,0,bell,16,16,ST7735_WHITE);
//	tft.drawBitmap(0,0,semiCircle, 50, 25, ST7735_WHITE);
//  tft.drawBitmap(0,0,myBitmap, 71, 71, ST7735_CYAN);
//  tft.drawBitmap(10,0,wifi_icon, 20, 15, ST7735_WHITE);
//  tft.drawBitmap(130,0,battery_icon, 20, 15, ST7735_WHITE);
//  tft.drawBitmap(70,0,user_icon, 15, 15, ST7735_WHITE);
//  tft.drawBitmap(0,0,evive_logo, 71, 71, ST7735_CYAN);


//Case 2: Multi Colored Images/Icons
  int h = 128,w = 97, row, col, buffidx=0;
  for (row=0; row<h; row++) { // For each scanline...
    for (col=0; col<w; col++) { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, pgm_read_word(evive_in_hand + buffidx));
      buffidx++;
    } // end pixel
  }
}

void loop() {
}
