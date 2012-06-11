
int pedButtonPin = 2;
int pedGreenPin = 3;
int pedRedPin = 4;
int carGreenPin = 8;
int carAmberPin = 9;
int carRedPin = 10;
volatile int pedRequest = 0;

const int ON = HIGH;
const int OFF = LOW;
const int STOP = 1;
const int GETREADY = 2;
const int GO = 3;

void press() {
  pedRequest = 1; 
}

void setup() {
  pinMode(pedButtonPin, INPUT);
  pinMode(pedGreenPin, OUTPUT);
  pinMode(pedRedPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(carAmberPin, OUTPUT);
  pinMode(carRedPin, OUTPUT);
  attachInterrupt(0, press, RISING);
}

void carPhase() {
  setCarState(GO);
  setPedState(STOP);
  pedRequest = 0;
  while (! pedRequest) {
      delay(1000);
  }
  delay(5000);
  setCarState(GETREADY);
  delay(1000);
  setCarState(STOP);
  delay(1000);
}

void pedPhase() {
  setCarState(STOP);
  setPedState(GO);
  delay(6000);
  for (int i = 0; i < 4; i++) {
      setPedState(GETREADY);
      delay(500);
      setPedState(GO);
      delay(500);
  }
  setPedState(STOP);
  delay(1000);  
}

void setCarState(int carState) {
  digitalWrite(carGreenPin, carState == GO ? ON : OFF);
  digitalWrite(carAmberPin, carState == GETREADY ? ON : OFF);
  digitalWrite(carRedPin, carState == STOP ? ON : OFF);
}
void setPedState(int pedState) {
  if (pedState == GO) {
      digitalWrite(pedGreenPin, ON);
  }
  else if (pedState == GETREADY) {
      analogWrite(pedGreenPin, 50);
  }
  else {
      digitalWrite(pedGreenPin, OFF);    
  }
  digitalWrite(pedRedPin, pedState == STOP ? ON : OFF);
}

void loop() {
  carPhase();
  pedPhase();
}


