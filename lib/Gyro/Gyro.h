#ifndef GYRO_H_
#define GYRO_H_

#include <Arduino.h>
#include <math.h>
#include <Core.h>
#include <Gyro.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

class Gyro {
    private:
        Adafruit_MPU6050 mpu;
    public:
        Gyro();
        void setup();

}

    
#endif