
int buzzerPin = 12;

int notes[] =   { 0, 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };
int ledPins[] = { 0,    2,    3,    4,    5,    6,    7,    8,   9 };

int twinkle[] = {
   1, 1,
   1, 1,
   5, 1,
   5, 1,
   6, 1,
   6, 1,
   5, 1,

   0, 1,

   4, 1,
   4, 1,
   3, 1,
   3, 1,
   2, 1,
   2, 1,
   1, 1,

   0, 1,

   5, 1,
   5, 1,
   4, 1,
   4, 1,
   3, 1,
   3, 1,
   2, 1,

   0, 1,

   5, 1,
   5, 1,
   4, 1,
   4, 1,
   3, 1,
   3, 1,
   2, 1,

   0, 1,

   1, 1,
   1, 1,
   5, 1,
   5, 1,
   6, 1,
   6, 1,
   5, 1,

   0, 1,

   4, 1,
   4, 1,
   3, 1,
   3, 1,
   2, 1,
   2, 1,
   1, 2,
   0, 2,
   
   // Zero-length note is terminator
   0, 0,
};

int weasel[] = {
   1, 2, // half
   3, 1, // a
   2, 2, // pound
   4, 1, // of
   3, 1, // tu-
   5, 1, // -pe-
   3, 1, // -ny
   1, 2, // rice.
   0, 1,
   
   1, 2, // half
   3, 1, // a
   2, 2, // pound
   4, 1, // of
   3, 3, // trea-
   1, 2, // cle
   0, 1,

   1, 2, // that's
   3, 1, // the
   2, 2, // way
   4, 1, // the
   3, 1, // mo-
   5, 1, // -o-
   3, 1, // -ny
   1, 2, // goes.
   0, 1,

   6, 3, // pop
   2, 2, // goes
   4, 1, // the
   3, 3, // wea-
   1, 3, // sel

   0, 5,
   
   // Zero-length note is terminator
   0, 0,
};

int woodenHeart[] = {
   1, 2, // can't
   2, 2, // you
   3, 4, // see
   3, 2, // I
   5, 2, // love
   4, 4, // you
   4, 2, // Please
   6, 2, // don't
   5, 3, // break
   6, 1, // my
   5, 2, // heart
   4, 2, // in
   3, 6, // two
   0, 2,
   
   5, 3, // that's
   6, 1, // not
   5, 2, // hard
   4, 2, // to
   3, 4, // do
   3, 2, // 'cause
   5, 2, // I
   4, 4, // don't
   4, 2, // have
   3, 2, // a
   2, 4, // woo-
   5, 4, // -den
   3, 10, // heart.
   0, 2,

   1, 2, // and
   2, 2, // if
   3, 4, // you
   3, 2, // say
   5, 2, // good-
   4, 4, // -bye
   4, 2, // then
   6, 2, // I
   5, 3, // know
   6, 1, // that
   5, 2, // I
   4, 2, // would
   3, 6, // cry
   0, 2,
   
   5, 3, // may-
   6, 1, // -be
   5, 2, // I
   4, 2, // would
   3, 4, // die
   3, 2, // 'cause
   5, 2, // I
   4, 4, // don't
   4, 2, // have
   3, 2, // a
   2, 4, // woo-
   5, 4, // -den
   1, 10, // heart.

   0, 10,

   // Zero-length note is terminator
   0, 0,
};

void playTone(int note, int duration) {
   Serial.print("play ");
   Serial.print(note);
   Serial.print(" for ");
   Serial.println(duration);
   if (note > 0) {
       int tone = notes[note];
       for (long i = 0; i < duration * 1000L; i += tone * 2) {
           digitalWrite(buzzerPin, HIGH);
           delayMicroseconds(tone);
           digitalWrite(buzzerPin, LOW);
           delayMicroseconds(tone);
       }
   }
   else {
      delay(duration); 
   }
}

void playTune(int *tune, int tempo) {
    for (int i = 0; tune[i + 1] > 0; i += 2) {
        int ledPin = ledPins[tune[i]];
        digitalWrite(ledPin, HIGH);
        playTone(tune[i], tune[i + 1] * tempo);
        digitalWrite(ledPin, LOW);
        delay(tempo / 2);
    }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  for (int i = 1; i < (sizeof(ledPins) / sizeof(int)); i++) {
     pinMode(ledPins[i], OUTPUT); 
  }
  Serial.begin(9600);
}

void loop() {
    int i;
    playTune(twinkle, 300);
    playTune(weasel, 150);
    playTune(woodenHeart, 100);
}


