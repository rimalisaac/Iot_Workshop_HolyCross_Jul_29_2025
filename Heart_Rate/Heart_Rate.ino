#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL

  if (!particleSensor.begin(Wire, I2C_SPEED_STANDARD)) {
    Serial.println("MAX30102 not found. Check connections.");
    while (1);
  }

  // Configure for heart rate and SpO2
  particleSensor.setup(); 
  particleSensor.setPulseAmplitudeRed(0x0A); 
  particleSensor.setPulseAmplitudeIR(0x0A); 
}

void loop() {
  long irValue = particleSensor.getIR();

  if (irValue < 3000) {
    Serial.println("No finger detected.");
  } else {
    Serial.print("IR: ");
    Serial.println(irValue);
  }

  delay(500);
}
