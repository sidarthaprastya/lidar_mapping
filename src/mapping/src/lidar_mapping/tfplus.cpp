#include "tfplus.h"
#define I2C_MODE 1

//This library is made for ESP32

uint8_t OBTAIN_DATA_CM[5] =   {0x5A, 0x05, 0x00, 0x01, 0x60};

uint8_t SET_BAUD_9600[8] = {0x5A, 0x08, 0x06, 0x00, 0x00, 0x25, 0x80, 0x0D};
uint8_t SET_BAUD_115200[8] = {0x5A, 0x08, 0x06, 0x00, 0x01, 0xC2, 0x00, 0x2B};
uint8_t SET_BAUD_128000[8] = {0x5A, 0x08, 0x06, 0x00, 0x01, 0xF4, 0x00, 0x5D};

uint8_t FRAME_100[6] = {0x5a,0x06,0x03,0x64,0x00,0xc7};
uint8_t FRAME_1000[6] = {0x5a,0x06,0x03,0x64,0x00,0xc7};

uint8_t SAVE[4] = {0x5A, 0x04, 0x11, 0x6F};

int i;

#ifdef I2C_MODE

tfplus::tfplus(char address=0x10){
    this->address = address;
}

void tfplus::begin(int frequency=100){
    Wire.begin();
    Wire.setClock(frequency);

//    Wire.beginTransmission(this->address);
//    Wire.write(FRAME_100, sizeof(FRAME_100));
//    Wire.endTransmission();

//    Wire.beginTransmission(this->address);
//    Wire.write(SAVE, sizeof(SAVE));
//    Wire.endTransmission();
}

void tfplus::getData(void){
    Wire.beginTransmission(this->address);

    Wire.write(OBTAIN_DATA_CM, sizeof(OBTAIN_DATA_CM));
    Wire.endTransmission();
    i = 0;
    Wire.requestFrom(this->address, 9);
    while(Wire.available()){
        data[i] = Wire.read();
        i++;
    }

    distance = (data[3] << 8) | data[2];
    strength = (data[5] << 8) | data[4];
    temperature = (data[7] << 8) | data[6];
}

#endif


#ifdef UART_MODE

tfplus::tfplus(uint8_t RX, uint8_t TX, unsigned long baud){
    this->uart.begin(baud, SERIAL_8N1, RX, TX);
    if(baud == 9600){
        for(i=0; i<9; i++){
            this->uart.write(SET_BAUD_9600[i]);
        }
    }
    if(baud == 115200){
        for(i=0; i<9; i++){
            this->uart.write(SET_BAUD_115200[i]);
        }
    }
    if(baud == 128000){
        for(i=0; i<9; i++){
            this->uart.write(SET_BAUD_128000[i]);
        }
    }
    
}



#endif
