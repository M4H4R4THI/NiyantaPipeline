#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include <TinyGPS++.h>
#include <SoftwareSerial.h>

void setupGPS();
void updateGPS();
double getLattitude();
double getLongitude();
double getAlttiude();

#endif