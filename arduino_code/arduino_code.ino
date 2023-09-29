
// Declaring factor for flow rate calculation
const float flow_rate_factor = 5.5;

// Declaring Variables for Flow Sensor Input
const int flow_sensor_A_pin = A1;
const int flow_sensor_B_pin = A3;

// Declaring Variables for Flow Rate
float flow_rate_A;
float flow_rate_B;

// Declaring Variables for Vibration Sensor Input
const int vibration_sensor_A_pin = A3;
const int vibration_sensor_B_pin = A5;

// Setup Function
void setup(){
  Serial.begin(9600);
  pinMode(flow_sensor_A_pin, INPUT);
  digitalWrite(flow_sensor_A_pin, LOW); 

  pinMode(flow_sensor_B_pin, INPUT);
  digitalWrite(flow_sensor_B_pin, LOW);

  pinMode(vibration_sensor_A_pin, INPUT);

  pinMode(vibration_sensor_B_pin, INPUT);
  
}

// Loop Function
void loop(){
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
  Serial.print("L/min");

  // Reading Analog Value from Vibration Sensors
  int vibration_sensor_A_value = analogRead(vibration_sensor_A_pin);
  int vibration_sensor_B_value = analogRead(vibration_sensor_B_pin);

  Serial.print("Vibration Rate of Vibration Sensor A: ");
  Serial.println(vibration_sensor_A_value);

  Serial.print("Vibration Rate of Vibration Sensor B: ");
  Serial.println(vibration_sensor_B_value);

  // Declaring delay for 1 second between the readings of sensor values
  delay(1000);

}


