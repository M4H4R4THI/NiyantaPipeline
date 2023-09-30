#include "flow_sensor.h"
#include "vibration_sensor.h"
#include "gps_module.h"


void setup(){
    Serial.begin(9600);
    setupFlowSensors();
    setupVibrationSensors();
    setupGPS();
}

void loop(){
    float flow_rate_A = readFlowSensorA();
    float flow_rate_B = readFlowSensorB();
    int vib_sens_A = readVibrationSensorA();
    int vib_sens_B = readVibrationSensorB();

    updateGPS();
    double latitude_val = getLattitude();
    double longitude_val = getLongitude();
    double altitude_val = getAlttiude();

    Serial.print("Flow rate A: ");
    Serial.print(flow_rate_A, DEC);
    Serial.println("L/min");

    Serial.print("Flow rate B: ");
    Serial.print(flow_rate_B, DEC);
    Serial.println("L/min");

    Serial.print("Vibration sensor A: ");
    Serial.println(vib_sens_A);

    Serial.print("Vibration sensor B: ");
    Serial.println(vib_sens_B);

    Serial.print("Latitude value: ");
    Serial.println(latitude_val, 12);

    Serial.print("Longitude value: ");
    Serial.println(longitude_val, 12);

    Serial.print("Altitude value: ");
    Serial.println(altitude_val, 12);

    delay(1000);
}