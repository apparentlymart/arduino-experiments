
int buzzerPin = 12;
int potPin = 0;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop () {
  while (1) {
    int potValue = analogRead(potPin);
    int t = 900 - potValue;
    digitalWrite(buzzerPin, HIGH);
    delayMicroseconds(t);
    digitalWrite(buzzerPin, LOW);
    delayMicroseconds(t);
  }
}

