#include <Arduino.h>
#include <Wire.h>

// Укажите пины, которые написаны на вашей плате или использовались в коде
#define I2C_SDA         8
#define I2C_SCL         9

void setup() {
  Serial.begin(115200);
  // Ожидание инициализации Serial Monitor для чипов со встроенным USB
  while (!Serial && millis() < 4000); 
  
  Serial.println("\n=== ЗАПУСК I2C СКАНЕРА ===");
  
  // Принудительно запускаем шину на наших пинах
  Wire.begin(I2C_SDA, I2C_SCL);
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Сканирование шины...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Устройство найдено по адресу: 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Неизвестная ошибка по адресу: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  
  if (nDevices == 0) {
    Serial.println("Устройства I2C НЕ найдены. Проверьте пины!\n");
  } else {
    Serial.println("Сканирование завершено.\n");
  }

  delay(3000); // Повторяем каждые 3 секунды
}
