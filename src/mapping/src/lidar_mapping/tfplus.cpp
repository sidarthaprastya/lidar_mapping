#include "tfplus.h"

uint8_t OBTAIN_DATA_CM[5] =   {0x5A, 0x05, 0x00, 0x01, 0x60};
int i;

tfplus::tfplus(char address=0x10){
    this->address = address;
}

void tfplus::begin(int frequency=1000){
    Wire.begin();
    Wire.setClock(frequency);
}

void tfplus::getData(void){
    Wire.beginTransmission(this->address);

    Wire.write(OBTAIN_DATA_CM, sizeof(OBTAIN_DATA_CM));
    Wire.endTransmission();
    i = 0;
    Wire.requestFrom(this->address, 8);
    while(Wire.available()){
        data[i] = Wire.read();
        i++;
    }

    distance = (data[3] << 8) | data[2];
    strength = (data[5] << 8) | data[4];
    temperature = (data[7] << 8) | data[6];
}
