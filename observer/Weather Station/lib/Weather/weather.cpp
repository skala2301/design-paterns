
#include "weather.h"



Weather::Weather(){
    
}

Weather::~Weather(){

}

double Weather::getTemperature(){
    return this->temperature;
}

double Weather::getPressure(){
    return this->pressure;
}


void Weather::addDisplay(std::shared_ptr<Display> display) {
    this->displays.push_back(display);
}

void Weather::removeDisplay(std::shared_ptr<Display> display) {
    // Busca y elimina el display
    this->displays.erase(
        std::remove(this->displays.begin(), this->displays.end(), display),
        this->displays.end()
    );
}

void Weather::notifyDisplays() {
    // Actualiza todos los displays cuando cambia el clima
    for (auto& display : this->displays) {
        display->update();
    }
}

void Weather::setTemperature(double temp) {
    this->temperature = temp;
    this->notifyDisplays();  // Notifica a los displays del cambio
}

void Weather::setPressure(double press) {
    this->pressure = press;
    this->notifyDisplays();  // Notifica a los displays del cambio
}
