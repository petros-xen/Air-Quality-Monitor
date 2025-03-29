#include "Photoresistor.h"

Photoresistor::Photoresistor(int pin) {
    _pin = pin;
}

void Photoresistor::begin() {
    pinMode(_pin, INPUT);
}

int Photoresistor::readLight() {
    return analogRead(_pin);
}