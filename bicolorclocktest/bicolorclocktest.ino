#include <Wire.h>
#include <stdint.h>

const int maxDataPin = 6;
const int maxClockPin = 5;
const int maxLoadPin = 4;

byte hourTens;
byte hourUnits;
byte minTens;
byte minUnits;

const byte digits[] = {
  0b011110,
  0b100001,
  0b100001,
  0b100001,
  0b100001,
  0b100001,
  0b011110,
  0b000000,
  
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000000,

  0b111110,
  0b000001,
  0b000001,
  0b011110,
  0b100000,
  0b100000,
  0b111111,
  0b000000,

  0b111110,
  0b000001,
  0b000001,
  0b011110,
  0b000001,
  0b000001,
  0b111110,
  0b000000,

  0b100001,
  0b100001,
  0b100001,
  0b011111,
  0b000001,
  0b000001,
  0b000001,
  0b000000,

  0b111111,
  0b100000,
  0b100000,
  0b111110,
  0b000001,
  0b000001,
  0b111110,
  0b000000,

  0b011110,
  0b100000,
  0b100000,
  0b111110,
  0b100001,
  0b100001,
  0b011110,
  0b000000,

  0b111111,
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000001,
  0b000000,

  0b011110,
  0b100001,
  0b100001,
  0b011110,
  0b100001,
  0b100001,
  0b011110,
  0b000000,

  0b011110,
  0b100001,
  0b100001,
  0b011111,
  0b000001,
  0b000001,
  0b011110,
  0b000000,

};

void setMaxRegisterAll(byte regCode, byte value) {
    digitalWrite(maxLoadPin, LOW);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, value);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, value);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, value);
    digitalWrite(maxLoadPin, HIGH);
}

void setMaxRegister(byte regCode, uint32_t values) {
    digitalWrite(maxLoadPin, LOW);
    byte valueC = (byte)(values);
    byte valueB = (byte)(values >> 8);
    byte valueA = (byte)(values >> 16);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, valueC);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, valueB);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, valueA);
    digitalWrite(maxLoadPin, HIGH);
}

void updateDisplay() {
    for (int i = 0; i < 7; i++) {
      uint32_t pixels = 0;
      pixels |= hourTens ? (uint32_t)1 << 23 : 0;
      pixels |= (uint32_t)(digits[(hourUnits * 8) + i]) << 16;
      pixels |= (uint32_t)(digits[(minTens * 8) + i] << 7);
      pixels |= (uint32_t)(digits[(minUnits * 8) + i]);
      // colon
      if (i == 2 || i == 4) {
          pixels |= (uint32_t)1 << 14;
      }
      setMaxRegister(i + 1, pixels);
    }
    setMaxRegisterAll(8, 0);
}

void updateTime() {
    Wire.beginTransmission(104);
    Wire.write(1);
    Wire.endTransmission();
    Wire.requestFrom(104, 2);
    int minutes;
    int hours;
    while (Wire.available()) {
        minutes = Wire.read();
        hours = Wire.read() & 0x3f;
    }

    minTens = minutes >> 4;
    minUnits = minutes & 0x0f;
    hourTens = hours & 0x10 ? 1 : 0;
    hourUnits = hours & 0x0f;
}

void setup() {
    pinMode(maxDataPin, OUTPUT);
    pinMode(maxClockPin, OUTPUT);
    pinMode(maxLoadPin, OUTPUT);

    Wire.begin();

    updateTime();
    updateDisplay();

    setMaxRegisterAll(0xa, 8); // intensity
    setMaxRegisterAll(0xb, 7); // scan limit
    setMaxRegisterAll(0xf, 0); // display test off
    setMaxRegisterAll(0x9, 0x00); // decode mode off
    setMaxRegisterAll(0xc, 1); // activate display
}

void loop() {
    delay(1000);
    updateTime();
    updateDisplay();
}


