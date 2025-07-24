#include <Wire.h>
#include <U8g2lib.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// OLED via I2C using U8g2
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  Wire.begin(D2, D1);  // SDA, SCL
  u8g2.begin();
  dht.begin();
}

void loop() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  if (isnan(temp) || isnan(hum)) {
    u8g2.drawStr(0, 24, "DHT11 Read Fail");
  } else {
    char line1[20];
    char line2[20];
    sprintf(line1, "Temp: %.1f C", temp);
    sprintf(line2, "Humidity: %.1f %%", hum);
    u8g2.drawStr(0, 24, line1);
    u8g2.drawStr(0, 44, line2);
  }

  u8g2.sendBuffer();
  delay(2000);
}
