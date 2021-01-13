#ifndef GYRO_H_
#define GYRO_H_

#include <Arduino.h>
#include <math.h>
#include <Core.h>
#include <Gyro.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

static float startMillis;

void gyroSetup();

void getGyroShizzle();

    
#endif