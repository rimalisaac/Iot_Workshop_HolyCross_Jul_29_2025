// Define the pins connected to the LEDs on the traffic light module
// Based on the connections provided: R -> D3, Y -> D2, G -> D1
#define RED_LED    D3  // GPIO0
#define YELLOW_LED D2  // GPIO4
#define GREEN_LED  D1  // GPIO5

void setup() {
  // Initialize each pin as a digital output
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop() {
  // --- Green Light Sequence ---
  digitalWrite(GREEN_LED, HIGH); // Turn Green LED ON
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  delay(5000); // Wait for 5 seconds

  // --- Yellow Light Sequence ---
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, HIGH); // Turn Yellow LED ON
  digitalWrite(RED_LED, LOW);
  delay(2000); // Wait for 2 seconds

  // --- Red Light Sequence ---
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, HIGH); // Turn Red LED ON
  delay(5000); // Wait for 5 seconds
}