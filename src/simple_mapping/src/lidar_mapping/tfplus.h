#ifndef TFPLUS_H
#define TFPLUS_H

#include <Arduino.h>
#include <Wire.h>

// This Library is made for Arduino UNO

class tfplus{
    private:
        char address;
        char data[9];

    public:
        // Initiate device TFPlus
        tfplus(char address);

        void begin(int frequency);

        // Get data: Distance, strength, and temperature
        void getData(void);

        int distance;
        int strength;
        int temperature;
};

#endif
