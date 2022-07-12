#include "tfplus.h"
#include <Wire.h>

tfplus lidar(0x10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lidar.begin(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  lidar.getData();
  Serial.println(lidar.distance);
  delay(1000);
}
