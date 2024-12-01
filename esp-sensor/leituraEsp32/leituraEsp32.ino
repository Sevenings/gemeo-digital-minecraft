#include <WiFi.h>  // Biblioteca para Wi-Fi do ESP8266
#include <ArduinoWebsockets.h>


// Websockets
using namespace websockets;

const char* websocket_server = "ws://192.168.236.250:8080";

WebsocketsClient client;


void setupWebSockets() {
  // Configurar o cliente WebSocket
  client.onMessage([](WebsocketsMessage message) {
    Serial.println("Mensagem recebida do servidor:");
    Serial.println(message.data());
  });

  client.onEvent([](WebsocketsEvent event, String data) {
    if (event == WebsocketsEvent::ConnectionOpened) {
      Serial.println("Conexão WebSocket aberta!");
    } else if (event == WebsocketsEvent::ConnectionClosed) {
      Serial.println("Conexão WebSocket fechada.");
    } else if (event == WebsocketsEvent::GotPing) {
      Serial.println("Ping recebido!");
    } else if (event == WebsocketsEvent::GotPong) {
      Serial.println("Pong recebido!");
    }
  });

  // Conectar ao servidor WebSocket
  if (client.connect(websocket_server)) {
    Serial.println("Conectado ao servidor WebSocket!");
  } else {
    Serial.println("Falha ao conectar ao servidor WebSocket.");
  }
}


// Leitura de sinal
#define pinSinal 21

// Conexão com Wifi
const char* ssid = "Zeni-net";         // Nome da rede Wi-Fi
const char* password = "lofibatata";    // Senha da rede Wi-Fi

void conectarWifi() {
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




void setup() {
    Serial.begin(9600);
    pinMode(pinSinal, INPUT);
    conectarWifi();
    setupWebSockets();
}

int sinal = 0;
void loop() {
    // Manter a conexão WebSocket
    client.poll();

    sinal = digitalRead(pinSinal);
    sinal = !sinal; // Entrada ativa nivel alto

    if (sinal == HIGH) {
        client.send("Ativado");
    } else {
        client.send("Desligado");
    }
    Serial.println("Mensagem enviada ao servidor.");
    Serial.println(sinal);
    
    delay(1000);
}
