#include "LPD8806.h"
#include "SPI.h"

int nLEDs = 160;
int dataPin  = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void setup() {
    strip.begin();
    strip.show();
}

void loop() {
  strip.setPixelColor(0, 175, 0, 0);
  strip.setPixelColor(0 + 20 - 1, 175, 0, 0);

  strip.setPixelColor(0 + 20, 175, 0, 0);
  strip.setPixelColor(0 + 20 + 24 - 1, 175, 0, 0);

  strip.setPixelColor(0 + 20 + 24, 175, 0, 0);
  strip.setPixelColor(0 + 20 + 24 + 24 - 1, 175, 0, 0);

  strip.setPixelColor(0 + 20 + 24 + 24, 175, 0, 0);
  strip.setPixelColor(0 + 20 + 24 + 24 + 24 - 1, 175, 0, 0);

  strip.show();
  delay(5000);
}

