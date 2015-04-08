#include "Arduino.h"
#include "debounced.h"

Debounced::Debounced(int pin, debfuncptr callback, int debounceDelay) {
  pinMode(pin, INPUT);
  _pin = pin;
  _debounceDelay = debounceDelay;
  _callback = callback;
  lastState = digitalRead(_pin);
}
Debounced::Debounced(int pin, debfuncptr callback) {
  pinMode(pin, INPUT);
  _pin = pin;
  _debounceDelay = 50;
  _callback = callback;
  lastState = digitalRead(_pin);
  state = lastState;
}

void Debounced::readButton() {
  int buttonState = digitalRead(_pin);
  if (lastState != buttonState) {
    startDebounce();
  }
  if (debounced() && state != buttonState) {
    state = buttonState;
    _callback(buttonState);
  }
  lastState = buttonState;
}

bool Debounced::debounced() {
  return (millis() - stateChanged) > _debounceDelay;
}

void Debounced::startDebounce() {
  stateChanged = millis();
}
