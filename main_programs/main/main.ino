#include "flow_sensor.h"
#include "vibration_sensor.h"
#include "gps_module.h"
#include <ArduinoJson.h>

const int RedLED = 12;
const int YellowLED = 13;
const int Relay = 10;
unsigned int count = 0;
unsigned int count2 = 0;


void setup(){
    Serial.begin(9600);
    setupFlowSensors();
    setupVibrationSensors();
    setupGPS();

    pinMode(RedLED, OUTPUT);
    pinMode(YellowLED, OUTPUT);

    digitalWrite(RedLED, LOW);
    digitalWrite(YellowLED, LOW);
    digitalWrite(Relay, HIGH);
}

void loop(){    
    // Health checking
    unsigned long previous_time = millis();
    while (millis() < (previous_time + 10000)){
      if ((readFlowSensorA() > 0) and (readFlowSensorB() > 0)) {
        digitalWrite(YellowLED, HIGH);
        delay(500);
        digitalWrite(YellowLED, LOW);
        break;
      }
      else {
        digitalWrite(RedLED, HIGH);
        delay(500);
        digitalWrite(RedLED, LOW);
        digitalWrite(Relay, LOW);
      }
    }
    
    float flow_rate_A = readFlowSensorA();
    // StaticJsonDocument<64> flowRateA;
    // flowRateA["flow_rate_a"] = flow_rate_A;
    // char FlowAJsonStr[64];
    // serializeJson(flowRateA, FlowAJsonStr);

    float flow_rate_B = readFlowSensorB();
    // StaticJsonDocument<64> flowRateB;
    // flowRateB["flow_rate_b"] = flow_rate_B;
    // char FlowBJsonStr[64];
    // serializeJson(flowRateB, FlowBJsonStr);

    int vib_sens_A = readVibrationSensorA();
    // StaticJsonDocument<64> VibSensA;
    // VibSensA["vib_sens_a"] = vib_sens_A;
    // char VibAJsonStr[64];
    // serializeJson(VibSensA, VibAJsonStr);

    int vib_sens_B = readVibrationSensorB();
    // StaticJsonDocument<64> VibSensB;
    // VibSensB["vib_sens_b"] = vib_sens_B;
    // char VibBJsonStr[64];
    // serializeJson(VibSensB, VibBJsonStr);

    updateGPS();
    double latitude_val = getLattitude();
    double longitude_val = getLongitude();
    double altitude_val = getAlttiude();

    // StaticJsonDocument<64> GpsModule;
    // GpsModule["latitude"] = latitude_val;
    // GpsModule["longitude"] = longitude_val;
    // GpsModule["altitude"] = altitude_val;
    // char GPSJsonStr[64];
    // serializeJson(GpsModule, GPSJsonStr);

    // Send JSON strings over serial
    // Serial.print(FlowAJsonStr);
    // Serial.print(",");
    // Serial.println(FlowBJsonStr);
    // Serial.print(",");
    // Serial.print(VibAJsonStr);
    // Serial.print(",");
    // Serial.println(VibBJsonStr);
    // Serial.print(",");
    // Serial.println(GPSJsonStr);

    Serial.print("Flow rate A: ");
    Serial.println(flow_rate_A, DEC);
    // Serial.println("L/min");

    Serial.print("Flow rate B: ");
    Serial.println(flow_rate_B, DEC);
    // Serial.println("L/min");

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

    // Check for flow rate difference

    if (abs(flow_rate_A - flow_rate_B) > 15){
      digitalWrite(YellowLED, HIGH);
      delay(1000);
      digitalWrite(YellowLED, LOW);
      count2++;
    }

    // Check if the vibration value is high

    if (vib_sens_A > 550){
      digitalWrite(RedLED, HIGH);
      delay(1000);
      digitalWrite(RedLED, LOW);
      count++;
    }

    // If the event is repeating, Blink LED and turn of Pump

    if ( count >= 15 || count2 >= 15 ){
      digitalWrite(RedLED, HIGH);
      delay(1000);
      digitalWrite(YellowLED, HIGH);
      delay(1000);
      digitalWrite(RedLED, LOW);
      delay(1000);
      digitalWrite(YellowLED, LOW);
      delay(1000);
      digitalWrite(RedLED, HIGH);
      digitalWrite(Relay, LOW);
      delay(1000);
      digitalWrite(RedLED, LOW);
    }

    delay(1000);
}