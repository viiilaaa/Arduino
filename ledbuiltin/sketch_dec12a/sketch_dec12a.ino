void setup() {
  pinMode(8, OUTPUT); // Configurar el GPIO10 como salida
}

void loop() {
  digitalWrite(8, HIGH); // Encender el LED
  delay(200);            // Esperar 1 segundo
  digitalWrite(8, LOW);  // Apagar el LED
  delay(200);            // Esperar 1 segundo
}
