#ifndef TFPLUS_H
#define TFPLUS_H

#include <Arduino.h>
#include <Wire.h>


class tfplus{
    private:
        char address;
        uint8_t data[9];
        //uart_t* uart;

    public:
        // Initiate device TFPlus
        tfplus(char address);

        void begin(int frequency);

        // Get data: Distance, strength, and temperature
        void getData(void);

        uint16_t distance;
        uint16_t strength;
        uint16_t temperature;
};

#endif
