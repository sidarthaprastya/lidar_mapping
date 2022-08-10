#include "mapping.h"
#include <math.h>

uint8_t k = 0;

Mapping::Mapping(int frequency, tfplus* lidar, Servo* servo){
    this->rate = round((1/ (float)frequency) * 1000);
    this->lidar = lidar;
    this->servo = servo;
}

void Mapping::begin(void){
    this->angle = 0;
    this->servo->write(angle);
    this->increment = true;
    this->time = millis();
    this->x[0] = 0.0;
    this->y[0] = 0.0;
}

void Mapping::getMap(void){
     if(millis() - this->time >= this->rate){
        this->servo->write(this->angle);
//        this->x[1] = x[0];
        this->lidar->getData();
//        this->x[0] = (float)this->lidar->distance;
//        this->y[1] = this->y[0];
//        this->y[0] = 0.33 * this->x[0] + 33.33 * this->x[1] - 33 * this->y[1];
//        this->y[0] = 0.0476 * this->x[0] + 0.0476 * this->x[1] + 0.9048 * this->y[1];
        map_array[this->angle] = this->lidar->distance;
//        map_array[this->angle] = this->y[0];
        if(this->angle <= 0){
            this->increment = true;
//            this->x[0] = 0.0;
//            this->x[1] = 0.0;
//            this->y[0] = 0.0;
//            this->y[1] = 0.0;
        }
        else if(this->angle > 178){
            this->increment = false;
//            this->x[0] = 0.0;
//            this->x[1] = 0.0;
//            this->y[0] = 0.0;
//            this->y[1] = 0.0;
        }

        if(this->increment == true){
            this->angle+=1;
        }
        else{
            this->angle-=1;
        }
//        Serial.println(this->angle);
         this->time = millis();
    }
    
}

void Mapping::resetMap(void){
    this->angle = 0;
//    this->map_array = {0};
    this->servo->write(angle);
}

void Mapping::rotate_test(void){
    for (k = 0; k < 99; k++)
    {
        this->servo->write(k);
        delay(1);
        this->lidar->getData();
        map_array[k] = this->lidar->distance;
    }
    for (k = 99; k > 0; k--)
    {
        this->servo->write(k);
        delay(1);
        this->lidar->getData();
        map_array[k] = this->lidar->distance;
    }
    Serial.println(map_array[99]);
    
    
}
