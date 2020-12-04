/*
 Name:		main.cpp
 Author:	Sciencelab Team
 Stage:		Alpha
*/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#include <RobocupLib.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <PID_v1.h>

TMotor m1 (2, 3, 4);
TMotor m2 (6, 7, 5);
TMotor m3 (8, 9, 10);
int returnArray[2] = {};

int ir[12] = {A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14};


static double errorValue;

void setup(void) {
	Serial.begin(9600);
	for(int i = 0; i < 12; i++){
		pinMode(ir[i], INPUT);
	}
	// gyroInit();	
	// errorValue = calculateError(100);
	// Input_M1 = calculateDegree(errorValue, 50);
	// Input_M2 = calculateDegree(errorValue, 50);
	// Input_M3 = calculateDegree(errorValue, 50);

	// SetPoint_M1 = 0;
	// SetPoint_M2 = 0;
	// SetPoint_M3 = 0;

	// myPID_M1.SetMode(AUTOMATIC);
	// myPID_M2.SetMode(AUTOMATIC);
	// myPID_M3.SetMode(AUTOMATIC);
}

void robotDirection(int dir, int speed){
	int sinm1, sinm2, sinm3;

	sinm1 = (speed) * sin((dir + 180) / RAD_TO_DEG);
	if (sinm1 < 1 && sinm1 > -1){
		sinm1 = 1;
	}
	sinm2 = (speed) * sin((dir + 60) / RAD_TO_DEG);
	if (sinm2 < 1 && sinm2 > -1){
		sinm2 = 1;
	}
	sinm3 = (speed) * sin((dir - 60) / RAD_TO_DEG);
	if (sinm3 < 1 && sinm3 > -1){
		sinm3 = 1;
	}

	// Serial.print("Motor 1: ");
	// Serial.println(sinm1);
	// Serial.print("Motor 2: ");
	// Serial.println(sinm2);
	// Serial.print("Motor 3: ");
	// Serial.println(sinm3);
	// delay(300);
	
	
	m1.move(sinm1);
	m2.move(sinm2);
	m3.move(sinm3);

	
}


void irInput(int tsopAmount){
	int irTest[tsopAmount] = {
		analogRead(ir[0]),
		analogRead(ir[1]),
		analogRead(ir[2]),
		analogRead(ir[3]),
		analogRead(ir[4]),
		analogRead(ir[5]),
		analogRead(ir[6]),
		analogRead(ir[7]),
		analogRead(ir[8]),
		analogRead(ir[9]),
		analogRead(ir[10]),
		analogRead(ir[11])
	};
	int irTestMap[tsopAmount] = {};
	for (int i = 0; i < tsopAmount; i++){
		irTestMap[i] = map(irTest[i], 0, 1023, 1203, 0);
	}
	int strongestValue = 0;
	int strongestInput = 0;
	for(int i = 0; i < tsopAmount; i++){
		if(irTestMap[i] > strongestValue){
			strongestInput = i;
			strongestValue = irTestMap[i];
		}
	}
	returnArray[0] = strongestInput;
	returnArray[1] = strongestValue;

	// if(strongestValue < 450){
	// 	robotDirection(0, 0);
	// }else{
	// 	robotDirection((returnArray[0] * -30), 200);
	// }
}

void loop() {
	irInput(12);

	Serial.println(returnArray[0]);
	Serial.println(returnArray[1]);
	delay(60);
}
