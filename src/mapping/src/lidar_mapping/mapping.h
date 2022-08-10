#ifndef MAPPING_H
#define MAPPING_H

#include <Arduino.h>
#include <Servo.h>
#include "tfplus.h"

class Mapping{
    private:
        tfplus* lidar;
        Servo*  servo;

        uint8_t angle;
        float rate;
        uint32_t time;
        bool increment;
        float x[2], y[2];

    public:
        Mapping(int frequency, tfplus* lidar, Servo* servo);
        void begin(void);
        void getMap(void);
        void resetMap(void);
        void rotate_test(void);

        uint16_t map_array[180];

};

#endif
