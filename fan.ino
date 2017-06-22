const int analogOutPin = 0x09;     // PWD pin voor ventilator

void setupFan(){
  TCCR1B = TCCR1B & B11111000 | B00000010;
}
void writeFanSpeed(int _fanSpeed) {
  analogWrite(analogOutPin, _fanSpeed*2/3);
}


