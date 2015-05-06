#ifndef debounced_h
#define debounced_h
#include "Arduino.h"

typedef void (*debfuncptr)(int);

class DebouncedCallback
{
    public:
        virtual void callback(int state) = 0;
};

class BasicDebouncedCallback : public DebouncedCallback
{
    public:
        BasicDebouncedCallback(debfuncptr callback);
        virtual void callback(int state);
    private:
        debfuncptr callbackFunc;
};

class Debounced 
{
  public:
    Debounced(const uint8_t pin, DebouncedCallback *functoidCallback);
    Debounced(const uint8_t pin, DebouncedCallback *functoidCallback, uint8_t debounceDelay);
    void readButton();
  private:
    uint8_t pin;
    uint8_t debounceDelay;
    uint8_t lastState = LOW;
    uint8_t state = LOW;   
    uint32_t stateChanged;
    DebouncedCallback *callback;
    bool debounced();
    void startDebounce();
};
#endif
