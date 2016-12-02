/*
 * Program acts as a controller for
 * a dishwasher with 'Economy', 'Deluxe',
 * and 'Super Deluxe' settings.
 */

#include <Arduino.h>
#include <Wire.h>

enum State {
  idle,            //idle
  econWash,        //economy cold water wash
  econDry,         //economy dryer
  deluxWash,       //deluxe hot water wash
  deluxDry,        //deluxe dryer
  supDeluxWash,    //super deluxe wash (7s hot water, then 7s hot + cold water)
};

State washState = idle;   //set current state to idle

int yellowPin  =  4;      //respective numbers of each pin
int redPin     =  3;
int greenPin   =  2;
int analogPin  =  0;
int buttonPin  =  5;
int lockedPin  = 13;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);   //set pinMode for each pin
  pinMode(lockedPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  washState = nextState(washState);
}

State nextState(State state) {
  switch (state) {
    
    case idle:
    
      digitalWrite(yellowPin, LOW);   //turn all pins off
      digitalWrite(redPin, LOW);
      digitalWrite(greenPin, LOW);
      digitalWrite(lockedPin, LOW);   //door is 'unlocked'

      if (!digitalRead(buttonPin)) {        //if button is pressed
        digitalWrite(lockedPin, HIGH);      //washer becomes 'locked' (lockedPin turned on)
        if (analogRead(analogPin) < 341) {
          state = supDeluxWash;              //set to super deluxe when dial set to voltage under 341
        }                                   
        else if (analogRead(analogPin) > 682) {
          state = econWash;                 //set to economy setting when dial set to voltage over 682
        }
        else {
          state = deluxWash;                 //set to deluxe setting when dial voltage between 341 and 682, inclusive
        }
      }
      
      break;

    case econWash:
      digitalWrite(greenPin, HIGH);
      
      for (int i = 1; i < 5000; i++) {       //wait 5s for economy wash
        delay(1);
        if (analogRead(analogPin) <= 682) {  //checks every millisecond if dial has been turned to deluxe or super deluxe
          state =  deluxDry;                 //if dial has been turned clockwise, changes states to deluxe dry
        }
      }

      if (state != deluxDry) {
        state = econDry;   //if change did not occurr, transitions to economy dry
      }
      break;

    case econDry:
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, HIGH);

      delay(2000);      //wait 2s for economy dry
      
      state = idle;     //set back to idle when wash and dry is finished

      break;

    case deluxWash:
      digitalWrite(redPin, HIGH);

      for (int j = 1; j < 7000; j++) {      //wait 7s for deluxe wash
        delay(1);
        if (analogRead(analogPin) > 682) {
          state = econDry;                  //if dial has been turned enough counter clockwise, set to economy dry
        }
      }
      
      if (state != econDry) {
        state = deluxDry;          //if change did not occurr, transitions to deluxe dry
      }

      break;

    case deluxDry:                    //counts as dry for both deluxe and super deluxe since
      digitalWrite(redPin, LOW);      //both have the same amount of time, outputs (also both
      digitalWrite(greenPin, LOW);    //occur after switch from economy wash)
      digitalWrite(yellowPin, HIGH);

      delay(7000);    //wait 7s for deluxe dry

      state = idle;   //set back to idle when wash and dry is finished

      break;

    case supDeluxWash:
      digitalWrite(redPin, HIGH);

      for (int k = 1; k < 7000; k++) {    //wait 7s for super deluxe hot water wash
        delay(1);
        if (analogRead(analogPin) > 682) {
          state = econDry;
        }
        else if (analogRead(analogPin) >= 341) {
          state = deluxDry;
        }
      }

      if (state != supDeluxWash) {
        break;
      }
      
      digitalWrite(greenPin, HIGH);   //both hot and cold water pins are on
 
      for (int k = 1; k < 7000; k++) {      //wait 7s for super deluxe medium water watch
        delay(1);
        if (analogRead(analogPin) > 682) {
          state = econDry;
        }
      }

      if (state != econDry) {
        state = deluxDry;
      }

      break;
    
  }
  return state;
}

