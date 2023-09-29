volatile int flow_frequency; // It will measures flow sensor's pulse
float volume = 0.0, l_minute;  // Calculates liters/hour
unsigned int flowsensor = 2;
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
   }
}
