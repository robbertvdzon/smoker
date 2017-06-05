#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
double displayLastCurrentTemp=-1; 
double displayLastRequiredTempValue=-1;

Adafruit_SSD1306 display(OLED_RESET);

void setupDisplay(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Starting");
  display.display();  
}



void writeDisplay(int _currentTemp, int _requiredTempValue) {
  if (displayLastCurrentTemp==_currentTemp && displayLastRequiredTempValue==_requiredTempValue){
    // nothing changed
    return;
  }
  displayLastCurrentTemp=_currentTemp;
  displayLastRequiredTempValue=_requiredTempValue;
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("T: ");
  display.print(_currentTemp);
  display.println(" C");
  display.print("SP: ");
  display.print(_requiredTempValue);
  display.println(" C");
  display.display();  
}

