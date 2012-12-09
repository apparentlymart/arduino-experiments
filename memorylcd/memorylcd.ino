/* Hardware setup:  
Sharp Memory Lcd Breakout  <-> Arduino Uno
Name   SLCD PIN    ARDU PIN
VCC 	   1		  5V
SCLK	   2		  13
SDATA      3		  11
SCS	       4  		  10
EXTCOM     5		   3
ENABLE     6		   4
ExtMode	   7		  5V
GND        8          GND
*/

#include <Arduino.h>
#include <SPI.h>

#define SLAVE_SELECT_PIN 10
#define DISP_ENABLE_PIN 4
#define EXTCOM_PIN 3
#define LCD_DELAY 3

#define CMD_CLEAR 0x04
#define CMD_WRITE_ROWS 0x01

#define DEBUG(msg) Serial.println(msg)

unsigned char data[96][96 / 8];

unsigned char font8x8[26][8] = {
  {
    0b01111100,
    0b10000010,
    0b10000010,
    0b11111110,
    0b10000010,
    0b10000010,
    0b10000010,
    0b00000000,
  },
  {
    0b01111110,
    0b10000010,
    0b10000010,
    0b01111110,
    0b10000010,
    0b10000010,
    0b01111110,
    0b00000000,
  },
};

void clear() {
  memset(&data, 0, sizeof(data));
  digitalWrite(SLAVE_SELECT_PIN, HIGH);
  delay(LCD_DELAY);
  SPI.transfer(CMD_CLEAR);
  SPI.transfer(0);
  delay(LCD_DELAY);
  digitalWrite(SLAVE_SELECT_PIN, LOW);
}

void refresh_rows(int start_row, int end_row) {
  digitalWrite(SLAVE_SELECT_PIN, HIGH);
  delay(LCD_DELAY);
  SPI.transfer((char)CMD_WRITE_ROWS);
  for (int row = start_row; row <= end_row; row++) {
    SPI.transfer(row + 1); // display is 1-indexed, array is 0-indexed
    for (int col = 0; col < (96 / 8); col++) {
      SPI.transfer(~data[row][col]);
    }
    SPI.transfer(0); // First 0 signals end of row
  }
  // Second 0 signals end of command
  SPI.transfer(0);
  delay(LCD_DELAY);
  digitalWrite(SLAVE_SELECT_PIN, LOW);
}

void refresh_all() {
  refresh_rows(0, 95);
}

void refresh_row(int row) {
  refresh_rows(row, row);
}

#define setPixel(x, y) data[y][x / 8] |= 0x1 << (x % 8);
#define clrPixel(x, y) data[y][x / 8] &= ~(0x1 << (x % 8));
#define write8Pixels(xbyte, y, pattern) data[y][xbyte] = pattern;
#define set8Pixels(xbyte, y, pattern) data[y][xbyte] |= pattern;
#define clr8Pixels(xbyte, y, pattern) data[y][xbyte] &= ~pattern;

void setup() {
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  analogWrite(3, 127);
  TCCR2B = TCCR2B & 0xFF;

  pinMode(SLAVE_SELECT_PIN, OUTPUT);
  pinMode(DISP_ENABLE_PIN, OUTPUT);
  digitalWrite(DISP_ENABLE_PIN, HIGH);
  SPI.setBitOrder(LSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  SPI.begin();
  clear();
}

void loop() {
  write8Pixels(0, 0, font8x8[0][0]);
  write8Pixels(0, 1, font8x8[0][1]);
  write8Pixels(0, 2, font8x8[0][2]);
  write8Pixels(0, 3, font8x8[0][3]);
  write8Pixels(0, 4, font8x8[0][4]);
  write8Pixels(0, 5, font8x8[0][5]);
  write8Pixels(0, 6, font8x8[0][6]);
  write8Pixels(0, 7, font8x8[0][7]);
  write8Pixels(1, 0, font8x8[1][0]);
  write8Pixels(1, 1, font8x8[1][1]);
  write8Pixels(1, 2, font8x8[1][2]);
  write8Pixels(1, 3, font8x8[1][3]);
  write8Pixels(1, 4, font8x8[1][4]);
  write8Pixels(1, 5, font8x8[1][5]);
  write8Pixels(1, 6, font8x8[1][6]);
  write8Pixels(1, 7, font8x8[1][7]);
  refresh_all();
  delay(4000);
  clear();
}

