
// This is a pretty easy one wiring-wise:
//  mic VCC goes to 3.3V and AREF
//  mic GND goes to common ground
//  mic OUT goes to analog0 -- but this assignment isn't correct for all models of arduino. only tested on Uno.
// Generates spectrum bars over the serial port, but
// it uses ANSI escape sequences so it's best viewed in a real
// terminal emulator, not the simple serial thing in the Arduino IDE.

#include <avr/pgmspace.h>
#include <stdint.h>
#include <ffft.h>
#include <avr/io.h>
#include <math.h>

#define ADC_CHANNEL 0

int16_t capture[FFT_N];
complex_t bfly[FFT_N];
uint16_t spectrum[FFT_N/2];
volatile byte samplePos = 0;

void setup() {
  Serial.begin(9600);
  
  ADMUX = ADC_CHANNEL;
  ADCSRA = _BV(ADEN) | _BV(ADSC) | _BV(ADATE) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
  ADCSRB = 0; // enable free run mode
  DIDR0 = 1 << ADC_CHANNEL; // turn off digital input
  TIMSK0 = 0; // turn off timer0
  
  sei();
}

void loop() {

  while(ADCSRA & _BV(ADIE)); // wait for sampling to finish -- then ISR will disable the interrupt

  fft_input(capture, bfly);
  fft_execute(bfly);
  fft_output(bfly, spectrum);

  static char bars[] = "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

  Serial.print("\e[2J\e[H");
  for (int i = 0; i < 25; i++) {
    int size = spectrum[i];
    if (size > 16) size = 16;
    memset(&bars, '\0', sizeof(bars));
    memset(&bars, '=', size);
    Serial.println(bars);
  }

  samplePos = 0;
  ADCSRA |= _BV(ADIE); // re-enable the interrupt
  
}

ISR(ADC_vect) { // audio-sampling interrupt
  static const int16_t noiseThreshold = 4;
  int16_t sample = ADC; // 0-1023
  
  capture[samplePos] =
    ((sample > (512 - noiseThreshold)) &&
     (sample < (512 + noiseThreshold))) ? 0 : sample - 512;

  if (++samplePos > FFT_N) ADCSRA &= ~_BV(ADIE); // interrupt off since buffer is full
}


