#include <ros.h>
#include <simple_mapping/mapping.h>

#include "tfplus.h"
#include <Wire.h>
#include <Servo.h>
#include "mapping.h"

#define rotator_pin 5

ros::NodeHandle nh;
simple_mapping::mapping map_msg;
ros::Publisher map_pub("map_lidar", &map_msg);


tfplus lidar(0x10);
Servo rotator;
Mapping mapper(100, &lidar, &rotator);

int j;

void map_post(){
  for(j=0; j<100; j++){
    map_msg.mapping[j] = mapper.map_array[j];
  }
}

void setup() {
  // put your setup code here, to run once:
  nh.initNode();
  Serial.begin(115200);
  lidar.begin(1000);
  rotator.attach(rotator_pin, 544,1100);
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
