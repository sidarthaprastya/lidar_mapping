#include <ros.h>
#include <mapping/mapping_vect.h>

#include "tfplus.h"
#include <Wire.h>
#include <Servo.h>
#include "mapping.h"

#define rotator_pin 4

ros::NodeHandle nh;
mapping::mapping_vect map_msg;
ros::Publisher map_pub("map_lidar", &map_msg);


tfplus lidar(0x10);
Servo rotator;
Mapping mapper(1000, &lidar, &rotator);

int j;

void map_post(){
  for(j=0; j<180; j++){
    map_msg.map_vect[j] = mapper.map_array[j];
  }
}

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  Serial.begin(115200);
  lidar.begin(1000);
//  rotator.attach(rotator_pin, 544,1100);
  rotator.attach(rotator_pin);
  mapper.begin();
  nh.advertise(map_pub);
}

void loop() {
  // put your main code here, to run repeatedly:
//  lidar.getData();
//  Serial.println(lidar.distance);
//  delay(100);
  mapper.getMap();
//  mapper.rotate_test();
  map_post();
  map_pub.publish(&map_msg);
  nh.spinOnce();
    

  delay(3);
}
