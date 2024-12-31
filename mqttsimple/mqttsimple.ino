#include <WiFi.h>
#include <PubSubClient.h>

// Configuración de WiFi
const char* ssid = "Estudio";    
const char* password = "vilarinhoseijo";

// Configuración del broker MQTT
const char* broker_ip = "192.168.1.74"; // Cambia por la IP del ordenador
const int broker_port = 1883;           // Puerto de Mosquitto

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

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(broker_ip, broker_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publicar el número "4" cada 30 segundos
  client.publish("test/topic", "4");
  Serial.println("Mensaje publicado: 4");
  delay(30000); // Esperar 30 segundos
}
