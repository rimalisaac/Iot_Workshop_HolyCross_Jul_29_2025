#include "MQ135.h"

// Define the pin connected to the MQ-135's Analog Out (A0)
#define SENSOR_PIN A0

// Initialize the MQ135 library
MQ135 gasSensor = MQ135(SENSOR_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("MQ-135 PPM Calculator Initializing...");
  Serial.println("Please wait while the sensor warms up.");
  delay(10000); // Allow significant time for sensor warmup

  // --- STEP 1: CALIBRATION ---
  // Run this part of the code once in a clean air environment to find your RZero value.
  // Then, comment it out and proceed to Step 2.
  Serial.println("Calibrating... Make sure the sensor is in clean air.");
  float rzero = gasSensor.getRZero();
  Serial.print("Your RZero is: ");
  Serial.println(rzero);
  Serial.println("-----------------------------------");
  // After you get your RZero, comment out the 3 lines above.

}

void loop() {
  // --- STEP 2: GETTING PPM READINGS ---
  // Make sure you have completed calibration and commented out the calibration code above.
  
  // Get the corrected PPM value
  // The library automatically compensates for temperature and humidity,
  // but you can provide them for higher accuracy: e.g., getCorrectedPPM(25.0, 50.0)
  float ppm = gasSensor.getCorrectedPPM(20.0, 65.0); // Assuming 20°C and 65% humidity

  Serial.print("CO2 ppm: ");
  Serial.println(ppm);

  delay(2000);
}