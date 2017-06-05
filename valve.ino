const int onoffRelaisPin = 0x06;   // valveOnOff pin
const int directionValveRelaisPin = 0x07;   // valveOnOff pin
const int valveFullyOpenSensorPin = 0x05;  
const int valveFullyClosedSensorPin = 0x04;  


// valve variable
int intNr = 0;
unsigned long startTime = 0;
unsigned long timeToCloseValve = 2000;


void setupValve(){
  pinMode(onoffRelaisPin, OUTPUT);
  pinMode(directionValveRelaisPin, OUTPUT);
  pinMode(valveFullyOpenSensorPin, INPUT_PULLUP);
  pinMode(valveFullyClosedSensorPin, INPUT_PULLUP);
}


void findValveTime(){
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  Serial.println(" turn open");
//  valveTurnOpen();
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  delay(10000);
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  Serial.println(" turn close");
//  valveTurnClosed();
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  delay(10000);
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  Serial.println(" turn stop");
//  valveStopTurn();
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  delay(5000);
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  Serial.println(" turn open");
//  valveTurnOpen();
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  delay(5000);
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  Serial.println(" turn close");
//  valveTurnClosed();
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  delay(5000);
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  Serial.println(" turn stop");
//  valveStopTurn();
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));
//  delay(5000);
//  Serial.println(" valveopen:"+String(digitalRead(valveFullyOpenSensorPin))+" valveclose:"+String(digitalRead(valveFullyClosedSensorPin)));


  
  Serial.println(" turn open");
  valveTurnOpen();
  while (digitalRead(valveFullyOpenSensorPin)==1){
    delay(1);
  }
  startTime = millis();
  Serial.println(" turn close");
  valveTurnClosed();
  while (digitalRead(valveFullyClosedSensorPin)==1){
    delay(1);
  }
  Serial.println(" closed");
  timeToCloseValve = millis()-startTime;
  valveStopTurn();
  Serial.println(" time:"+String(timeToCloseValve));
}


unsigned long currentValvePerc = 0;
unsigned long lastChangeValveTime = 0;


void openValveInPerc(unsigned long perc){
  if (currentValvePerc==perc) return;
  unsigned long now = millis();
  unsigned long diff = now - lastChangeValveTime;
  if (diff<60000L){
    Serial.println("valve change needed, but skipped. Valve was already changes this minute:"+String(diff));
    return;
  }
  Serial.println("change valve : "+String(diff));
  lastChangeValveTime = now;

  
  // first close
  valveTurnClosed();
  while (digitalRead(valveFullyClosedSensorPin)==1){
    delay(1);
  }
  if (perc==0){ 
    // do nothing
  }
  else if (perc==100){
    // fully open
    valveTurnOpen();
    while (digitalRead(valveFullyOpenSensorPin)==1){
      delay(1);
    }
  }    
  else{
    // go to percentage
    long timeToOpen = (perc*((long)timeToCloseValve))/100;
    unsigned long startTime = millis();
    valveTurnOpen();
    while (millis()<(startTime+timeToOpen)){
      delay(1);
    }
  }
  valveStopTurn();
  currentValvePerc = perc;
  
}


void valveTurnOpen(){
  digitalWrite(onoffRelaisPin, LOW);
  digitalWrite(directionValveRelaisPin, HIGH);  
}
void valveTurnClosed(){
  digitalWrite(onoffRelaisPin, LOW);
  digitalWrite(directionValveRelaisPin, LOW);  
}
void valveStopTurn(){
  digitalWrite(onoffRelaisPin, HIGH);
  digitalWrite(directionValveRelaisPin, LOW);  
}

int getRequiredValvePerc(){
  if (fanSpeed<=64) return 0;
  if (fanSpeed<=128) return 33;
  if (fanSpeed<=192) return 66;
  return 100;  
}


