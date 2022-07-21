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
}

void Mapping::getMap(void){
     if(millis() - this->time >= this->rate){
        this->servo->write(this->angle);
        this->lidar->getData();
        map_array[this->angle] = this->lidar->distance;
        if(this->angle <= 0){
            this->increment = true;
        }
        else if(this->angle > 80){
            this->increment = false;
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
