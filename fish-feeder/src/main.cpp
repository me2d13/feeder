#include <Arduino.h>

const int in1 =  9;
const int in2 = 10;
const int in3 = 11;
const int in4 = 12;
const int outGnd = 8;
const int inFeed = 7;
const int inStep = 6;

const unsigned char steps[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};

int gStepIndex = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(outGnd, OUTPUT);
  digitalWrite(outGnd, LOW);
  pinMode(inFeed, INPUT_PULLUP);
  pinMode(inStep, INPUT_PULLUP);
}

void turn(int angle, int speed) {
  for(int i=0;i<(angle*64*8/45);i++)
  {
    digitalWrite(in1, steps[gStepIndex] & 0x01);
    digitalWrite(in2, steps[gStepIndex] & 0x02 ? HIGH : LOW);
    digitalWrite(in3, steps[gStepIndex] & 0x04 ? HIGH : LOW);
    digitalWrite(in4, steps[gStepIndex] & 0x08 ? HIGH : LOW);
    gStepIndex++;
    if (gStepIndex == 8) {
      gStepIndex = 0;
    }
    delay(speed);
  }
}

void zero() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  if (digitalRead(inFeed) == LOW) {
    turn(45, 5);
    zero();
  }
  if (digitalRead(inStep) == LOW) {
    turn(1, 10);
    zero();
  }
  delay(20);
}
