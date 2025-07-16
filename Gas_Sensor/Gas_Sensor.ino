#include "MQ135.h"

// Define the pin connected to the MQ-135's Analog Out (A0)
#define SENSOR_PIN A0

// Initialize the MQ135 library
MQ135 gasSensor = MQ135(SENSOR_PIN);

void setup() {
  Serial.begin(9600);
  Serial.println("MQ-135 PPM Measurement Mode");
  
  // The calibration code is now commented out because the RZero value
  // is permanently stored in the MQ135.h library file.
  /*
  Serial.println("Calibrating... Make sure the sensor is in clean air.");
  float rzero = gasSensor.getRZero();
  Serial.print("Your RZero is: ");
  Serial.println(rzero);
  Serial.println("-----------------------------------");
  */
}

void loop() {
  // Now, this function will work correctly using the hard-coded RZero value.
  float ppm = gasSensor.getCorrectedPPM(20.0, 65.0); // Assuming 20°C and 65% humidity

  Serial.print("CO2 ppm: ");
  Serial.println(ppm);

  delay(2000);
}