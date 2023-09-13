#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SETPIN 3
#define BILNK 5
#define JOYSTICK_VRX A3
#define JOYSTICK_VRY A2
#define JOYSTICK_SW 7

int buttonState = 0;
int lastButtonState = LOW;
int press = 0;
int nextStep = 0;
int currentHour = 0;
char buf[10] = { 0 };

LiquidCrystal_I2C lcd(0x27, 16, 2);
// set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {

  // initialize the lcd
  lcd.init();
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("min-hee Kwon");
  lcd.setCursor(0, 1);
  lcd.print("AM 00: 00: 00");

  pinMode(SETPIN, INPUT);

  Serial.begin(9600); // test 
}

void loop() {
  buttonState = digitalRead(SETPIN);
  int vrx = analogRead(JOYSTICK_VRX);
  int vry = analogRead(JOYSTICK_VRY);
  int sw = analogRead(JOYSTICK_SW);
  // int vrxMap = map(vrx, 0, 1023, 0, 12);
  int vryMap = map(vry, 0, 1023, 0, 60);

  // Serial.println(vrxMap);
  // Serial.println(vryMap);
  // delay(100);


  if (buttonState) {
    press++;
    if (press == 1) {
      for (int i = 0; i < BILNK; i++) {
        lcd.setCursor(0, 1);
        lcd.print("  ");
        delay(150);
        lcd.setCursor(0, 1);
        lcd.print("AM");
        delay(150);
      }
    }

    else if (press == 2) {
      for (int i = 0; i < BILNK; i++) {
        lcd.setCursor(0, 1);
        lcd.print("  ");
        delay(150);
        lcd.setCursor(0, 1);
        lcd.print("PM");
        delay(150);
      }
    }

    else {
      nextStep++;
      if (nextStep == 1) {
        for (int i = 0; i < BILNK; i++) {
          lcd.setCursor(3, 1);
          lcd.print("   ");
          delay(150);
          lcd.setCursor(3, 1);
          lcd.print("00");
          lcd.setCursor(5, 1);
          lcd.print(":");
          delay(150);
        }
          int vrxMap = map(vrx, 0, 1023, 0, 12);
          sprintf(buf, "%4d", vrxMap);
          lcd.setCursor(3, 3);
          lcd.print(buf);
          delay(100);        
         
          lcd.setCursor(5, 5);
          lcd.print(":");
          //delay(100);
          Serial.print("vrxMap ");
          Serial.println(buf); 

       

         
        
        
      }


      else if (nextStep == 2) {
        for (int i = 0; i < BILNK; i++) {
          lcd.setCursor(7, 7);
          lcd.print("   ");
          delay(150);
          lcd.setCursor(7, 7);
          lcd.print("00");
          lcd.setCursor(9, 9);
          lcd.print(":");
          delay(150);
        }
      }

      else if (nextStep == 3) {
        for (int i = 0; i < BILNK; i++) {
          lcd.setCursor(11, 11);
          lcd.print("   ");
          delay(150);
          lcd.setCursor(11, 11);
          lcd.print("00");
          delay(150);
        }
      }
    }

    if (nextStep == 4) {
      press = 0;
      nextStep = 0;
    }
  }
}
