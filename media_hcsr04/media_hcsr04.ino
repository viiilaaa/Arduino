#define TRIG_PIN 9  // Pin para Trig del HC-SR04
#define ECHO_PIN 6  // Pin para Echo del HC-SR04

void setup() {
  Serial.begin(115200);     // Inicializar el monitor serie
  Serial.println("Iniciando medición con HC-SR04...");
  pinMode(TRIG_PIN, OUTPUT); // Configurar Trig como salida
  pinMode(ECHO_PIN, INPUT);  // Configurar Echo como entrada
}

void loop() {
  const int maxIntentos = 20;
  const int limiteMedicion = 500; // Límite de distancia válida (cm)
  int medicionesValidas = 0;
  float sumaMediciones = 0.0;

  for (int intento = 1; intento <= maxIntentos; ++intento) {
    // Generar un pulso de 10 microsegundos en el Trig
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Leer el tiempo del pulso en el Echo
    long duration = pulseIn(ECHO_PIN, HIGH);

    // Calcular la distancia en centímetros
    float distance = (duration * 0.034) / 2;

    if (distance > 0 && distance <= limiteMedicion) {
      // Medición válida
      sumaMediciones += distance;
      medicionesValidas++;
      Serial.print("Intento ");
      Serial.print(intento);
      Serial.print(": Distancia válida = ");
      Serial.print(distance);
      Serial.println(" cm");
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
    float media = sumaMediciones / medicionesValidas;
    Serial.print("Media de las mediciones válidas: ");
    Serial.print(media);
    Serial.println(" cm");
  } else {
    Serial.println("No se obtuvieron mediciones válidas.");
  }

  delay(5000); // Esperar 5 segundos antes de reiniciar el bucle
}
