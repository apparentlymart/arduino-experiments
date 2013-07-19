
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_BicolorMatrix matrices[3] = {
  Adafruit_BicolorMatrix(),
  Adafruit_BicolorMatrix(),
  Adafruit_BicolorMatrix()
};

/*
 * For rendering we emulate a 7-segment LED display for each digit.
 * The following tells us which of the segments (in gfedcba order)
 * should be illuminated for each numeral, and then we'll draw lines
 * on the display for each illuminated segment.
 */
char patterns[] = {
    0x3f,
    0x06,
    0x5b,
    0x4f,
    0x66,
    0x6d,
    0x7d,
    0x07,
    0x7f,
    0x6f,
    0x77,
    0x7c,
    0x39,
    0x5e,
    0x79,
    0x71,
};

#define SEG_A 0b00000001
#define SEG_B 0b00000010
#define SEG_C 0b00000100
#define SEG_D 0b00001000
#define SEG_E 0b00010000
#define SEG_F 0b00100000
#define SEG_G 0b01000000

#define SEGMENT_ON(value, segment) ((patterns[value] & segment) != 0)

char ht = 0; // hour tens
char hu = 0; // hour units
char mt = 0; // minute tens
char mu = 0; // minute units
char colon = 0;

void update_display() {
    uint16_t color = LED_YELLOW;

    int i;

    for (i = 0; i < 3; i++) {
        matrices[i].clear();
    }

    // This is a pretty dumb way to implement this but it's fine for an prototype
    if (ht > 0) {
        if SEGMENT_ON(ht, SEG_A) matrices[0].drawFastHLine(0, 0, 4, color);
        if SEGMENT_ON(ht, SEG_B) matrices[0].drawFastVLine(3, 0, 4, color);
        if SEGMENT_ON(ht, SEG_C) matrices[0].drawFastVLine(3, 3, 4, color);
        if SEGMENT_ON(ht, SEG_D) matrices[0].drawFastHLine(0, 6, 4, color);
        if SEGMENT_ON(ht, SEG_E) matrices[0].drawFastVLine(0, 3, 4, color);
        if SEGMENT_ON(ht, SEG_F) matrices[0].drawFastVLine(0, 0, 4, color);
        if SEGMENT_ON(ht, SEG_G) matrices[0].drawFastHLine(0, 3, 4, color);
    }

    if SEGMENT_ON(hu, SEG_A) {
        matrices[0].drawFastHLine(5, 0, 3, color);
        matrices[1].drawFastHLine(0, 0, 1, color);
    }
    if SEGMENT_ON(hu, SEG_B) matrices[1].drawFastVLine(0, 0, 4, color);
    if SEGMENT_ON(hu, SEG_C) matrices[1].drawFastVLine(0, 3, 4, color);
    if SEGMENT_ON(hu, SEG_D) {
        matrices[0].drawFastHLine(5, 6, 3, color);
        matrices[1].drawFastHLine(0, 6, 1, color);
    }
    if SEGMENT_ON(hu, SEG_E) matrices[0].drawFastVLine(5, 3, 4, color);
    if SEGMENT_ON(hu, SEG_F) matrices[0].drawFastVLine(5, 0, 4, color);
    if SEGMENT_ON(hu, SEG_G) {
        matrices[0].drawFastHLine(5, 3, 3, color);
        matrices[1].drawFastHLine(0, 3, 1, color);
    }

    if (colon) {
        matrices[1].drawPixel(3, 2, color);
        matrices[1].drawPixel(3, 4, color);
    }

    if SEGMENT_ON(mt, SEG_A) {
        matrices[1].drawFastHLine(6, 0, 2, color);
        matrices[2].drawFastHLine(0, 0, 2, color);
    }
    if SEGMENT_ON(mt, SEG_B) matrices[2].drawFastVLine(1, 0, 4, color);
    if SEGMENT_ON(mt, SEG_C) matrices[2].drawFastVLine(1, 3, 4, color);
    if SEGMENT_ON(mt, SEG_D) {
        matrices[1].drawFastHLine(6, 6, 2, color);
        matrices[2].drawFastHLine(0, 6, 2, color);
    }
    if SEGMENT_ON(mt, SEG_E) matrices[1].drawFastVLine(6, 3, 4, color);
    if SEGMENT_ON(mt, SEG_F) matrices[1].drawFastVLine(6, 0, 4, color);
    if SEGMENT_ON(mt, SEG_G) {
        matrices[1].drawFastHLine(6, 3, 2, color);
        matrices[2].drawFastHLine(0, 3, 2, color);
    }
    
    if SEGMENT_ON(mu, SEG_A) matrices[2].drawFastHLine(3, 0, 4, color);
    if SEGMENT_ON(mu, SEG_B) matrices[2].drawFastVLine(6, 0, 4, color);
    if SEGMENT_ON(mu, SEG_C) matrices[2].drawFastVLine(6, 3, 4, color);
    if SEGMENT_ON(mu, SEG_D) matrices[2].drawFastHLine(3, 6, 4, color);
    if SEGMENT_ON(mu, SEG_E) matrices[2].drawFastVLine(3, 3, 4, color);
    if SEGMENT_ON(mu, SEG_F) matrices[2].drawFastVLine(3, 0, 4, color);
    if SEGMENT_ON(mu, SEG_G) matrices[2].drawFastHLine(3, 3, 4, color);
  
    for (i = 0; i < 3; i++) {
        matrices[i].writeDisplay();
    }  
    
}

void update_clock() {
    Wire.beginTransmission(104);
    Wire.write(0);
    Wire.endTransmission();
    Wire.requestFrom(104, 3);
    while (Wire.available()) {
        int seconds = Wire.read() & 0x7f;
        int minutes = Wire.read();
        int hours = Wire.read();
        ht = hours / 16;
        hu = hours % 16;
        mt = minutes / 16;
        mu = minutes % 16;
    }    
}

void setup() {
      
    int i;
      
    for (i = 0; i < 3; i++) {
        matrices[i].begin(0x70 + i);
        matrices[i].setBrightness(0);
        matrices[i].setRotation(3);
        matrices[i].clear();
    }
}

void loop() {

    update_clock();
    colon = 1;
    update_display();
    delay(500);
    colon = 0;
    update_display();
    delay(500);

    mu++;
    if (mu > 9) {
        mt++;
        mu = 0; 
    }
    if (mt > 9) {
        hu++;
        mt = 0;
    }
    if (hu > 9) {
        ht++;
        hu = 0;
    }
    if (ht > 9) {
        ht = hu = mt = mu = 0;
    }
}

