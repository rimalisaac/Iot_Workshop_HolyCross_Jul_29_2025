#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

// Create an MPU-6050 sensor object
Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);

  // Explicitly start the I2C bus on the correct pins for your wiring
  // Format is Wire.begin(SDA_PIN, SCL_PIN)
  Wire.begin(D2, D1);

  // Initialize the MPU-6050 sensor
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Set the measurement range for the accelerometer and gyroscope
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  
  delay(100);
}

void loop() {
  // Create sensor event objects to store the readings
  sensors_event_t a, g, temp;
  
  // Get new sensor events with the latest readings
  mpu.getEvent(&a, &g, &temp);

  // --- Print Accelerometer Data ---
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(" m/s^2 | ");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(" m/s^2 | ");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  // --- Print Gyroscope Data ---
  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(" rad/s | ");
  Serial.print("Y: ");
  Serial.print(g.gyro.y);
  Serial.print(" rad/s | ");
  Serial.print("Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.println("------------------------------------");
  delay(500);
}