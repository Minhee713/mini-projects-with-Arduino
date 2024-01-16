#ifndef _RANDOM_H
#define _RANDOM_H

/* 난수 생성 헤더 */
/* 출처: https://gist.github.com/bloc97/b55f684d17edd8f50df8e918cbc00f94 (Method 1 코드 사용) */

const int waitTime = 16;

byte rotate(byte b, int r) {
  return (b << r) | (b >> (8-r));
}

void pushLeftStack(byte bitToPush) {
  byte leftStack = (leftStack << 1) ^ bitToPush ^ leftStack;
}
void pushRightStackRight(byte bitToPush) {
  byte rightStack = (rightStack >> 1) ^ (bitToPush << 7) ^ rightStack;
}

byte lastByte = 0;

byte leftStack = 0;
byte rightStack = 0;

byte getTrueRotateRandomByte() {
  byte finalByte = 0;
  
  byte lastStack = leftStack ^ rightStack;
  
  for (int i=0; i<4; i++) {
    delayMicroseconds(waitTime);
    int leftBits = analogRead(1);
    
    delayMicroseconds(waitTime);
    int rightBits = analogRead(1);
    
    finalByte ^= rotate(leftBits, i);
    finalByte ^= rotate(rightBits, 7-i);
    
    for (int j=0; j<8; j++) {
      byte leftBit = (leftBits >> j) & 1;
      byte rightBit = (rightBits >> j) & 1;
  
      if (leftBit != rightBit) {
        if (lastStack % 2 == 0) {
          pushLeftStack(leftBit);
        } else {
          pushRightStackRight(leftBit);
        }
      }
    }
    
  }
  lastByte ^= (lastByte >> 3) ^ (lastByte << 5) ^ (lastByte >> 4);
  lastByte ^= finalByte;
  
  return lastByte ^ leftStack ^ rightStack;
}

#endif