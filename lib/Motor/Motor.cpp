#include <Arduino.h>
#include <Core.h>
#include <Motor.h>

/**
 * Constructor
 * in1 = 1st input pin
 * in2 = 2nd input pin
 * pwm = speed pin
 * speeddiff = what should be added or subtracted to make the motor function properly 
 * (defaults to 0 if not specified)
 */

Motor::Motor(int in1, int in2, int pwm, float speeddiff) {
    Motor::in1 = in1;
    Motor::in2 = in2;
    Motor::pwm = pwm;
    Motor::speeddiff = speeddiff;
}
Motor::Motor(int in1, int in2, int pwm) {
    Motor::in1 = in1;
    Motor::in2 = in2;
    Motor::pwm = pwm;
    Motor::speeddiff = 0;
}

/**
 * Must be called in the setup() method.
 * Sets the correct pinMode for the pins used.
 */

void Motor::setup() {
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(pwm, OUTPUT);
    pinMode(enc1, OUTPUT);
    pinMode(enc2, OUTPUT);
}

// Just for testing purposes
void Motor::test() {
    debug("Encoder A: " + String(analogRead(enc1)));
    debug("Encoder B: " + String(analogRead(enc2)));
}

/**
 * Move method. Makes the motor spin at given speed (-255 - 255) 
 * applies a speed differential if set, otherwise 
 * 
*/

void Motor::move(float speed) {
    if(speed < -255 || speed > 255) {
        // normally I'd do an exception but arduino doesnt support that.
        return;
    }
    if(speed < 0) { 
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, abs(speed));
    } else {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwm, abs(speed + speeddiff));
    }   
}


/**
 * Default Motor movements.
 * 
 */

MotorControl::MotorControl(Motor m1, Motor m2, Motor m3) {
    MotorControl::m1 = m1;
    MotorControl::m2 = m2;
    MotorControl::m3 = m3;
}


/**
 * Simple functions for motor-movement 
 * Forward, Backward, Left-Turn, Right-Turn
 */


void MotorControl::forward(float time, float speed) {
    m2.move(speed);
    m3.move(speed*-1);
    delay(time);
    m2.move(0);
    m3.move(0);
}

void MotorControl::backward(float time, float speed) {
    m2.move(speed*-1);
    m3.move(speed);
    delay(time);
    m2.move(0);
    m3.move(0);
}

void MotorControl::right(float degrees) {
    
}

void MotorControl::left(float degrees) {

}