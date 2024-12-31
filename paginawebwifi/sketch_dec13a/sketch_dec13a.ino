#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Estudio";     // Cambia por tu red Wi-Fi
const char* password = "vilarinhoseijo";

WebServer server(80);

void handleRoot() {
    server.send(200, "text/plain", "Hola desde ESP32-C3");
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando...");
    }

    Serial.println("Conectado");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    server.handleClient();
}
