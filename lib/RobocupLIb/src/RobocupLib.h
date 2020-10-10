#ifndef ROBOCUPLIBREWRITE_H_
#define ROBOCUPLIBREWRITE_H_

#include <Arduino.h>
#include <math.h>

class TMotor {
    private:
        int in1, in2, pwm;
        int lastSpeed = 0;
        bool isOn;
        void TMotor::cruise(int speedCurrent, int speedFinal, double acc, int motorDelay);
    public:
        TMotor::TMotor(int pin1, int pin2, int pin3);
        void move(int setPWM, double acc, int motorDelay);
};



#endif