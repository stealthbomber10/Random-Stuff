/*
 * Program to get weather data from
 * specified places on the inernet
 * and display it on Arduino. Arduino
 * side measures potentiometer value,
 * receives weather char from PC
 * side.
 */

#include <Arduino.h>
#include <Wire.h>
#include "font.h"

const int analogPin = A0;
const int MAGIC_NUM = '!';
const int POTENTIOMETER = 0x33; //2-Byte Integer

const int ROW_SIZE = 7;
const int COL_SIZE = 5;

const int row[ROW_SIZE] = { 2, 3, 4, 5, 6, 7, 8 };

const int col[COL_SIZE] = { 9, 10, 11, 12, 13 };

int counter = 0x00;
unsigned long lastTime = 0;
long period = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(DEFAULT);
  for (int i = 0; i < ROW_SIZE; i++) {
    pinMode(row[i], OUTPUT);
  }

  for (int i = 0; i < COL_SIZE; i++) {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (newPeriod()) {
    int reading = analogRead(analogPin);
    Serial.println(reading);
    sendPotentiometer(reading);
  }
  if (Serial.available() > 0) {
    if (Serial.read() == MAGIC_NUM) {
      char input = Serial.read();
      counter = (int) input;
    }
  }
  charDisplay();
}

void sendPotentiometer(int reading)
{
  Serial.write(MAGIC_NUM);
  Serial.write(POTENTIOMETER);
  Serial.write(reading >> 8);
  Serial.write(reading);
}

void charDisplay() {
  for (int i = 0; i < COL_SIZE; i++) {
    char line = font_5x7[counter][i];
    digitalWrite(col[i], LOW);
    for (int j = 0; j < 7; j++) {
      if (line & 0x02) {
        digitalWrite(row[j], HIGH);
      }
      else {
        digitalWrite(row[j], LOW);
      }
      line >>= 1;
    }
    delay(2);
    digitalWrite(col[i], HIGH);
  }
}

bool newPeriod() {
  long deltaTime = millis() - lastTime;
  if (deltaTime > period) {
    lastTime = millis();
    return true;
  }
  return false;
}

