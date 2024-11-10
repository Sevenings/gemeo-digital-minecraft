#include <ESP8266WiFi.h>  // Biblioteca para Wi-Fi do ESP8266

// Configurações da rede Wi-Fi
const char* ssid = "Zeni-net";         // Nome da rede Wi-Fi
const char* password = "lofibatata";    // Senha da rede Wi-Fi

void setup() {
  Serial.begin(115200);         // Inicializa a comunicação serial para monitoramento
  delay(10);

  Serial.println();
  Serial.println("Conectando ao Wi-Fi...");
  
  WiFi.begin(ssid, password);   // Conecta ao Wi-Fi usando o SSID e senha fornecidos
  
  // Aguarda a conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado ao Wi-Fi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());  // Exibe o IP obtido na rede
}

void loop() {
  // Coloque aqui o código que você quer executar após a conexão Wi-Fi
}
