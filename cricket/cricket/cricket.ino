/*
 * Program acts as thermometer
 * that measures the temperature
 * to the number of times the LED
 * blinks, or the number of 
 * 'cricket chirps.'
 */

#include <Arduino.h>
#include <Wire.h>

unsigned long lastTime = 0;
unsigned long ledTime = 0;

const int ledPin = 2;
const int analogPin = 1;
const long interval = 500;
const long BLINK_DURATION = 200;
const int FILTER_COUNTS = 7;

float temperatures[FILTER_COUNTS];
int count = 0;
float currentTemp = 25;

boolean ledIsOn = false;

void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  if (millis() - lastTime >= interval) {
    currentTemp = readTemp();
    Serial.print(currentTemp);
    Serial.print(",");
    Serial.println(mean());
    lastTime = millis();
  }

  float period = 60000 / (7 * (currentTemp - 10) + 40);
  
  if(ledIsOn){
    if(millis() - ledTime >= BLINK_DURATION){

      ledIsOn = !ledIsOn;
      ledTime = millis();
    }
  }else{
    if (millis() - ledTime >= (period - BLINK_DURATION)) {

      ledIsOn = !ledIsOn;
      ledTime = millis();
    }
  }
  digitalWrite(ledPin, ledIsOn);
}

float readTemp() {
  int reading = analogRead(analogPin);
  float temp = 25 + (reading * 1.1 / 1024 - 0.75) * 100;
  temperatures[count % FILTER_COUNTS] = temp;
  count += 1;

  return temp;
}

float mean() {
  float sum = 0;
  int len;
  
  if (count < FILTER_COUNTS) {
    len = count % FILTER_COUNTS;
  }
  else {
    len = FILTER_COUNTS;
  }

  for (int i = 0; i < len; i++) {
    sum += temperatures[i];
  }
  return sum / len;
}

