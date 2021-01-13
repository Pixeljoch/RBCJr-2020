#include <Arduino.h>
#include <math.h>
#include <Core.h>
#include <Gyro.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>


void Gyro::setup() {
    mpu.begin();
}



