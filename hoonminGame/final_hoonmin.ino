#include "korConsonant.h"
#include "random.h"
#include "timer.h"
#include "hoonmin.h"


void setup() {

  pinMode(BUTTON_JAEM, INPUT_PULLUP);
  pinMode(BUTTON_PERSON1, INPUT_PULLUP);
  pinMode(BUTTON_PERSON2, INPUT_PULLUP);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BUZZER1, OUTPUT);
  pinMode(BUZZER2, OUTPUT);
  pinMode(ST_CP, OUTPUT);
  pinMode(SH_CP, OUTPUT);
  pinMode(DS, OUTPUT);


  for (int i = 0; i < 2; i++) {
    dote.shutdown(i, false);
    dote.setIntensity(i, 3);
    dote.clearDisplay(i);
  }
  
}

void loop() {
  static int count = 300;

  while (1) {

    ft_jaem();
    displayNumber(count);
    ft_buttonLed();

    if (count == 0)
      break;
    count--;
  }
}

void ft_jaem(void) {
  int buttonState_jaem = digitalRead(BUTTON_JAEM);

  if (buttonState_jaem) {
    ft_random(1, getTrueRotateRandomByte() % SIZE_OF_JAEM);
    delay(100);
    ft_random(0, getTrueRotateRandomByte() % SIZE_OF_JAEM);
    delay(100);
  }
}

void ft_random(int module, int row) {
  for (int i = 0; i < 8; i++)
    dote.setRow(module, i, ja_em[row][i]);
}

void ft_buttonLed(void) {
  int buttonState_person1 = digitalRead(BUTTON_PERSON1);
  int buttonState_person2 = digitalRead(BUTTON_PERSON2);

  if (buttonState_person1) {
    digitalWrite(LED_1, HIGH);
    tone(BUZZER1, NOTE_C4, 300);
  } else {
    digitalWrite(LED_1, LOW);
    noTone(BUZZER1);
    digitalWrite(BUZZER1, LOW);
  }

  if (buttonState_person2) {
    digitalWrite(LED_2, HIGH);
    tone(BUZZER2, NOTE_F5, 300);
  } else {
    digitalWrite(LED_2, LOW);
    noTone(BUZZER2);
    digitalWrite(BUZZER2, LOW);
  }
}
