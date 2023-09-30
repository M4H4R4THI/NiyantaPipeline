#include "flow_sensor.h"
#include <Arduino.h>

// Flow sensor factor (Q)
const float flow_rate_factor = 5.5;

// Declaring port for sensors
unsigned int flow_sensor_A_pin = 2;
unsigned int flow_sensor_B_pin = 3;

volatile int flow_frequency_A;
volatile int flow_frequency_B;

float volume_A = 0.0, l_minute_A;
unsigned long currentTime_A;
unsigned long cloopTime_A;

float volume_B = 0.0, l_minute_B;
unsigned long currentTime_B;
unsigned long cloopTime_B;

void flow_A() 
{
   flow_frequency_A++;
}

void flow_B() 
{
   flow_frequency_B++;
}

void setupFlowSensors(){
    pinMode(flow_sensor_A_pin, INPUT);
    digitalWrite(flow_sensor_A_pin, HIGH);

    pinMode(flow_sensor_B_pin, INPUT);
    digitalWrite(flow_sensor_B_pin, HIGH);

    attachInterrupt(digitalPinToInterrupt(flow_sensor_A_pin), flow_A, RISING); 
    attachInterrupt(digitalPinToInterrupt(flow_sensor_B_pin), flow_B, RISING); 

    currentTime_A = millis();
    cloopTime_A = currentTime_A;

    currentTime_B = millis();
    cloopTime_B = currentTime_B;
}

float readFlowSensorA(){
    currentTime_A = millis();

   if (currentTime_A >= (cloopTime_A + 1000))
   {
      cloopTime_A = currentTime_A; // Updates cloopTime

      if (flow_frequency_A != 0) {
         // Pulse frequency (Hz) = 5.5Q, Q is flow rate in L/min.
         l_minute_A = (flow_frequency_A / 5.5); 
         l_minute_A = l_minute_A / 60; 

         volume_A = volume_A + l_minute_A;

        // Resetting Counter
         flow_frequency_A = 0; 
      }
      else {
         l_minute_A = 0;
      }
   }
   return l_minute_A;
}

float readFlowSensorB(){
    currentTime_B = millis();

   if (currentTime_B >= (cloopTime_B + 1000))
   {
      cloopTime_B = currentTime_B; // Updates cloopTime

      if (flow_frequency_B != 0) {
         // Pulse frequency (Hz) = 5.5Q, Q is flow rate in L/min.
         l_minute_B = (flow_frequency_B / 5.5); 
         l_minute_B = l_minute_B / 60; 

         volume_B = volume_A + l_minute_B;

        // Resetting Counter
         flow_frequency_B = 0; 
      }
      else {
         l_minute_B = 0;
      }
   }
   return l_minute_B;
}
