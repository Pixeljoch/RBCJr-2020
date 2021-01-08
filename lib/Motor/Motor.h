#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>
#include <Motor.h>
#include <Core.h>

class Motor {
    private:
        int in1, in2, enc1, enc2, pwm;
        float speeddiff;
    public:
        Motor(int in1, int in2, int pwm, int enc1, int enc2, float speeddiff);
        Motor(int in1, int in2, int pwm, int enc1, int enc2);
        void test(); 
        void move(float speed);
        void setup();
};

class MotorControl {
    private:
        Motor m1, m2, m3;
    public:
        MotorControl(Motor m1, Motor m2, Motor m3);
        void forward(float time); 
        void backward(float time);
        void right(float degrees);
        void left(float degrees);
};

#endif