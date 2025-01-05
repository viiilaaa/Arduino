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
  const int maxIntentos = 20;
  const int limiteMedicion = 500; // Límite de distancia válida (mm)
  int medicionesValidas = 0;
  long sumaMediciones = 0;

  for (int intento = 1; intento <= maxIntentos; ++intento) {
    VL53L0X_RangingMeasurementData_t measure;

    // Leer la distancia
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4 && measure.RangeMilliMeter <= limiteMedicion) {
      // Medición válida
      sumaMediciones += measure.RangeMilliMeter;
      medicionesValidas++;
      Serial.print("Intento ");
      Serial.print(intento);
      Serial.print(": Distancia válida = ");
      Serial.print(measure.RangeMilliMeter);
      Serial.println(" mm");
    } else {
      // Medición inválida
      Serial.print("Intento ");
      Serial.print(intento);
      Serial.println(": Medición inválida o fuera de rango.");
    }

    delay(1000); // Esperar 1 segundo entre intentos
  }

  // Calcular y mostrar la media
  if (medicionesValidas > 0) {
    float media = (float)sumaMediciones / medicionesValidas;
    Serial.print("Media de las mediciones válidas: ");
    Serial.print(media);
    Serial.println(" mm");
  } else {
    Serial.println("No se obtuvieron mediciones válidas.");
  }

  delay(5000); // Esperar 5 segundos antes de reiniciar el bucle
}
