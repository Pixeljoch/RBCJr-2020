/*
 Name:		RobocupFootball_Final.ino
 Created:	10/15/2019 09:54:14
 Author:	Sciencelab Team
 Stage:		Alpha
*/

#include <Arduino.h>
#include <RobocupLibrary.h>


Motor motor;
IR_SENSOR ir_sensor;

void setup() {
    Serial.begin(9600);
    motor.init();   
	ir_sensor.init();

}

void loop() {
	int speedMotor = 255;
	int motorDelay = 1000;
	
    // motor.control(1, 1, 255);
	motor.direction(0, speedMotor);
	delay(motorDelay);
	motor.direction(0, 0);
	delay(10);
	motor.direction(90, speedMotor);
	delay(motorDelay);
	motor.direction(0, 0);
	delay(10);
	motor.direction(180, speedMotor);
	delay(motorDelay);
	motor.direction(0, 0);
	delay(10);
	motor.direction(-90, speedMotor);
	delay(motorDelay);
	motor.direction(0, 0);
	delay(10);
}
