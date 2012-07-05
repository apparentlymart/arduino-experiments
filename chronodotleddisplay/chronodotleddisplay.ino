#include <Wire.h>

const int maxDataPin = 11;
const int maxClockPin = 13;
const int maxLoadPin = 10;
const int colonPin = 9;
const int hourButtonInterrupt = 0;
const int minuteButtonInterrupt = 1;
const int hourButtonPin = 2;
const int minuteButtonPin = 3;

int seconds;
volatile int minutes;
volatile int hours;
int date;
int month;
int year;
volatile int writeTime = false;
unsigned long lastButtonMillis = 0;
volatile unsigned int timeHasBeenSet = true;

const byte digits[] = {
    B00111111,
    B00000110,
    B01011011,
    B01001111,
    B01100110,
    B01101101,
    B01111101,
    B00000111,
    B01111111,
    B01101111,
    B01110111,
    B01111100,
    B00111001,
    B01011110,
    B01111001,
    B01110001,
    B00000000,
};

void setMaxRegister(byte regCode, byte value) {
    digitalWrite(maxLoadPin, LOW);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, value);
    digitalWrite(maxLoadPin, HIGH);
}

byte dec_to_bcd(byte val) {
  return ( (val/10*16) + (val%10) );
}

byte bcd_to_dec(byte val) {
  return ( (val/16*10) + (val%16) );
}

void hourButtonPressed() {
  unsigned long time = millis();
  if ((time - lastButtonMillis) > 150) {
    int decHours = bcd_to_dec(hours);
    hours = dec_to_bcd((decHours + 1) % 24);
    writeTime = true;
    timeHasBeenSet = true;
    updateDisplay();
  }
  lastButtonMillis = time;
}

void minuteButtonPressed() {
  unsigned long time = millis();
  if ((time - lastButtonMillis) > 150) {
    int decMinutes = bcd_to_dec(minutes);
    minutes = dec_to_bcd((decMinutes + 1) % 60);
    writeTime = true;
    timeHasBeenSet = true;
    updateDisplay();
  }
  lastButtonMillis = time;
}

void updateDisplay() {
   setMaxRegister(0x1, digits[hours >> 4]);
   setMaxRegister(0x2, digits[hours & 0x0f]);
   setMaxRegister(0x3, digits[minutes >> 4]);
   setMaxRegister(0x4, digits[minutes & 0x0f]);
}

void updateTime() {
    Wire.beginTransmission(104);
    Wire.write(0);
    Wire.endTransmission();
    Wire.requestFrom(104, 7);
    while (Wire.available()) {
      seconds = Wire.read() & 0x7f;
      minutes = Wire.read();
      hours = Wire.read() & 0x3f;
      Wire.read(); // discard day
      date = Wire.read();
      month = Wire.read();
      year = Wire.read();
    }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  updateTime();
  if (hours == 0 && minutes == 0) {
    timeHasBeenSet = false;
  }
  /*
  Wire.beginTransmission(104);
  Wire.write(0);
  Wire.write(0); // seconds
  Wire.write(0); // minutes
  Wire.write(0); // hours
  Wire.write(0); // day (not used)
  Wire.write(0); // date
  Wire.write(0); // month
  Wire.write(0); // year
  Wire.endTransmission();*/
  pinMode(maxDataPin, OUTPUT);
  pinMode(maxClockPin, OUTPUT);
  pinMode(maxLoadPin, OUTPUT);
  pinMode(colonPin, OUTPUT);
  setMaxRegister(0xa, 8); // intensity
  setMaxRegister(0xb, 7); // scan limit
  setMaxRegister(0xf, 0); // display test off
  setMaxRegister(0x9, 0x00); // decode mode off
  setMaxRegister(0xc, 1); // activate display
  pinMode(hourButtonPin, INPUT);
  pinMode(minuteButtonPin, INPUT);
  attachInterrupt(hourButtonInterrupt, hourButtonPressed, RISING);
  attachInterrupt(minuteButtonInterrupt, minuteButtonPressed, RISING);
}

void loop() {
  unsigned int colon = true;
  while (1) {
    if (writeTime) {
      Wire.beginTransmission(104);
      Wire.write(1);
      Wire.write(minutes);
      Wire.write(hours);
      Wire.endTransmission();
      writeTime = false; 
    }
    Wire.beginTransmission(104);
    Wire.write(0);
    Wire.endTransmission();
    Wire.requestFrom(104, 7);
    updateTime();
    updateDisplay();
    colon = ! colon;
    digitalWrite(colonPin, colon ? LOW : HIGH);
    int intensity = timeHasBeenSet ? 8 : (colon ? 8 : 0);
    setMaxRegister(0xa, intensity); // intensity
    delay(500);
  }
}

