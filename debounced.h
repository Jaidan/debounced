#ifndef debounced_h
#define debounced_h
#include "Arduino.h"

typedef void (*debfuncptr)(int);

class Debounced 
{
  public:
    Debounced(const int pin, debfuncptr callback);
    Debounced(const int pin, debfuncptr callback, int debounceDelay);
    void readButton();
  private:
    int _pin;
    int _debounceDelay;
    int lastState = LOW;
    int state = LOW;   
    unsigned long stateChanged;
    debfuncptr _callback;
    bool debounced();
    void startDebounce();
};
#endif