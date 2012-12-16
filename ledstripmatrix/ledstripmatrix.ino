#include "LPD8806.h"
#include "SPI.h"

int nLEDs = 160;
int dataPin  = 2;
int clockPin = 3;
int hiPixels[] = {
  5,   7,   11,
  36,  34,  32,  30,
  51,  53,  57,
  84,  83,  82,  80, 78,
  99, 101, 103, 105,
 132, 130, 128,
 145, 147, 149, 151,
};

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

  for (int i = 0; i < (sizeof(hiPixels) / sizeof(int)); i++) {
    strip.setPixelColor(hiPixels[i], 200, 200, 0);
  }

  strip.show();
  delay(5000);
}


