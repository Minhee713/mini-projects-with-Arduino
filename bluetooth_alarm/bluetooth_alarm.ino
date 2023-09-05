#include <Wire.h>
#include <LiquidCrystal_I2C.h> 


LiquidCrystal_I2C lcd(0x27,16,2);
// set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("Arduino UNO!");
 
  delay(1000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("ADC VALUE");
  lcd.setCursor(0,1);
  lcd.print(buf);

}

void loop() {
  ad_value = analogRead(A0);
  sprintf(buf, "%4d", ad_value);
  lcd.setCursor(0,1);
  lcd.print(buf);
  delay(100);

}
