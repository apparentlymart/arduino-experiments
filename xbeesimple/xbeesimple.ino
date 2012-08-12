
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write("hi\r\n");
  delay(1000);
}

