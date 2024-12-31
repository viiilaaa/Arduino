#include <WiFi.h>
#include <PubSubClient.h>

// Configuración de WiFi
const char* ssid = "Estudio";    
const char* password = "vilarinhoseijo";

// Configuración del broker MQTT
const char* broker_ip = "192.168.1.74"; // Cambia por la IP del ordenador
const int broker_port = 1883;           // Puerto de Mosquitto

// Pines del HC-SR04
#define TRIG_PIN 2
#define ECHO_PIN 4

WiFiClient espClient;
PubSubClient client(espClient);

// Función para conectar al WiFi
void setup_wifi() {
  Serial.print("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado a WiFi!");
}

// Función para reconectar al broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando al broker MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Error: ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// Función para medir la distancia con el HC-SR04
float medir_distancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // Distancia en cm
  return distance;
}

void setup() {
  Serial.begin(115200);

  // Configuración de pines del sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Conexión WiFi
  setup_wifi();
  client.setServer(broker_ip, broker_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Medir distancia y publicar en el tópico MQTT
  float distancia = medir_distancia();
  String mensaje = String(distancia, 2); // Convertir a string con 2 decimales
  client.publish("sensor/distancia", mensaje.c_str());
  
  Serial.print("Mensaje publicado: ");
  Serial.println(mensaje);
  
  delay(5000); // Esperar 30 segundos
}
