#ifndef _HOONMIN_H
#define _HOONMIN_H 

#include <LedControl.h>

#define BUTTON_JAEM 8
#define BUTTON_PERSON1 9
#define BUTTON_PERSON2 10
#define LED_1 11
#define LED_2 12
#define DIN_PIN 7
#define CLK_PIN 6
#define CS_PIN 5
#define BUZZER1 A3
#define BUZZER2 A4
#define SIZE_OF_JAEM sizeof(ja_em) / sizeof(ja_em[0])
#define NOTE_C4 262
#define NOTE_F5 698
#define DEVICE_NUM 2



LedControl dote = LedControl(DIN_PIN, CLK_PIN, CS_PIN, DEVICE_NUM);  // pin: DIN, CLK, CS



#endif