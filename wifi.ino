const int tempOutPin = 0x0A;     // PWD pin die aangeeft wat de temp is (voor de wifi controller)
const int fanOutPin = 0x0B;     // PWD pin die aangeeft wat de fan is (voor de wifi controller)


void writeFanAndTempTo8266(int _currentTemp, int _fanSpeed) {
  int pwmTempValue = _currentTemp;
  if (pwmTempValue>253) pwmTempValue = 253;
  int pwmFanValue = _fanSpeed;
  if (pwmFanValue>253) pwmFanValue = 253;
  analogWrite(tempOutPin, pwmTempValue);
  analogWrite(fanOutPin, pwmFanValue);
}

