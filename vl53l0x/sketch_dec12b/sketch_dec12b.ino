#include <Adafruit_VL53L0X.h>
#include <Wire.h>

// Crear una instancia del sensor
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando VL53L0X...");

  // Intentar inicializar el sensor en un bucle
  while (!lox.begin()) {
    Serial.println("¡Error al inicializar el VL53L0X! Verifique la conexión.");
    delay(1000); // Esperar 1 segundo antes de intentar nuevamente
  }

  Serial.println("VL53L0X inicializado correctamente.");
}

void loop() {
  VL53L0X_RangingMeasurementData_t measure;

  // Leer la distancia
  lox.rangingTest(&measure, false);

  // Verificar si la medida es válida
  if (measure.RangeStatus != 4) {
    Serial.print("Distancia: ");
    Serial.print(measure.RangeMilliMeter);
    Serial.println(" mm");
  } else {
    Serial.println("Fuera de rango");
  }

  delay(1000); // Leer la distancia cada segundo
}
