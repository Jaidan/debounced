#include "Arduino.h"
#include "debounced.h"

#define DEFAULT_DELAY 50

Debounced::Debounced(uint8_t pin, DebouncedCallback *callback, uint8_t debounceDelay) :
    pin(pin),
    callback(callback),
    debounceDelay(debounceDelay)
{
    pinMode(pin, INPUT_PULLUP);
    lastState = digitalRead(pin);
    state = lastState;
}
Debounced::Debounced(uint8_t pin, DebouncedCallback *callback) :
    Debounced(pin, callback, DEFAULT_DELAY)
{
}

void Debounced::readButton() {
    int buttonState = digitalRead(pin);
    if (lastState != buttonState) {
        startDebounce();
    }
    if (debounced() && state != buttonState) {
        state = buttonState;
        callback->callback(buttonState);
    }
    lastState = buttonState;
}

bool Debounced::debounced() {
    return (millis() - stateChanged) > debounceDelay;
}

void Debounced::startDebounce() {
    stateChanged = millis();
}

BasicDebouncedCallback::BasicDebouncedCallback(debfuncptr callback) :
    callbackFunc(callback)
{

}

void BasicDebouncedCallback::callback(int state)
{
    callbackFunc(state);
}
