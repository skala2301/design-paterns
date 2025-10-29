

#include "display.h"
#include "../Weather/weather.h"
#include <iostream>

Display::Display() : weather(nullptr) {
}

Display::Display(Weather* w) : weather(w) {
}

Display::~Display() {
    this->weather = nullptr;
}

void Display::update() {
    if (this->weather) {
        std::cout << "Display actualizado - Temp: " << this->weather->getTemperature() 
                  << "°C, Presión: " << this->weather->getPressure() << " hPa\n";
    }
}