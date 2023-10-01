#include "vibration_sensor.h"
#include <Arduino.h>

const int vibration_sensor_A_pin = A3;
const int vibration_sensor_B_pin = A5;

void setupVibrationSensors(){
    pinMode(vibration_sensor_A_pin, INPUT);

    pinMode(vibration_sensor_B_pin, INPUT);
}

int readVibrationSensorA(){
    return analogRead(vibration_sensor_A_pin);
}

int readVibrationSensorB(){
    return analogRead(vibration_sensor_B_pin);
}
