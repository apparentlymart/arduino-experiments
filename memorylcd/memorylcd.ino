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
#include "c64font.h"
#include "string.h"
#include "stdio.h"

#define SLAVE_SELECT_PIN 10
#define DISP_ENABLE_PIN 4
#define EXTCOM_PIN 3
#define LCD_DELAY 3

#define CMD_CLEAR 0x04
#define CMD_WRITE_ROWS 0x01

#define DISPLAY_WIDTH 96
#define DISPLAY_HEIGHT 96
#define DISPLAY_ROW_BYTES (DISPLAY_WIDTH / 8)

unsigned char data[DISPLAY_HEIGHT][DISPLAY_ROW_BYTES];
unsigned char display_data_offset = 0; // to allow scrolling without shuffling data about
unsigned char cursor_y = 0;
unsigned char cursor_x = 0;

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
    for (int col = 0; col < DISPLAY_ROW_BYTES; col++) {
      SPI.transfer(~data[(row + display_data_offset) % DISPLAY_HEIGHT][col]);
    }
    SPI.transfer(0); // First 0 signals end of row
  }
  // Second 0 signals end of command
  SPI.transfer(0);
  delay(LCD_DELAY);
  digitalWrite(SLAVE_SELECT_PIN, LOW);
}

void refresh_all() {
  refresh_rows(0, DISPLAY_HEIGHT - 1);
}

void refresh_row(int row) {
  refresh_rows(row, row);
}

#define setPixel(x, y) (data[y][x / 8] |= 0x1 << (x % 8));
#define clrPixel(x, y) (data[y][x / 8] &= ~(0x1 << (x % 8)));
#define write8Pixels(xbyte, y, pattern) (data[y][xbyte] = pattern);
#define set8Pixels(xbyte, y, pattern) (data[y][xbyte] |= pattern);
#define clr8Pixels(xbyte, y, pattern) (data[y][xbyte] &= ~pattern);

void writeText(int xbyte, int y, char * text) {
  for (int row = 0; row < 8; row++) {
    int col = 0;
    for (char * c = text; *c != 0; c++) {
      char sym = (*c) - 32;
      char pixels = pgm_read_byte(&(c64font[sym][row]));
      write8Pixels(xbyte + col, y + row, pixels);
      col++;
    }
  }
  refresh_rows(y, y+8);
}

void scroll(int rows) {
  display_data_offset = (display_data_offset + rows) % DISPLAY_HEIGHT;
}

void print(char * text) {
  Serial.print("------------\nPrinting ");
  Serial.println(text);
  int len = strlen(text);
  char line[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
  int local_cursor_x = cursor_x;
  int local_cursor_y = cursor_y;
  int advance = DISPLAY_ROW_BYTES;
  int pos = 0;
  for (pos = 0; pos < len; pos += advance) {
    advance = DISPLAY_ROW_BYTES - local_cursor_x;
    Serial.print("Drawing from pos = ");
    Serial.print(pos);
    Serial.print(" with advance = ");
    Serial.println(advance);
    local_cursor_y = local_cursor_y % (DISPLAY_HEIGHT / 8);
    strncpy((char*)&line, (char*)&(text[pos]), advance);
    Serial.print("line = ");
    Serial.println((char*)&line);
    Serial.print("Drawing at x = ");
    Serial.print(local_cursor_x);
    Serial.print(" y = ");
    Serial.println(local_cursor_y);
    writeText(local_cursor_x, local_cursor_y * 8, line);
    local_cursor_x = 0;
    local_cursor_y++;
    Serial.print("New pos will be ");
    Serial.println(pos + advance);
  }

  Serial.print("Terminating with pos = ");
  Serial.println(pos);
  
  cursor_y = (cursor_y + ((cursor_x + len)/ DISPLAY_ROW_BYTES)) % (DISPLAY_HEIGHT / 8);
  cursor_x = (cursor_x + len) % DISPLAY_ROW_BYTES;
}
void println(char * text) {
  print(text);
  cursor_y = (cursor_y + 1) % DISPLAY_HEIGHT;
  cursor_x = 0;
}

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
  int i = 0;
  char buf[48] = "         ";
  while (1) {
    delay(2000);
    sprintf(buf, "The quick brown fox jumps over the lazy dog %i", i);
    println(buf);
    i++;
    if (i > 999) i = 0;
  }
  display_data_offset = 0;
  delay(4000);
}


