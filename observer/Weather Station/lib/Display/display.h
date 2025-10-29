#ifndef DISPLAY_H
#define DISPLAY_H

class Weather;

class Display {
    protected:
        Weather* weather;  // Referencia al weather que observa
        
    public:
        Display();
        Display(Weather* w);
        ~Display();
        virtual void update();  // Recibe el weather actualizado
};



#endif