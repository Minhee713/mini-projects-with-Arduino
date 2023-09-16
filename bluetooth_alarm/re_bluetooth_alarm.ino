#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#define JOYSTICK_VRX A3
#define JOYSTICK_VRY A2
#define JOYSTICK_SW 7

int press = 0;
int vrx = 0;
int vry = 0;
int swState = 0;
int hour = 0;
int minute = 0;
int second = 0;
int isAmPm = 0;


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

  pinMode(JOYSTICK_SW, INPUT_PULLUP);

  Serial.begin(9600);
  while (!Serial) {
  }
}

void loop() {
  swState = digitalRead(JOYSTICK_SW);

  Serial.print("JoyStick switch START : ");
  Serial.println(swState);

  int vrxMap = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);
  int vryMap = map(analogRead(JOYSTICK_VRY), 0, 1023, 0, 60);

  // Serial.print("VRX for Hour (0 ~ 12) : ");
  // Serial.println(vrxMap);

  // Serial.print("VRY for Minute & Second (0 ~ 60) : ");
  // Serial.println(vryMap);

  Serial.print("Press START : ");
  Serial.println(press);

  Serial.println();
  Serial.print("Hour: ");
  Serial.println(hour);
  Serial.print("Minite: ");
  Serial.println(minute);
  Serial.print("Second: ");
  Serial.println(second);
  Serial.println();


  delay(500);

  // Set start
  if (swState == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Time ");
    lcd.setCursor(0, 1);
    lcd.print("AM 00: 00: 00");

    Serial.print("Set START : ");
    Serial.println(swState);

    press = 1;

    Serial.print("Press 1 (AM/PM): ");
    Serial.println(swState);
  }

  // Set AM/PM
  while (press == 1) {
    // lcd.setCursor(0, 1);
    // lcd.print("  ");
    // delay(300);
    // lcd.setCursor(0, 1);
    // lcd.print("AM");
    // delay(300);


    Serial.print("Press 1 with swState : ");
    Serial.println(swState);

    int presentVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 10);

    Serial.print("presentVRX : ");
    Serial.println(presentVRX);

    while (press == 1) {
      int newVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 10);

      Serial.println();
      Serial.print("presentVRX : ");
      Serial.println(presentVRX);
      Serial.print("newVRX : ");
      Serial.println(newVRX);
      Serial.println();

      if (newVRX > presentVRX) {
        isAmPm = 2;
        for (int i = 0; i < 5; i++) {
          lcd.setCursor(0, 1);
          lcd.print("  ");
          delay(300);
          lcd.setCursor(0, 1);
          lcd.print("PM");
          delay(300);
        }
      } else if (newVRX < presentVRX) {
        isAmPm = 1;
        for (int i = 0; i < 5; i++) {
          lcd.setCursor(0, 1);
          lcd.print("  ");
          delay(300);
          lcd.setCursor(0, 1);
          lcd.print("AM");
          delay(300);
        }
      }

      if (digitalRead(JOYSTICK_SW) == LOW) {
        press = 2;

        Serial.print("Press 2 with swState: ");
        Serial.println(swState);

        Serial.print("isAmPM : ");
        Serial.println(isAmPm);
        Serial.println();
      }
    }
  }

  // Set Hour
  while (press == 2) {
    lcd.setCursor(3, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(3, 1);
    lcd.print("00");
    lcd.setCursor(5, 1);
    lcd.print(":");
    delay(300);

    int presentVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);
    int pastVRX = presentVRX;

    Serial.print("presentVRX : ");
    Serial.println(presentVRX);

    while (press == 2) {
      int newVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);

      Serial.print("presentVRX : ");
      Serial.println(presentVRX);

      Serial.print("newVRX : ");
      Serial.println(newVRX);

      if (newVRX > pastVRX) {
        hour++;
      } else if (newVRX < pastVRX) {
        hour--;
      }

      if (hour < 0) {
        hour = 12;
      } else if (hour > 12) {
        hour = 0;
      }

      if (hour < 10) {
        lcd.setCursor(3, 1);
        lcd.print("  ");
        delay(300);
        lcd.setCursor(3, 1);
        lcd.print("0");
        lcd.setCursor(4, 1);
        lcd.print(hour);
        delay(300);
      } else {
        lcd.setCursor(3, 1);
        lcd.print("  ");
        delay(300);
        lcd.setCursor(3, 1);
        lcd.print(hour);
        delay(300);
      }


      //pastVRX = newVRX;

      Serial.print("hour");
      Serial.println(hour);

      if (digitalRead(JOYSTICK_SW) == LOW) {
        press = 3;
        Serial.print("Press 4 (Minute) : ");
        Serial.println(digitalRead(JOYSTICK_SW));
      }
    }
  }

  // Set Minute
  while (press == 3) {
    lcd.setCursor(7, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(7, 1);
    lcd.print("00");
    lcd.setCursor(9, 1);
    lcd.print(":");
    delay(300);

    int presentVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);
    int pastVRX = presentVRX;

    Serial.print("presentVRX : ");
    Serial.println(presentVRX);

    while (press == 3) {
      int newVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);

      Serial.print("presentVRX : ");
      Serial.println(presentVRX);

      Serial.print("newVRX : ");
      Serial.println(newVRX);

      if (newVRX > pastVRX) {
        minute++;
      } else if (newVRX < pastVRX) {
        minute--;
      }

      if (minute < 0) {
        minute = 60;
      } else if (minute > 60) {
        minute = 0;
      }

      if (minute < 10) {
        lcd.setCursor(7, 1);
        lcd.print("  ");
        delay(300);
        lcd.setCursor(7, 1);
        lcd.print("0");
        lcd.setCursor(8, 1);
        lcd.print(minute);
        delay(300);
      } else {
        lcd.setCursor(7, 1);
        lcd.print("  ");
        delay(300);
        lcd.setCursor(7, 1);
        lcd.print(minute);
        delay(300);
      }


      Serial.print("minute");
      Serial.println(minute);
      if (digitalRead(JOYSTICK_SW) == LOW) {
        press = 4;
        Serial.print("Press 4 (Second) : ");
        Serial.println(digitalRead(JOYSTICK_SW));
      }
    }
  }


  // Set Second
  while (press == 4) {
    lcd.setCursor(11, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(11, 1);
    lcd.print("00");
    delay(300);


    int presentVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);
    int pastVRX = presentVRX;

    Serial.print("presentVRX : ");
    Serial.println(presentVRX);

    while (press == 4) {
      int newVRX = map(analogRead(JOYSTICK_VRX), 0, 1023, 0, 12);

      Serial.print("presentVRX : ");
      Serial.println(presentVRX);

      Serial.print("newVRX : ");
      Serial.println(newVRX);

      if (newVRX > pastVRX) {
        second++;
      } else if (newVRX < pastVRX) {
        second--;
      }

      if (second < 0) {
        second = 60;
      } else if (second > 60) {
        second = 0;
      }

      if (second < 10) {
        lcd.setCursor(11, 1);
        lcd.print("  ");
        delay(300);
        lcd.setCursor(11, 1);
        lcd.print("0");
        lcd.setCursor(12, 1);
        lcd.print(second);
        delay(300);
      } else {
        lcd.setCursor(11, 1);
        lcd.print("  ");
        delay(300);
        lcd.setCursor(11, 1);
        lcd.print(second);
        delay(300);
      }
      Serial.print("second");
      Serial.println(second);
      if (digitalRead(JOYSTICK_SW) == LOW) {
        press = 5;
        Serial.print("Press 5 (Set Complete) : ");
        Serial.println(digitalRead(JOYSTICK_SW));
      }
    }
  }

  // Set Complete
  if (press == 5) {
    lcd.clear();
    lcd.setCursor(1, 1);
    lcd.print("Setup Complete!");


    delay(2000);

    //press = 0;

    Serial.print("Set complete! (press = 0) ");
    Serial.println(digitalRead(JOYSTICK_SW));
  }
}

void saveTime(int h, int m, int s) {
}
