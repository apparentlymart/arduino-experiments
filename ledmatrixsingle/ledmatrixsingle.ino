
const int maxDataPin = 4;
const int maxClockPin = 3;
const int maxLoadPin = 2;

byte hi[] = {
    0b01111111,
    0b00001000,
    0b01111111,
    0b00000000,
    0b01111010,
    0b00000000,
    0b01011111,
    0b00000000,
};

byte smile[] = {
    0b01111110,
    0b10000001,
    0b10010101,
    0b10100001,
    0b10010101,
    0b10000001,
    0b01111110,
    0b00000000,
};

void setMaxRegister(byte regCode, byte value) {
    digitalWrite(maxLoadPin, LOW);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, regCode);
    shiftOut(maxDataPin, maxClockPin, MSBFIRST, value);
    digitalWrite(maxLoadPin, HIGH);
}

void showPicture(byte pic[8]) {
  for (int i = 0; i < 8; i++) {
      setMaxRegister(i + 1, pic[i]);
  }
}

void setup() {
  pinMode(maxDataPin, OUTPUT);
  pinMode(maxClockPin, OUTPUT);
  pinMode(maxLoadPin, OUTPUT);

  setMaxRegister(0xa, 8); // intensity
  setMaxRegister(0xb, 7); // scan limit
  setMaxRegister(0xf, 0); // display test off
  setMaxRegister(0x9, 0x00); // decode mode off
  setMaxRegister(0xc, 1); // activate display

  setMaxRegister(0x1, 0b01111111);
  setMaxRegister(0x2, 0b00001000);
  setMaxRegister(0x3, 0b01111111);
  setMaxRegister(0x4, 0b00000000);
  setMaxRegister(0x5, 0b01111010);
  setMaxRegister(0x6, 0b00000000);
  setMaxRegister(0x7, 0b01011111);
  setMaxRegister(0x8, 0);
}

void loop() {
  showPicture(smile);
  delay(1000);
  showPicture(hi);
  delay(1000);
}

