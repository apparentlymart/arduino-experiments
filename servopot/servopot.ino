
#include <Servo.h>
Servo servo;

int servoPin = 9;
int upBtnPin = 2;
int downBtnPin = 3;
int currentPos = -1;
volatile int targetPos = 0;
int lastIntMillis = 0;

void turnUp() {
  if (millis() - lastIntMillis < 100) return;
  Serial.println("turnUp");
  targetPos = targetPos + 20;
  if (targetPos > 180) targetPos = 180;
  lastIntMillis = millis();
}

void turnDown() {
  if (millis() - lastIntMillis < 100) return;
  Serial.println("turnDown");
  targetPos = targetPos - 20;  
  if (targetPos < 0) targetPos = 0;
  lastIntMillis = millis();
}

void setup() {
  servo.attach(servoPin);
  pinMode(upBtnPin, INPUT);
  pinMode(downBtnPin, INPUT);
  attachInterrupt(1, turnUp, RISING);
  attachInterrupt(0, turnDown, RISING);
  Serial.begin(9600);
}

void loop() {
  if (currentPos != targetPos) {
    Serial.print("Turning to ");
    Serial.println(targetPos);
    delay(20);
    servo.write(targetPos);
    currentPos = targetPos;
    delay(20); 
  }
}

