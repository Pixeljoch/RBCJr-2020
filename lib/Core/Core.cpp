#include <Arduino.h>
#include <Core.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

void setupCore() {
    Serial.begin(9600);
}

void debug(String msg) {
    Serial.println("Debug >>> " + msg);
}

