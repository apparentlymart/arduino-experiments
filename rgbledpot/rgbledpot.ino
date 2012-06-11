
int redPin = 9;
int greenPin = 11;
int bluePin = 10;
int potPin = 0;
int buttonPin = 12;

const boolean ON = LOW;
const boolean OFF = HIGH;

unsigned char huecolor[] = {
    255, 0, 0,
    255, 4, 0,
    255, 8, 0,
    255, 13, 0,
    255, 17, 0,
    255, 21, 0,
    255, 25, 0,
    255, 30, 0,
    255, 34, 0,
    255, 38, 0,
    255, 42, 0,
    255, 47, 0,
    255, 51, 0,
    255, 55, 0,
    255, 60, 0,
    255, 64, 0,
    255, 68, 0,
    255, 72, 0,
    255, 77, 0,
    255, 81, 0,
    255, 85, 0,
    255, 89, 0,
    255, 94, 0,
    255, 98, 0,
    255, 102, 0,
    255, 106, 0,
    255, 111, 0,
    255, 115, 0,
    255, 119, 0,
    255, 123, 0,
    255, 128, 0,
    255, 132, 0,
    255, 136, 0,
    255, 140, 0,
    255, 145, 0,
    255, 149, 0,
    255, 153, 0,
    255, 157, 0,
    255, 162, 0,
    255, 166, 0,
    255, 170, 0,
    255, 174, 0,
    255, 179, 0,
    255, 183, 0,
    255, 187, 0,
    255, 191, 0,
    255, 195, 0,
    255, 200, 0,
    255, 204, 0,
    255, 208, 0,
    255, 213, 0,
    255, 217, 0,
    255, 221, 0,
    255, 225, 0,
    255, 229, 0,
    255, 234, 0,
    255, 238, 0,
    255, 242, 0,
    255, 247, 0,
    255, 251, 0,
    255, 255, 0,
    251, 255, 0,
    247, 255, 0,
    242, 255, 0,
    238, 255, 0,
    234, 255, 0,
    230, 255, 0,
    225, 255, 0,
    221, 255, 0,
    217, 255, 0,
    212, 255, 0,
    208, 255, 0,
    204, 255, 0,
    200, 255, 0,
    195, 255, 0,
    191, 255, 0,
    187, 255, 0,
    183, 255, 0,
    179, 255, 0,
    174, 255, 0,
    170, 255, 0,
    166, 255, 0,
    162, 255, 0,
    157, 255, 0,
    153, 255, 0,
    149, 255, 0,
    145, 255, 0,
    140, 255, 0,
    136, 255, 0,
    132, 255, 0,
    128, 255, 0,
    123, 255, 0,
    119, 255, 0,
    115, 255, 0,
    110, 255, 0,
    106, 255, 0,
    102, 255, 0,
    98, 255, 0,
    94, 255, 0,
    89, 255, 0,
    85, 255, 0,
    81, 255, 0,
    77, 255, 0,
    72, 255, 0,
    68, 255, 0,
    64, 255, 0,
    60, 255, 0,
    55, 255, 0,
    51, 255, 0,
    47, 255, 0,
    42, 255, 0,
    38, 255, 0,
    34, 255, 0,
    30, 255, 0,
    26, 255, 0,
    21, 255, 0,
    17, 255, 0,
    13, 255, 0,
    8, 255, 0,
    4, 255, 0,
    0, 255, 0,
    0, 255, 4,
    0, 255, 8,
    0, 255, 13,
    0, 255, 17,
    0, 255, 21,
    0, 255, 25,
    0, 255, 30,
    0, 255, 34,
    0, 255, 38,
    0, 255, 42,
    0, 255, 47,
    0, 255, 51,
    0, 255, 55,
    0, 255, 60,
    0, 255, 64,
    0, 255, 68,
    0, 255, 72,
    0, 255, 77,
    0, 255, 81,
    0, 255, 85,
    0, 255, 89,
    0, 255, 94,
    0, 255, 98,
    0, 255, 102,
    0, 255, 106,
    0, 255, 111,
    0, 255, 115,
    0, 255, 119,
    0, 255, 123,
    0, 255, 128,
    0, 255, 132,
    0, 255, 136,
    0, 255, 140,
    0, 255, 144,
    0, 255, 149,
    0, 255, 153,
    0, 255, 157,
    0, 255, 162,
    0, 255, 166,
    0, 255, 170,
    0, 255, 174,
    0, 255, 179,
    0, 255, 183,
    0, 255, 187,
    0, 255, 191,
    0, 255, 195,
    0, 255, 200,
    0, 255, 204,
    0, 255, 208,
    0, 255, 212,
    0, 255, 217,
    0, 255, 221,
    0, 255, 225,
    0, 255, 229,
    0, 255, 234,
    0, 255, 238,
    0, 255, 242,
    0, 255, 247,
    0, 255, 251,
    0, 255, 255,
    0, 251, 255,
    0, 247, 255,
    0, 242, 255,
    0, 238, 255,
    0, 234, 255,
    0, 229, 255,
    0, 225, 255,
    0, 221, 255,
    0, 217, 255,
    0, 212, 255,
    0, 208, 255,
    0, 204, 255,
    0, 200, 255,
    0, 195, 255,
    0, 191, 255,
    0, 187, 255,
    0, 183, 255,
    0, 178, 255,
    0, 174, 255,
    0, 170, 255,
    0, 166, 255,
    0, 162, 255,
    0, 157, 255,
    0, 153, 255,
    0, 149, 255,
    0, 145, 255,
    0, 140, 255,
    0, 136, 255,
    0, 132, 255,
    0, 128, 255,
    0, 123, 255,
    0, 119, 255,
    0, 115, 255,
    0, 111, 255,
    0, 106, 255,
    0, 102, 255,
    0, 98, 255,
    0, 94, 255,
    0, 89, 255,
    0, 85, 255,
    0, 81, 255,
    0, 76, 255,
    0, 72, 255,
    0, 68, 255,
    0, 64, 255,
    0, 60, 255,
    0, 55, 255,
    0, 51, 255,
    0, 47, 255,
    0, 43, 255,
    0, 38, 255,
    0, 34, 255,
    0, 30, 255,
    0, 25, 255,
    0, 21, 255,
    0, 17, 255,
    0, 13, 255,
    0, 8, 255,
    0, 4, 255,
    0, 0, 255,
    4, 0, 255,
    8, 0, 255,
    13, 0, 255,
    17, 0, 255,
    21, 0, 255,
    25, 0, 255,
    30, 0, 255,
    34, 0, 255,
    38, 0, 255,
    42, 0, 255,
    47, 0, 255,
    51, 0, 255,
    55, 0, 255,
    60, 0, 255,
    64, 0, 255,
    68, 0, 255,
    72, 0, 255,
    76, 0, 255,
    81, 0, 255,
    85, 0, 255,
    89, 0, 255,
    93, 0, 255,
    98, 0, 255,
    102, 0, 255,
    106, 0, 255,
    111, 0, 255,
    115, 0, 255,
    119, 0, 255,
    123, 0, 255,
    128, 0, 255,
    132, 0, 255,
    136, 0, 255,
    140, 0, 255,
    144, 0, 255,
    149, 0, 255,
    153, 0, 255,
    157, 0, 255,
    162, 0, 255,
    166, 0, 255,
    170, 0, 255,
    174, 0, 255,
    179, 0, 255,
    183, 0, 255,
    187, 0, 255,
    191, 0, 255,
    195, 0, 255,
    200, 0, 255,
    204, 0, 255,
    208, 0, 255,
    213, 0, 255,
    217, 0, 255,
    221, 0, 255,
    225, 0, 255,
    230, 0, 255,
    234, 0, 255,
    238, 0, 255,
    242, 0, 255,
    247, 0, 255,
    251, 0, 255,
    255, 0, 255,
    255, 0, 251,
    255, 0, 247,
    255, 0, 242,
    255, 0, 238,
    255, 0, 234,
    255, 0, 230,
    255, 0, 225,
    255, 0, 221,
    255, 0, 217,
    255, 0, 212,
    255, 0, 208,
    255, 0, 204,
    255, 0, 200,
    255, 0, 195,
    255, 0, 191,
    255, 0, 187,
    255, 0, 183,
    255, 0, 179,
    255, 0, 174,
    255, 0, 170,
    255, 0, 166,
    255, 0, 161,
    255, 0, 157,
    255, 0, 153,
    255, 0, 149,
    255, 0, 144,
    255, 0, 140,
    255, 0, 136,
    255, 0, 132,
    255, 0, 128,
    255, 0, 123,
    255, 0, 119,
    255, 0, 115,
    255, 0, 111,
    255, 0, 106,
    255, 0, 102,
    255, 0, 98,
    255, 0, 94,
    255, 0, 89,
    255, 0, 85,
    255, 0, 81,
    255, 0, 77,
    255, 0, 72,
    255, 0, 68,
    255, 0, 64,
    255, 0, 60,
    255, 0, 55,
    255, 0, 51,
    255, 0, 47,
    255, 0, 43,
    255, 0, 38,
    255, 0, 34,
    255, 0, 30,
    255, 0, 26,
    255, 0, 21,
    255, 0, 17,
    255, 0, 13,
    255, 0, 8,
    255, 0, 4,
};

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void setColor(char r, char g, char b) {
  analogWrite(redPin, 255 - r);
  analogWrite(greenPin, 255 - g);
  analogWrite(bluePin, 255 - b);  
}

void loop() {
  int i = 1;
  while (1) {
     int h = analogRead(potPin) / 4;
     int pressed = digitalRead(buttonPin) == LOW;
     Serial.println(pressed);
     int div = pressed ? 10 : 1;
     int base = h * 3;
     int r = huecolor[base] / div;
     int g = huecolor[base + 1] / div;
     int b = huecolor[base + 2] / div;
     setColor(r, g, b);
  }
}

