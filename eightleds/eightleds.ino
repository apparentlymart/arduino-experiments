
void setup() {
  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  /*for (int i = 2; i <= 9; i++) {
    digitalWrite(i, HIGH);
    delay(250);
  }  
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, LOW);
    delay(250);
  }*/
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, (((i % 4) == 0) || ((i % 4) == 1)) ? HIGH : LOW);
  }  
  delay(250);
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, (((i % 4) == 1) || ((i % 4) == 2)) ? HIGH : LOW);
  }  
  delay(250);
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, (((i % 4) == 2) || ((i % 4) == 3)) ? HIGH : LOW);
  }  
  delay(250);
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, (((i % 4) == 3) || ((i % 4) == 0)) ? HIGH : LOW);
  }  
  delay(250);
}

