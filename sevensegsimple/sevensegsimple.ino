

int cathodePins[] = {
  8, // a
  7, // b
  5, // c
  3, // d
  2, // e
  10, // f
  11, // g
  6  // dp
};

int chars[16] = {
   B11111100,  // 0
   B01100000,  // 1
   B11011010,  // 2
   B11110010,  // 3
   B01100110,  // 4
   B10110110,  // 5
   B10111110,  // 6
   B11100000,  // 7
   B11111110,  // 8
   B11100110,  // 9
   B11101110,  // A
   B00111110,  // b
   B10011100,  // C
   B01111010,  // d
   B10011110,  // E
   B10001110,  // F
};

void setup() {
  for (int i = 0; i < sizeof(cathodePins)/sizeof(int); i++) {
     pinMode(cathodePins[i], OUTPUT); 
  }
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < sizeof(chars)/sizeof(int); i++) {
    Serial.println("----");
    Serial.println(i);
    int segs = chars[i];
    for (int j = 7; j >= 0; j--) {
      int which = (bitRead(segs, j)) ? LOW : HIGH;
      digitalWrite(cathodePins[7 - j], which);
      Serial.print(7 - j);
      Serial.println(which ? " HIGH" : " LOW");
    }
    delay(500);
  }
  return;
  for (int i = 0; i < sizeof(cathodePins)/sizeof(int); i++) {
    Serial.println("----");
    for (int j = 0; j < sizeof(cathodePins)/sizeof(int); j++) {
      int which = i == j ? LOW : HIGH;
      digitalWrite(cathodePins[j], which);
      Serial.print(i);
      Serial.print(", ");
      Serial.print(j);
      Serial.println(which ? " HIGH" : " LOW");
    }
    delay(500);
  }
}

