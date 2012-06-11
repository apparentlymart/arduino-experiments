

int dataPin = 11;
int latchPin = 13;
int clockPin = 12;

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  //Serial.begin(9600);  
}

void loop() {
  for (int i = 0; i < 63; i++) {
    //Serial.println(i);
    digitalWrite(latchPin, LOW);
    digitalWrite(clockPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, i);
    delay(100);
    digitalWrite(latchPin, HIGH);
    delay(100);
  }  
}

