#include <mpu6050.h> // The working library you found

// I2C address of the MPU-6050.
// 0x69 if AD0 pin is HIGH, 0x68 if AD0 pin is LOW or unconnected.
#define MPU_ADDRESS 0x68 

// A structure to hold all sensor data in one place
struct MPUData {
  float dpsGX, dpsGY, dpsGZ;       // Gyroscope values in Degrees per Second
  float gForceAX, gForceAY, gForceAZ; // Accelerometer values in G-Force
};

void setup() {
  Serial.begin(115200);
  wakeSensor(MPU_ADDRESS); // Wakes sensor from sleep mode using the library's function
  Serial.println("MPU-6050 Data Reader Initialized.");
}

void loop() {
  MPUData sensorData; // Create an instance of our data structure

  // Read sensor data and populate the structure
  getSensorReadings(sensorData);
  
  // Print the collected data in a formatted way
  printReadings(sensorData);

  delay(500); // Wait half a second before the next reading
}

/**
 * @brief Reads all raw data from the MPU-6050 and converts it.
 * @param &data A reference to the MPUData struct to be filled.
 */
void getSensorReadings(MPUData &data) {
  // Temporary variables for raw sensor values
  float rawGX, rawGY, rawGZ;
  float rawAX, rawAY, rawAZ;

  // Read raw data using the library's functions
  readGyroData(MPU_ADDRESS, rawGX, rawGY, rawGZ);
  readAccelData(MPU_ADDRESS, rawAX, rawAY, rawAZ);
  
  // Convert raw data to meaningful units and store in the struct
  rawGyroToDPS(rawGX, rawGY, rawGZ, data.dpsGX, data.dpsGY, data.dpsGZ);
  rawAccelToGForce(rawAX, rawAY, rawAZ, data.gForceAX, data.gForceAY, data.gForceAZ);
}

/**
 * @brief Prints the sensor data to the Serial Monitor in a clean format.
 * @param data The MPUData struct containing the values to print.
 */
void printReadings(const MPUData &data) {
  Serial.print("Gyro (dps): ");
  Serial.print("X= "); Serial.print(data.dpsGX);
  Serial.print("\t| Y= "); Serial.print(data.dpsGY);
  Serial.print("\t| Z= "); Serial.println(data.dpsGZ);

  Serial.print("Accel (G):  ");
  Serial.print("X= "); Serial.print(data.gForceAX);
  Serial.print("\t| Y= "); Serial.print(data.gForceAY);
  Serial.print("\t| Z= "); Serial.println(data.gForceAZ);
  Serial.println("-----------------------------------------------------");
}