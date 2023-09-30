#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Creating the object name using the class SoftwareSerial
SoftwareSerial GPS_SoftSerial(4, 3);
/* Rx pin = 4 & Tx pin = 3 with baud rate 9600*/

// Creating the object name gps_module using TinyGPSPlus
TinyGPSPlus gps_module;

volatile float minutes, seconds;
volatile int degree, secs, mins;

// Declaring factor for flow rate calculation
const float flow_rate_factor = 5.5;

// Declaring Variables for Flow Sensor Input
const int flow_sensor_A_pin = A5;
const int flow_sensor_B_pin = A4;

// Declaring Variables for Flow Rate
float flow_rate_A;
float flow_rate_B;

// Declaring Variables for Vibration Sensor Input
const int vibration_sensor_A_pin = A3;
const int vibration_sensor_B_pin = A2;

void setup(){
  // For serial communication -  defining baud rate as 9600
  Serial.begin(9600);

  // For Software Serial Communication - defining baud rate as 9600
  GPS_SoftSerial.begin(9600);

  //flow sensor
  pinMode(flow_sensor_A_pin, INPUT);
  digitalWrite(flow_sensor_A_pin, LOW); 

  pinMode(flow_sensor_B_pin, INPUT);
  digitalWrite(flow_sensor_B_pin, LOW);

  pinMode(vibration_sensor_A_pin, INPUT);

  pinMode(vibration_sensor_B_pin, INPUT);
}

void loop(){
  // Generating precise delay of 1 millisecond
  smartDelay(1000);
  unsigned long start;
  double latitude_value, longitude_value, altitude_meter_value;
  uint8_t hour_value, minute_value, second_value;
  bool location_valid, altitude_valid, time_valid;

  latitude_value = gps_module.location.lat(); // Getting latitude data from gps
  location_valid = gps_module.location.isValid(); // Checking whether the available data is valid or not

  longitude_value = gps_module.location.lng(); // Getting longitude data from gps
  
  altitude_meter_value = gps_module.altitude.meters(); // Getting altitude data in meters
  altitude_valid = gps_module.altitude.isValid(); // Checking whether the available data of altitude is valid or not

  hour_value = gps_module.time.hour(); // Getting value for hour
  minute_value = gps_module.time.minute(); // Getting value for minute
  second_value = gps_module.time.second(); // Getting value for second

      //SENSORs
    // Reading Analog Value from Flow Sensors
  int flow_sensor_A_value = analogRead(flow_sensor_A_pin);
  int flow_sensor_B_value = analogRead(flow_sensor_B_pin);

  // Calculation of flow rate for flow sensor A and B [Flow rate = Flow Factor * Q(sensor value)]
  float flow_rate_A = flow_rate_factor * flow_sensor_A_value;
  float flow_rate_B = flow_rate_factor * flow_sensor_B_value;

  // Sending the value of flow_rate_B to using SerialIO
  Serial.print("Flow Rate of Flow Sensor A: ");
  Serial.print(flow_rate_A);
  Serial.println("L/min");

  Serial.print("Flow Rate of Flow Sensor B: ");
  Serial.print(flow_rate_B);
  Serial.println
  ("L/min");

  // Reading Analog Value from Vibration Sensors
  int vibration_sensor_A_value = analogRead(vibration_sensor_A_pin);
  int vibration_sensor_B_value = analogRead(vibration_sensor_B_pin);

  Serial.print("Vibration Rate of Vibration Sensor A: ");
  Serial.println(vibration_sensor_A_value);

  Serial.print("Vibration Rate of Vibration Sensor B: ");
  Serial.println(vibration_sensor_B_value);

  // Declaring delay for 1 second between the readings of sensor values
  delay(1000);
  time_valid = gps_module.time.isValid(); // Checking whether the value for time data is valid or not

  if( !location_valid){
    Serial.print("Latitude Value: ");
    Serial.println("************");

    Serial.print("Longitude Value: ");
    Serial.println("***********");
  } else {
    DegreeMinuteSecond(latitude_value);
    Serial.print("Latitude in decimal value: ");
    Serial.println(latitude_value, 12);

    Serial.print("Latitude Value in Degrees Minutes Seconds : ");
    Serial.print(degree);
    Serial.print("\t");

    Serial.print(mins);
    Serial.print("\t");

    Serial.print(secs);
    DegreeMinuteSecond(longitude_value);

    // Converting the decimal value of degree in the form of minutes and seconds
    Serial.print("Value of Longitude in Decimal Degrees: ");
    Serial.println(longitude_value, 12);

    Serial.print("Value of Longtitude in Degrees Minutes Seconds: ");
    Serial.print(degree);
    Serial.print("\t");

    Serial.print(mins);
    Serial.print("\t");

    Serial.println(secs);


  
  }


  // Checking whether the value of altitude is valid or not
  if (!altitude_valid){
    Serial.print("Value of Altitude: ");
    Serial.println("**********");
  }
  else{
    Serial.print("Value of Altitude: ");
    Serial.println(altitude_meter_value, 12);
  }

  // Checking whether the value of time is valid of not
  if (!time_valid){
    Serial.print("Time : ");
    Serial.println("***********");
  }
  else 
  {
    char time_string_value[32];
    sprintf(time_string_value, "Time: %02d/%02d/%02d \n", hour_value, minute_value, second_value);
    Serial.print(time_string_value);
  }

}

static void smartDelay(unsigned long millisecond){
  unsigned long start = millis();
  do {
    // While data is available on serial port - encoding the data read from GPS
    while (GPS_SoftSerial.available())
    gps_module.encode(GPS_SoftSerial.read());
  } while (millis() - start < millisecond);
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







