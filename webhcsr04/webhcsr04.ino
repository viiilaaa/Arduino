#include <WiFi.h>
#include <WebServer.h>

// Configuración de red Wi-Fi
const char* ssid = "Estudio";     // Cambia por tu red Wi-Fi
const char* password = "vilarinhoseijo";

// Configuración del servidor web
WebServer server(80);

// Pines del HC-SR04
const int trigPin = 2;
const int echoPin = 4;

// Función para medir distancia
long medirDistancia() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Calcula el tiempo de respuesta del pulso
    long duration = pulseIn(echoPin, HIGH);
    // Calcula la distancia en centímetros
    long distancia = duration * 0.034 / 2;
    Serial.println(distancia);
    return distancia;
}

// Función para calcular la distancia promedio durante 10 segundos
float calcularPromedio() {
    long suma = 0;
    int conteo = 0;
    unsigned long tiempoInicio = millis();
    
    while (millis() - tiempoInicio < 10000) { // 10 segundos
        long distancia = medirDistancia();
        if (distancia > 0 && distancia < 400) { // Filtro para valores válidos
            suma += distancia;
            conteo++;
        }
        delay(100); // Pausa entre mediciones
    }

    if (conteo > 0) {
        return suma / (float)conteo;
    } else {
        return -1; // Retornar -1 si no se obtuvieron valores válidos
    }
}

// Manejar la raíz del servidor
void handleRoot() {
    float promedio = calcularPromedio();
    if (promedio != -1) {
        String mensaje = "Distancia promedio durante 10 segundos: " + String(promedio, 2) + " cm";
        server.send(200, "text/plain", mensaje);
    } else {
        server.send(200, "text/plain", "No se obtuvieron mediciones válidas.");
    }
}

void setup() {
    Serial.begin(115200);

    // Configuración del sensor HC-SR04
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);

    // Conectar al Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando...");
    }

    Serial.println("Conexión exitosa");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());

    // Configurar el servidor web
    server.on("/", handleRoot);
    server.begin();
}

void loop() {
    server.handleClient();
}
