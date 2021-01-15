#include <Arduino.h>
#include <Core.h>

void setupCore() {
    Serial.begin(9600);
}

void debug(String msg) {
    Serial.println("Debug >>> " + msg);
}
