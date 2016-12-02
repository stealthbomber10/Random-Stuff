/*
 * Trent Andraka
 * 
 * WUSTL Key: trentandraka
 * 
 * CSE 132
 * Lab H
 * Morse Assignment
 */

#include"MorseCodes.h"

const int led = 2;
const int unit = 500;
int letterTime = unit;
unsigned long lastTime;

// Argument: Any character
// Return Value: Either:
//                  1) If the character is a letter, the upper case equivalent.  
//                  2) If the character is not a letter, the original value.
char toUpper(char c) {
  // TODO
  if (c >= 'a' && c <= 'z') {
    return c^32;
  }
  else {
    return c;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}


void convertIncomingCharsToMorseCode() {
  // TODO
  if (Serial.available() > 0) {
    
    char input = Serial.read();
    digitalWrite(led, LOW);
    String morse = morseEncode(input);
    
    for (int i = 0; i < morse.length(); i++) {
      digitalWrite(led, LOW);
      lastTime = millis();
      while (millis() - lastTime <= letterTime) {
        if (morse[i] == '.') {
          digitalWrite(led, HIGH);
          letterTime = unit;
        }
        else if (morse[i] == '-') {
          digitalWrite(led, HIGH);
          letterTime = unit * 3;
        }
        else {
          digitalWrite(led, LOW);
          letterTime = 0;
        }
      }
      lastTime = millis();
      while(millis() - lastTime <= unit) {
        digitalWrite(led, LOW);
      }
      
      while (millis() - lastTime <= (unit * 3)) {
        digitalWrite(led, LOW);
      }
    }
  }
}

void loop() {
  // No Need to Modify this.  Put most of your code in "convertIncomingCharsToMorseCode()"
  convertIncomingCharsToMorseCode();
}
