#ifndef PHOTORESISTOR_H
#define PHOTORESISTOR_H

#include <Arduino.h>

class Photoresistor {
public:
    Photoresistor(int pin);
    void begin();
    int readLight();
private:
    int _pin;
};

#endif