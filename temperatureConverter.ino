const int tempSensorPin = A2;   // Temperatuur sensor

double refC[] = {0   ,  20,  80 , 110 , 126 , 156 , 277, 277 };
double refV[] = {1024, 940, 540 , 320 , 230 , 123 , 15 , 0   };

int loadTemparature(){
  return calculateTemparature(analogRead(tempSensorPin));
}


int calculateTemparature(double sensorValue){
  int segment = 1;
  while (refV[segment]>sensorValue) {
    segment++;
  }
  double sens1=refV[segment-1];
  double sens2=refV[segment];
  double temp1=refC[segment-1];
  double temp2=refC[segment];
  double temp = temp1+(sens1-sensorValue)*((temp2-temp1)/(sens1-sens2));
  return (int)temp;
  
}
