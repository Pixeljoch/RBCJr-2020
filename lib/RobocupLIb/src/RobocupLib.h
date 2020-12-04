#ifndef ROBOCUPLIBREWRITE_H_
#define ROBOCUPLIBREWRITE_H_


#include <Arduino.h>
#include <math.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

static float startMillis;

void gyroInit();
float calculateElapsedTime(float delayTime);
float returnGyro();
float calculateError(int calTime);
float calculateDegree(float errorMargin, float delayTime);

class TMotor {
    private:
        int in1, in2, pwm;
        int lastSpeed = 0;
        bool isOn;
    public:
        TMotor::TMotor(int pin1, int pin2, int pin3);
        void move(int setPWM);
};

class IR_SENSOR{
    private:
        int ir_pin;
    public:
        IR_SENSOR::IR_SENSOR(int pin);
        int readSensor();
};



#endif