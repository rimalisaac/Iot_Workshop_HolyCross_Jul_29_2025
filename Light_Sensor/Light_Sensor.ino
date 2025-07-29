// Define the analog pin connected to the LDR sensor module's output
#define LDR_PIN A0

void setup() {
  // Initialize Serial Communication at 9600 bits per second (baud rate)
  // This is for sending data from the NodeMCU to your computer's Serial Monitor
  Serial.begin(9600);
  
  Serial.println("LDR Light Sensor");
  Serial.println("--------------------------------");
}

void loop() {
  // Read the analog voltage value from the LDR pin (A0)
  // The value will be between 0 (0V) and 1023 (3.3V)
  int ldrValue = analogRead(LDR_PIN);

  // Print the value to the Serial Monitor
  Serial.print("Ambient Light Level: ");
  Serial.println(ldrValue);

  // Wait for half a second before taking the next reading
  delay(500);
}
