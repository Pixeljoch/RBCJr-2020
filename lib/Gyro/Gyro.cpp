#include <Arduino.h>
#include <math.h>
#include <Core.h>
#include <Gyro.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;
sensors_event_t a, g, temp;


void gyroSetup() {
  Serial.println("Adafruit MPU6050 test!");
 
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
    mpu.setGyroRange(MPU6050_RANGE_250_DEG);
}


void getGyroShizzle() {
    mpu.getEvent(&a, &g, &temp);
    // debug("X " + String(g.gyro.x));
    //debug("Y " + String(g.gyro.y * 180 / PI));
    debug("Z " + String(g.gyro.y * 180 / PI));
}
