#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define JOYSTICK_VRX A3
#define JOYSTICK_VRY A2
#define JOYSTICK_SW 7

int press;
int nextStep = 0;
int currentHour = 0;
char buf[10] = { 0 };
int vrx = 0;
int vry = 0;
int swState = 0;

boolean flag = false;


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

  delay(500);

  pinMode(13, OUTPUT);  // test
  Serial.begin(9600);   // test
}

void loop() {
  vrx = analogRead(JOYSTICK_VRX);
  vry = analogRead(JOYSTICK_VRY);
  swState = digitalRead(JOYSTICK_SW);

  int vrxMap = map(vrx, 0, 1023, 0, 12);
  int vryMap = map(vry, 0, 1023, 0, 60);

  Serial.print("sw before: ");  //test
  Serial.println(swState);      //test

  delay(500);


  // 1
  if (swState == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Set Time ");
    lcd.setCursor(0, 1);
    lcd.print("AM 00: 00: 00");

    Serial.print("1 sw after: ");  //test
    Serial.println(swState);       //test
    press = 1;
  }

  // 2
  while (press == 1) {
    lcd.setCursor(0, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(0, 1);
    lcd.print("AM");
    delay(300);
    if (digitalRead(JOYSTICK_SW) == LOW) {
      press = 2;
      Serial.print("2 sw after: ");              //test
      Serial.println(digitalRead(JOYSTICK_SW));  //test
    }
  }


  // 3
  while (press == 2) {
    lcd.setCursor(0, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(0, 1);
    lcd.print("PM");
    delay(300);
    if (digitalRead(JOYSTICK_SW) == LOW) {
      press = 3;
      Serial.print("3 sw after: ");              //test
      Serial.println(digitalRead(JOYSTICK_SW));  //test
    }
  }
  // 4
  while (press == 3) {
    lcd.setCursor(3, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(3, 1);
    lcd.print("00");
    lcd.setCursor(5, 1);
    lcd.print(":");
    delay(300);
    if (digitalRead(JOYSTICK_SW) == LOW) {
      press = 4;
      Serial.print("4 sw after: ");              //test
      Serial.println(digitalRead(JOYSTICK_SW));  //test
    }
  }
  // 5
  while (press == 4) {
    lcd.setCursor(7, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(7, 1);
    lcd.print("00");
    lcd.setCursor(9, 1);
    lcd.print(":");
    delay(300);
    if (digitalRead(JOYSTICK_SW) == LOW) {
      press = 5;
      Serial.print("5 sw after: ");              //test
      Serial.println(digitalRead(JOYSTICK_SW));  //test
    }
  }
  // 6
  while (press == 5) {
    lcd.setCursor(11, 1);
    lcd.print("  ");
    delay(300);
    lcd.setCursor(11, 1);
    lcd.print("00");
    delay(300);
    if (digitalRead(JOYSTICK_SW) == LOW) {
      press = 6;
      Serial.print("7 sw after: ");              //test
      Serial.println(digitalRead(JOYSTICK_SW));  //test
    }
  }


  // 0
  if (press == 6) {
    press = 0;
    Serial.print("0 sw after: ");              //test
    Serial.println(digitalRead(JOYSTICK_SW));  //test
  }
}
