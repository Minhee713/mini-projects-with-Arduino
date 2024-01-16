# mini-projects-with-Arduino  


## 프로젝트명 : 아두이노로 훈민정음 게임하기   

## 개요  
![훈민정음게임](https://github.com/Minhee713/mini-projects-with-Arduino/assets/127821647/27f6fc00-7ec4-42d3-9aa2-c5b424fc966a)


## 내용  
- 게임 참가자 2명이 LED에 나타난 2개의 자음을 보고 생각나는 단어를 말함
- 각자에게 할당된 버튼을 누르고 올바른 단어를 먼저 말한 사람이 승리
- 타이머에 나타난 시간 내에 말해야 함    

## 하드웨어 구성  
- Arduino Uno 보드 
- 브레드 보드 2개
- 도트 매트릭스 2개
- 4bit LED Digital Tube Module 1개
- 택트 스위치 3개
- 220저항 5개
- LED (빨강, 초록 각각 1개씩)  
- 피에조 부저 2개   

## 파일 구성  
- minheeKwon_final_hoonminGame_230817.ino: setup()함수와 loop()함수가 있는 메인함수 파일
- hoonmin.h: LedControl관련 객체와 핀 설정을 위한 매크로 정의가 담겨 있음
- korConsonant.h: 자음 출력을 위한 자음 배열이 담겨 있음 
- random.h: 자음 랜덤 출력을 위한 난수 생성 함수가 담겨 있음 
- timer.h: 4bit LED Tube를 제어하기 위한 함수가 담겨 있음   

## 발생 문제  
- 자음 랜덤 출력을 제어하는 버튼을 눌렀을 때 결선된 수동 부저에서 미세한 노이즈가 발생함
- 리셋 버튼을 눌렀을 경우 노이즈가 사라짐
- LED제어 버튼을 눌렀을 땐 노이즈가 없고, 자음 출력 버튼을 눌렀을 경우에만 노이즈가 발생하며 리셋 되기 전까지 노이즈 현상이 사라지지 않음  

## 문제 원인  
- 도트 매트릭스와 SPI통신을 하는 과정에서 노이즈가 발생하는 것으로 추론  

## 문제 해결 방법  
- 도트 매트릭스를 제어하는 다른 라이브러리를 사용하여 코드를 수정하려 했으나
  시간적 여유가 많지 않아 해당 방법으로 해결하지 못함 
- 수동 부저를 피에조 부저로 바꾸는 방법으로 문제를 해결 함   

## 아쉬운 점  
- 도트 매트릭스를 제어할 수 있는 다른 라이브러리를 사용하여 코드를 수정함으로써 수동 부저의 노이즈 발생 문제를 해결하지 못한 것이 아쉬움
- 타이머를 제어하는 장치를 추가하지 못함. 현재 작성된 프로그램은 프로그래밍 
  시작과 동시에 타이머가 작동하는데, 버튼이나 기타 장치를 통해 사용자가 원하
  는 타이밍에 타이머를 작동할 수 있도록 구현했다면 더 좋았을 듯함
- 타이머의 시간이 정확하지 않음     
