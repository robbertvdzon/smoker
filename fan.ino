const int analogOutPin = 0x09;     // PWD pin voor ventilator


void writeFanSpeed(int _fanSpeed) {
  analogWrite(analogOutPin, _fanSpeed*2/3);
}


