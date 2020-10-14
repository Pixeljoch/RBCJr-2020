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

void TMotor::move(int setPWM){
    if(setPWM >= -255 && setPWM <= -1) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, abs(setPWM));
    }
    if(setPWM <= 255 && setPWM >= 1) {
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwm, abs(setPWM));
    }
    
}

IR_SENSOR::IR_SENSOR(int pin){
    ir_pin = pin;
    
    pinMode(ir_pin, INPUT);
}

int IR_SENSOR::readSensor(){
    int value = analogRead(ir_pin);
	if(value > 100){
		value = 0;
	}
	// Serial.println(value);
	
    return value;
}
