/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrices[3] = {
  Adafruit_BicolorMatrix(),
  Adafruit_BicolorMatrix(),
  Adafruit_BicolorMatrix()
};

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");

  int i;

  for (i = 0; i < 3; i++) {
    matrices[i].begin(0x70 + i);
    matrices[i].setBrightness(0);
    matrices[i].setRotation(3);
    matrices[i].clear();
  }

  uint16_t color = LED_YELLOW;

  matrices[0].drawFastHLine(1, 0, 2, color);
  matrices[0].drawFastHLine(1, 3, 2, color);
  matrices[0].drawFastHLine(1, 6, 2, color);
  matrices[0].drawFastHLine(6, 0, 2, color);
  matrices[0].drawFastHLine(6, 3, 2, color);
  matrices[0].drawFastHLine(6, 6, 2, color);
  matrices[0].drawFastVLine(0, 0, 7, color);
  matrices[0].drawFastVLine(3, 0, 7, color);
  matrices[0].drawFastVLine(5, 0, 7, color);

  matrices[1].drawFastVLine(0, 0, 7, color);
  matrices[1].drawFastVLine(6, 0, 7, color);
  matrices[1].drawPixel(3, 2, color);
  matrices[1].drawPixel(3, 4, color);
  matrices[1].drawPixel(7, 0, color);
  matrices[1].drawPixel(7, 3, color);
  matrices[1].drawPixel(7, 6, color);

  matrices[2].drawFastHLine(4, 0, 2, color);
  matrices[2].drawFastHLine(4, 3, 2, color);
  matrices[2].drawFastHLine(4, 6, 2, color);
  matrices[2].drawFastVLine(1, 0, 7, color);
  matrices[2].drawFastVLine(3, 0, 7, color);
  matrices[2].drawFastVLine(6, 0, 7, color);
  matrices[2].drawPixel(0, 0, color);
  matrices[2].drawPixel(0, 3, color);
  matrices[2].drawPixel(0, 6, color);

  for (i = 0; i < 3; i++) {
    matrices[i].writeDisplay();
  }  

}

void loop() {

  delay(1000);

  //matrix.setRotation(0);
}

