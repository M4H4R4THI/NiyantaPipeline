

// Declaring factor for flow rate calculation
const float flow_rate_factor = 5.5;

// Declaring Variables for Flow Sensor Input
const int flow_sensor_A_pin = A1;

// Declaring Variables for Flow Rate
float flow_rate_A;

// Setup Function
void setup(){
  Serial.begin(9600);
  pinMode(flow_sensor_A_pin, INPUT);
  digitalWrite(flow_sensor_A_pin, LOW); 
  
}

// Loop Function
void loop(){
  // Reading Analog Value from Flow Sensors
  int flow_sensor_A_value = analogRead(flow_sensor_A_pin);

  // Calculation of flow rate for flow sensor A and B [Flow rate = Flow Factor * Q(sensor value)]
  float flow_rate_A = flow_rate_factor * flow_sensor_A_value;

  // Sending the value of flow_rate_B to using SerialIO
  Serial.print("Flow Rate of Flow Sensor A: ");
  Serial.print(flow_rate_A);
  Serial.println("L/min");

  // Declaring delay for 1 second between the readings of sensor values
  delay(1000);

}


