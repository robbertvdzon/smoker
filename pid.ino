#include <PID_v1.h>


double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint,2,5,1, DIRECT);


int calculateFanSpeed(double _currentTemp, int _currentMode)
{
  if (_currentMode==1) return 0;
  Input = _currentTemp; 
  myPID.Compute();
  return Output;
}


void setupPID(double _currentTemp, double _requiredTempValue)
{
  Serial.println("Setup pid to "+String(_requiredTempValue));
  Input = _currentTemp;
  Setpoint = _requiredTempValue;
  myPID.SetMode(AUTOMATIC);
}


