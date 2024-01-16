#include "korConsonant.h"  // 자음 배열 헤더
#include "random.h"        // 랜덤 함수 헤더
#include "timer.h"         // 4비트 LED 모듈을 이용한 타이머 헤더
#include "hoonmin.h"       // 매크로 정의 헤더


void setup() {

  pinMode(BUTTON_JAEM, INPUT_PULLUP);     // 핀 8번. 도트 매트릭스에 자음을 제어하기 위한 버튼핀 설정
  pinMode(BUTTON_PERSON1, INPUT_PULLUP);  // 핀 9번. 참가자가 누를 버튼핀 설정
  pinMode(BUTTON_PERSON2, INPUT_PULLUP);  // 핀 10번.참가자가 누를 버튼핀 설정
  pinMode(LED_1, OUTPUT);                 // 핀 11번.참가자가 버튼을 눌렀을 때 나오는 LED핀 설정
  pinMode(LED_2, OUTPUT);                 // 핀 12번.참가자가 버튼을 눌렀을 때 나오는 LED핀 설정
  pinMode(BUZZER1, OUTPUT);               // 핀 A3번.참가자가 버튼을 눌렀을 때 나오는 부저핀 설정 
  pinMode(BUZZER2, OUTPUT);               // 핀 A4번.참가자가 버튼을 눌렀을 때 나오는 부저핀 설정
  pinMode(ST_CP, OUTPUT);                 // 핀 A1. 4비트 LED Digital Tube 모듈 RCLK 연결 핀 설정
  pinMode(SH_CP, OUTPUT);                 // 핀 A2. 4비트 LED Digital Tube 모듈 SCLK 연결 핀 설정
  pinMode(DS, OUTPUT);                    // 핀 A0. 4비트 LED Digital Tube 모듈 DIO 연결 핀 설정

  for (int i = 0; i < DEVICE_NUM; i++) {  // 도트 매트릭스 2개 설정
    dote.shutdown(i, false);              // 절전모드 '사용하지 않음'으로 설정
    dote.setIntensity(i, 3);              // 밝기 3으로 설정
    dote.clearDisplay(i);                 // LED 초기화
  }
}

void loop() {
  /* 
   * 타이머 카운트 시작 숫자 초기화. 
   * loop()가 반복될 때마다 300으로 초기화 되는 것을 방지하기 위하여 static 정적 변수 선언 
   */
  static int count = 1000;
  /*
   * 타이머가 300에서 0까지 카운트 될 동안 도트 매트릭스에 나타난 자음에 맞는 낱말을 말해야 함
   */  
  while (1) {

    ft_jaem();              
    displayNumber(count);                 // 타이머 LED에 숫자 출력하는 함수 
    ft_buttonLed();

    if (count == 0)
      break;
    count--;
  }
  
}

/*
 * 자음을 랜덤으로 바꾸는 함수.  
 * 버튼을 누를 때마다 2개의 도트 매트릭스에 나타나는 자음이 랜덤으로 바뀜
 * 중복을 최소화 하는, 보다 정확한 난수를 만들기 위하여 random.h에 있는 getTrueRotateRandomByte() 함수 사용
 * getTrueRotateRandomByte() 함수는 0 ~ 255까지의 숫자를 반환.
 * 반환된 숫자를 korConsonant.h파일에 있는 자음 배열의 크기로 나누면 배열의 '행'값이 나옴 
 * 계산된 행값을 ft_random함수에 매개변수로 주어 LED가 점등됨   
 */
void ft_jaem(void) {
  int buttonState_jaem = digitalRead(BUTTON_JAEM);

  if (buttonState_jaem) {
    for (int i = 0; i < DEVICE_NUM; i++) {
      ft_random(i, getTrueRotateRandomByte() % SIZE_OF_JAEM);
      delay(100);
    }
  }
}

/*
 * 모듈 번호와 자음 배열의 행값을 받아 LED를 점등하는 함수
 */
void ft_random(int module, int row) {
  for (int i = 0; i < 8; i++)
    dote.setRow(module, i, ja_em[row][i]);
}

/* 
 * 참가자 2명이 각각 버튼을 눌렀을 때 LED를 점등하고, 부저가 소리나게 하는 함수 
 */
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
