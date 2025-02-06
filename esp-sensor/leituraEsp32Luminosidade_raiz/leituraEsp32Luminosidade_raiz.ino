#include <WiFi.h>

// Configurações de Wifi
const char* ssid = "Zeni-net";
const char* password = "lofibatata";


// Inputs
const int fotoresistor = 27;


// Configuração Wifi
WiFiClient espClient;

void setup_wifi() {
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}


void setup() {
    Serial.begin(9600);
    // setup_wifi();
    pinMode(fotoresistor, INPUT);
}

void loop() {
  int iluminacao = analogRead(fotoresistor);
  
  // Conversão para temperatura em Celsius (assumindo sensor TMP36)
  Serial.print("Iluminacao (RAW): ");
  Serial.println(iluminacao);
  if (iluminacao >= 2000) {
    Serial.println("Status: Lampada Ligada");
  } else {
    Serial.println("Status: Lampada Desligada");
  }
  Serial.println("====================================\n");

  delay(1000); 
}
