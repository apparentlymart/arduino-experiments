
#include <Wire.h>

byte dec_to_bcd(byte val) {
  return ( (val/10*16) + (val%10) );
}

byte bcd_to_dec(byte val) {
  return ( (val/16*10) + (val%16) );
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(104);
  Wire.write(0);
  Wire.write(dec_to_bcd(0)); // seconds
  Wire.write(dec_to_bcd(56)); // minutes
  Wire.write(dec_to_bcd(5)); // hours
  Wire.write(dec_to_bcd(0)); // day (not used)
  Wire.write(dec_to_bcd(1)); // date
  Wire.write(dec_to_bcd(07)); // month
  Wire.write(dec_to_bcd(11)); // year
  Wire.endTransmission();
}

void loop() {
  Wire.beginTransmission(104);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(104, 7);
  while (Wire.available()) {
    int seconds = bcd_to_dec(Wire.read() & 0x7f);
    int minutes = bcd_to_dec(Wire.read());
    int hours = bcd_to_dec(Wire.read() & 0x3f);
    Wire.read(); // discard day
    int date = bcd_to_dec(Wire.read());
    int month = bcd_to_dec(Wire.read());
    int year = bcd_to_dec(Wire.read());
    Serial.print("20");
    Serial.print(year);
    Serial.print("-");
    Serial.print(month);
    Serial.print("-");
    Serial.print(date);
    Serial.print("T");
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print(":");
    Serial.println(seconds);
  }
  delay(1000);
}

