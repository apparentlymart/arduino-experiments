
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrices[3] = {
  Adafruit_BicolorMatrix(),
  Adafruit_BicolorMatrix(),
  Adafruit_BicolorMatrix()
};

char bell[][8] = {
  {
    0b00011000,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b01111110,
    0b00100000,
  },
  {
    0b00011000,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b01111110,
    0b00010000,
  },
  {
    0b00011000,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b01111110,
    0b00001000,
  },
  {
    0b00011000,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b00111100,
    0b01111110,
    0b00000100,
  },
};

char treered[] = {
  0b00000000,
  0b00000000,
  0b00011000,
  0b00111100,
  0b00011000,
  0b00000000,
  0b00010000,
  0b00000100,
  0b00100000,
  0b00001000,
  0b00100000,
  0b00001000,
  0b01000010,
  0b00111100,
  0b00111100,
  0b00011000,
};
char treegreen[] = {
  0b00000000,
  0b00000000,
  0b00011000,
  0b00111100,
  0b00011000,
  0b00011000,
  0b00111100,
  0b00011000,
  0b00111100,
  0b01111110,
  0b00111100,
  0b01111110,
  0b11111111,
  0b00000000,
  0b00000000,
  0b00000000,
};
char stockingred[] = {
  0b00001110,
  0b00001010,
  0b00001100,
  0b00000110,
  0b00001010,
  0b00011100,
  0b00101100,
  0b00110000,
};
char stockinggreen[] = {
  0b00001110,
  0b00000100,
  0b00000010,
  0b00001000,
  0b00000100,
  0b00000010,
  0b00010000,
  0b00001000,
};

void setup() {
      
    Serial.begin(9600);
    int i;
      
    for (i = 0; i < 3; i++) {
        Serial.println("init");
        Serial.println(i);
        matrices[i].begin(0x70 + i);
        matrices[i].setBrightness(0);
        matrices[i].setRotation(3);
        matrices[i].clear();
        matrices[i].writeDisplay();
    }

}

void drawBitmap(Adafruit_BicolorMatrix *matrix, char *red_data, char *green_data) {
  for (int y = 0; y < 8; y++) {
    char red_row = red_data[y];
    char green_row = green_data[y];
    for (int x = 0; x < 8; x++) {
      // this was originally written this way because I expected 0b01 to be red, 0b10 to be green and thus 0b11 to be yellow
      // but actually the adafruit library isn't set up that way so this was hastily transformed into a more laborious
      // branch-based method. Not sweating too much since it's just a silly Christmas thing, but for any later reader note
      // that this is far from the tidiest and most efficient way to do this. :)
      char red_value = (red_row & (0b10000000 >> x)) ? 1 : 0;
      char green_value = (green_row & (0b10000000 >> x)) ? 1 : 0;
      uint16_t color = 0;
      if (red_value && green_value) {
        color = LED_YELLOW;
      }
      else if (red_value) {
        color = LED_RED;
      }
      else if (green_value) {
        color = LED_GREEN; 
      }
      matrix->drawPixel(x, y, color);
    }
  }
  matrix->writeDisplay();
}

void loop() {
  drawBitmap(&matrices[0], (char*)&bell[1], (char*)&bell[1]);
  delay(100);
  drawBitmap(&matrices[2], (char*)&bell[1], (char*)&bell[1]);
  delay(100);
  drawBitmap(&matrices[1], (char*)&bell[1], (char*)&bell[1]);
  delay(100);
  drawBitmap(&matrices[0], (char*)&bell[2], (char*)&bell[2]);
  delay(100);
  drawBitmap(&matrices[2], (char*)&bell[2], (char*)&bell[2]);
  delay(100);
  drawBitmap(&matrices[1], (char*)&bell[2], (char*)&bell[2]);
  delay(100);
}

