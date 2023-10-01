// Measures flow sensor's pulse
volatile int flow_frequency_of_A; 
volatile int flow_frequency_of_B;

// Calculates liters/hour (FA - Flow sensor A, FB - Flow sensor B)
float volume_of_FA = 0.0, l_minute_FA;  
float volume_of_FB = 0.0, l_minute_FB;  

unsigned int flowsensor_A = 2;
unsigned int flowsensor_B = 3;

unsigned long currentTime;
unsigned long cloopTime;

// This is the function or interruption
void flow() 
{
   flow_frequency++;
}

void setup()
{
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH);
   Serial.begin(9600);
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); 
   currentTime = millis();
   cloopTime = currentTime;
}

void loop()
{
   currentTime = millis();

   if (currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime

      if (flow_frequency != 0) {
         // Pulse frequency (Hz) = 5.5Q, Q is flow rate in L/min.
         l_minute = (flow_frequency / 5.5); 
         l_minute = l_minute / 60; 

         volume = volume + l_minute;

        // Resetting Counter
         flow_frequency = 0; 

         Serial.print(l_minute, DEC); 
         Serial.println(" L/Min");
      }
      else {
         Serial.println(" Flow Rate : 0 ");
      }

   // Check for a command from Python
    if (Serial.available() > 0) {
      String command = Serial.readStringUntil('\n');
      
      if (command == "READ_DATA\n") {
        // Send the flow frequency and volume to Python
        Serial.print("FLOW_DATA:");
        Serial.print(l_minute_A);
        Serial.print(",");
        Serial.print(volume_of_FA);
        Serial.print(",");
        Serial.print(l_minute_B);
        Serial.print(",");
        Serial.print(volume_of_FB);
        Serial.print("\n");
      }
   }
}
