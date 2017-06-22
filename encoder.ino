int encoderPin1 = 2; //these pins can not be changed 2/3 are special pins
int encoderPin2 = 3; //these pins can not be changed 2/3 are special pins
int encoderPin3 = 13; 

int lastButtonState = 1;
int mode = 0;
volatile int lastEncoded = 0;
volatile long encoderValue = 440;
long lastencoderValue = 440;
int lastMSB = 0;
int lastLSB = 0;


void setupEncoder(){
  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);
  pinMode(encoderPin3, INPUT);

  digitalWrite(encoderPin1, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); //turn pullup resistor on
  digitalWrite(encoderPin3, HIGH); //turn pullup resistor on

  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);
}

void updateEncoder(){
  int MSB = digitalRead(encoderPin1); //MSB = most significant bit
  int LSB = digitalRead(encoderPin2); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}

int getMode(){
  return mode;
}

int getRequiredTempValue(){
  int buttonState = digitalRead(encoderPin3);
  if (buttonState==0 && lastButtonState==1){
    if (mode == 0 ){
        Serial.println("Change mode to 1");
        mode = 1;
    }
    else if (mode == 1 ){
        Serial.println("Change mode to 0");
        mode = 0;
    }
    
  }
  lastButtonState = buttonState;

  
  return encoderValue/4;
}
