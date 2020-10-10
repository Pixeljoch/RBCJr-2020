#include <Arduino.h>
#include <RobocupLib.h>

TMotor::TMotor(int pin1, int pin2, int pin3) {
    in1 = pin1;
    in2 = pin2;
    pwm = pin3; 

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(pwm, OUTPUT);


}

void TMotor::move(int setPWM, double acc, int motorDelay){
    if(setPWM >= -255 && setPWM <= -1) {
        if(lastSpeed > 0) {
            cruise(lastSpeed, 0, acc, motorDelay);
        }
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        cruise(lastSpeed, setPWM, acc, motorDelay);
    }
    if(setPWM <= 255 && setPWM >= 1) {
        if(lastSpeed < 0) {
            cruise(lastSpeed, 0, acc, motorDelay);
        }
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        cruise(lastSpeed, setPWM, acc, motorDelay);
    }
    
}

void TMotor::cruise(int speedCurrent, int speedFinal, double acc, int motorDelay){
    int speed_dif = speedFinal - speedCurrent;

    if (speedCurrent > speedFinal) {
        for(int speed = speedCurrent; speed >= speedFinal; speed = speed + speed_dif * acc) {
            if (speed < -255){
                speed = -255;
            }
            analogWrite(pwm, abs(speed));
            delay(motorDelay);
        } 
    } else {
        for(int speed = speedCurrent; speed <= speedFinal; speed = speed + speed_dif * acc) {
            if (speed > 255){
                speed = 255;
            }
            analogWrite(pwm, abs(speed));
            delay(motorDelay);
        }
    }   
    lastSpeed = speedFinal;
}