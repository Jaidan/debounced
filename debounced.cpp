#include "Arduino.h"
#include "debounced.h"

Debounced::Debounced(uint8_t pin, debfuncptr callback, uint8_t debounceDelay) {
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
  _debounceDelay = debounceDelay;
  _callback = callback;
  lastState = digitalRead(_pin);
}
Debounced::Debounced(uint8_t pin, debfuncptr callback) {
  pinMode(pin, INPUT_PULLUP);
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
