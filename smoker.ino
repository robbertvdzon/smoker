#include <Arduino.h>

int requiredTempValue = 110;      // temperature in degrees
int currentTemp = 0;              // temperature calculated from the sensor (in degrees)
int fanSpeed = 0;                 // value send to the pwm controlled fan (0-255)


void setup() {
  Serial.begin(9600);
  Serial.println("setup");
  currentTemp = loadTemparature();
  setupPID(currentTemp, requiredTempValue);
  setupDisplay();
  setupValve();
  setupEncoder();
  setupFan();
  findValveTime();
}


int outerLoop = 0;
int lastRequiredTempValue = 0;
int currentMode = 0;
void loop() {
  requiredTempValue = getRequiredTempValue();
  currentMode = getMode();
  if (lastRequiredTempValue!=requiredTempValue){
    setupPID(currentTemp, requiredTempValue);
    lastRequiredTempValue=requiredTempValue;
  }
  outerLoop++;
  if (outerLoop%1000==0){ // check the millies to do this every 20 seconds or so
    currentTemp = loadTemparature();
    fanSpeed = calculateFanSpeed(currentTemp, currentMode);
    writeFanSpeed(fanSpeed);
    openValveInPerc(getRequiredValvePerc());  
  }
  if (outerLoop%10000==0){ 
      writeFanAndTempTo8266(currentTemp, fanSpeed);
      logValues(currentTemp, fanSpeed);
  }
  writeDisplay(currentTemp,requiredTempValue, fanSpeed, currentMode);
  delay(1);  
}


