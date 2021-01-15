/* Get tilt angles on X and Y, and rotation angle on Z
 * Angles are given in degrees
 * 
 * License: MIT
 */

#include <Arduino.h>
#include "Wire.h"
#include <Motor.h>
#include <SparkFunLSM9DS1.h>

LSM9DS1 IMU;
Motor m1 (2, 3, 4);
Motor m2 (6, 7, 5);
Motor m3 (8, 9, 10);
unsigned long timer = 0;

void setup() {
  setupCore();

  Wire.begin();
  if (IMU.begin() == false) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
  {
    Serial.println("Failed to communicate with LSM9DS1.");
    Serial.println("Double-check wiring.");
    Serial.println("Default settings in this sketch will " \
                   "work for an out of the box LSM9DS1 " \
                   "Breakout, but may need to be modified " \
                   "if the board jumpers are.");
    while (1);
  }
  IMU.calibrate(false);
}

void move(double degrees, int baseSpeed) {
    float pi = 57.29577951;
    float speedM1 = -(baseSpeed) * sin((degrees + 180) / pi);
    float speedM2 = -(baseSpeed) * sin((degrees - 60) / pi);
    float speedM3 = -(baseSpeed) * sin((degrees + 60) / pi);
    m1.move(speedM1);
    m2.move(speedM2);
    m3.move(speedM3);
    debug(String(speedM1));
    debug(String(speedM2));
    debug(String(speedM3));
}

void printGyro()
{
  // Now we can use the gx, gy, and gz variables as we please.
  // Either print them as raw ADC values, or calculated in DPS.
  Serial.print("G: ");
  // If you want to print calculated values, you can use the
  // calcGyro helper function to convert a raw ADC value to
  // DPS. Give the function the value that you want to convert.
  Serial.print(IMU.calcGyro(IMU.gx), 2);
  Serial.print(", ");
  Serial.print(IMU.calcGyro(IMU.gy), 2);
  Serial.print(", ");
  Serial.print(IMU.calcGyro(IMU.gz), 2);
  Serial.println(" deg/s");
}
 
void loop() {
    if ( IMU.gyroAvailable() )
  {
    // debug("Je/ vuile moer");
    // To read from the gyroscope,  first call the
    // readGyro() function. When it exits, it'll update the
    // gx, gy, and gz variables with the most current data.
    IMU.readGyro();

    delay(100);
    printGyro();
  }
}