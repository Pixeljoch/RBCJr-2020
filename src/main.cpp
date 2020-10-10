/*
 Name:		main.cpp
 Author:	Sciencelab Team
 Stage:		Alpha
*/

#include <Arduino.h>
#include <RobocupLib.h>

TMotor m1 (3, 2, 4);
TMotor m2 (7, 6, 5);
TMotor m3 (9, 8, 10);

void setup() {
	Serial.begin(9600);
}

void robotDirection(int dir, int speed, double acc, int motorDelay){
	int sinm1, sinm2, sinm3;

	sinm1 = -(speed) * sin((dir + 180) / RAD_TO_DEG);
	if (sinm1 < 1 && sinm1 > -1){
		sinm1 = 1;
	}
	sinm2 = -(speed) * sin((dir + 60) / RAD_TO_DEG);
	if (sinm2 < 1 && sinm2 > -1){
		sinm2 = 1;
	}
	sinm3 = -(speed) * sin((dir - 60) / RAD_TO_DEG);
	if (sinm3 < 1 && sinm3 > -1){
		sinm3 = 1;
	}

	m1.move(sinm1, acc, motorDelay);
	m2.move(sinm2, acc, motorDelay);
	m3.move(sinm3, acc, motorDelay);
}

void loop() {
	robotDirection(0, 255, 0.15, 30);
	delay(1500);
	robotDirection(90, 255, 0.15, 30);
	delay(1500);
}