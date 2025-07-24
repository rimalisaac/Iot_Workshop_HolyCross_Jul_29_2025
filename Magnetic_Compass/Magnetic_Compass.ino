#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(0x0D); // QMC5883L default address
  Wire.write(0x00); // Start register for data
  Wire.endTransmission();

  Wire.requestFrom(0x0D, 6); // Read 6 bytes

  if (Wire.available() == 6) {
    int16_t x = Wire.read() | (Wire.read() << 8);
    int16_t y = Wire.read() | (Wire.read() << 8);
    int16_t z = Wire.read() | (Wire.read() << 8);

    Serial.print("X: "); Serial.print(x);
    Serial.print(" Y: "); Serial.print(y);
    Serial.print(" Z: "); Serial.println(z);
  } else {
    Serial.println("Failed to read from QMC5883L");
  }

  delay(500);
}
