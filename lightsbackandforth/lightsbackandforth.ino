
int numPins = 8;
int ledPins[] =    {2,3,4,5,6,7,8,9};
int brightness[] = {0,0,0,0,0,0,0,0};

void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  for (int i = 0; i < numPins; i++) {
    Serial.println(i);
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
    int delta = 1;
    int active = 0;
    int beat = 0;
    int animBeat = 0;
    while (1) {
      int animate = (animBeat % 2048) == 0;
      for (int i = 0; i < numPins; i++) {
        int pin = ledPins[i];
        int bright = brightness[i];
        int which = beat < bright ? LOW : HIGH;
        digitalWrite(pin, which);
        if ((animBeat % 32) == 0) {
           brightness[i]--;
           if (brightness[i] < 0) brightness[i] = 0;
        }
      }
      if (animate) {
        brightness[active] = 255;
        Serial.println("animate");
        Serial.println(active);
        Serial.println(delta);
        if (active >= (numPins - 1)) {
           Serial.println("bounce back down");
           active = numPins - 2;
           delta = -1;
           active = 0;
           delta = 1;
        }
        else if (active <= 0) {
           Serial.println("bounce back up");
           active = 1;
           delta = 1; 
        }
        else {
           Serial.println("continue");
           active = active + delta; 
        }
        Serial.println(active);
        Serial.println(delta);
      }
      beat++;
      animBeat++;
      beat = beat % 256;
    }
}

