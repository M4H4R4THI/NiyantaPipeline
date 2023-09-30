#include "gps_module.h"
#include <Arduino.h>

TinyGPSPlus gps_module;
SoftwareSerial GPS_SoftSerial(6, 5);


volatile float minutes, seconds;
volatile int degree, secs, mins;

unsigned long start;
double latitude_value, longitude_value, altitude_meter_value;
uint8_t hour_value, minute_value, second_value;
bool location_valid, altitude_valid, time_valid;

void setupGPS(){
    GPS_SoftSerial.begin(9600);
}

void DegreeMinuteSecond(double total_value)
{
  degree = (int)total_value;
  minutes = total_value - degree;
  seconds = 60 * minutes;
  minutes = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}
static void smartDelay(unsigned long millisecond){
  unsigned long start = millis();
  do {
    // While data is available on serial port - encoding the data read from GPS
    while (GPS_SoftSerial.available())
    gps_module.encode(GPS_SoftSerial.read());
  } while (millis() - start < millisecond);
}

void updateGPS(){
    smartDelay(1000);
    latitude_value = gps_module.location.lat();
    location_valid = gps_module.location.isValid();
    longitude_value = gps_module.location.lng();
    altitude_meter_value = gps_module.altitude.meters();
    altitude_valid = gps_module.altitude.isValid();
    hour_value = gps_module.time.hour();
    minute_value = gps_module.time.minute();
    second_value = gps_module.time.second(); 
    time_valid = gps_module.time.isValid();
    DegreeMinuteSecond(latitude_value);
}

double getLattitude(){
    if(!location_valid){
        return 0.0000;
    }
    return latitude_value;
}

double getLongitude(){
    if(!location_valid){
        return 0.0000;
    }
    return latitude_value;
}

double getAlttiude(){
    if (!altitude_valid){
        return 0.0000;
    }
    return altitude_meter_value;
}
