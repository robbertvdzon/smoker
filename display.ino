#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
double displayLastCurrentTemp=-1; 
double displayLastRequiredTempValue=-1;
double displayLastSturingValue=-1;


void setupDisplay(){
  lcd.begin(20,4);         // initialize the lcd for 20 chars 4 lines and turn on backlight

// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(100);
    lcd.noBacklight();
    delay(100);
  }
  lcd.backlight(); // finish with backlight on  

  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Starting");
}



void writeDisplay(int _currentTemp, int _requiredTempValue, int _sturingValue) {
  if (displayLastCurrentTemp==_currentTemp && displayLastRequiredTempValue==_requiredTempValue && displayLastSturingValue==_sturingValue){
    // nothing changed
    return;
  }
  displayLastCurrentTemp=_currentTemp;
  displayLastRequiredTempValue=_requiredTempValue;
  displayLastSturingValue=_sturingValue;

  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Temperatuur: ");
  lcd.print(_currentTemp);
  lcd.print(" C");
  
  lcd.setCursor(0,2); //Start at character 0 on line 0
  lcd.print("Instelling : ");
  lcd.print(_requiredTempValue);
  lcd.print(" C");

  lcd.setCursor(0,3); //Start at character 0 on line 0
  lcd.print("Sturing    : ");
  lcd.print(_sturingValue*100/256);
  lcd.print(" %");
  
}

