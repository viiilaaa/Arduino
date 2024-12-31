#define TRIG_PIN 9  // Pin para Trig del HC-SR04
#define ECHO_PIN 6  // Pin para Echo del HC-SR04
#define LED_PIN 8

void setup() {
  Serial.begin(115200);     // Inicializar el monitor serie
  Serial.print("Coomenzamos ");
  pinMode(TRIG_PIN, OUTPUT); // Configurar Trig como salida
  pinMode(ECHO_PIN, INPUT);  // Configurar Echo como entrada
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
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

  // Mostrar la distancia en el monitor serie
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    digitalWrite(LED_PIN, HIGH); // Enciende el LED
  } else {
    digitalWrite(LED_PIN, LOW);  // Apaga el LED
  }

  delay(500); // Esperar medio segundo antes de la siguiente medición
}