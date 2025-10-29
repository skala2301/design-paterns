#ifndef WEATHER_H
#define WEATHER_H
#include <memory>
#include <vector>
#include <algorithm>
#include "../Display/display.h"

class Weather{
    protected:
        double temperature = 0.00;
        double pressure = 0.00;
        std::vector<std::shared_ptr<Display>> displays;

    public:
        Weather();
        ~Weather();
        double getTemperature();
        double getPressure();


        void addDisplay(std::shared_ptr<Display> display);
        void removeDisplay(std::shared_ptr<Display> display);
        void notifyDisplays();  // Actualiza todos los displays
        void setTemperature(double temp);
        void setPressure(double press);

};



#endif