#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Configurações de Wifi
const char* ssid = "Zeni-net";
const char* password = "lofibatata";
// Configurações do MQTT Broker
const char* mqtt_server = "perspex.ddns.net";
const char* topic = "testeLucas";

WiFiClient espClient;
PubSubClient client(espClient);


// Configurações de Input / Output
// ------------------------------------------

// Porta que controlará algum instrumento
// O que será controlado é a saída do led
const int ativacaoPin = 2; 

// Porta por onde o sinal do sensor entrará
const int sensorPin = 21;

int leituraAnterior = LOW;
int leitura = LOW;


// Funções
// -------------------------------------------

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

void callback(char* topic, byte* message, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String messageTemp;

    for (int i = 0; i < length; i++) {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    // Feel free to add more if statements to control more GPIOs with MQTT

    // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
    // Changes the output state according to the message
    if (String(topic) == topic) {
        Serial.print("Changing output to ");
        if(messageTemp == "on"){
            Serial.println("on");
            digitalWrite(ativacaoPin, HIGH);
        }
        else if(messageTemp == "off"){
            Serial.println("off");
            digitalWrite(ativacaoPin, LOW);
        }
    }
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        //  if (client.connect("ESP8266Client")) {
        if (client.connect("mosquito-lima")) {
            Serial.println("connected");
            // Subscribe
            client.subscribe(topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}


void setup() {
    Serial.begin(115200);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    pinMode(ativacaoPin, OUTPUT);
    pinMode(sensorPin, INPUT);
}


int contador = 0;


void loop() {
    // Conexão com a internet
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Realizar a leitura
    leitura = digitalRead(sensorPin);

    // Print debug
    Serial.print("Leitura "); Serial.print(contador++); Serial.print(":"); Serial.println(leitura);

    // Detectar ativação no sinal
    if (leituraAnterior == LOW && leitura == HIGH) {
        client.publish(topic, "Ativou");

    // Detectar desativação no sinal
    } else if (leituraAnterior == HIGH && leitura == LOW) {
        client.publish(topic, "Desativou");
    }

    leituraAnterior = leitura;

    delay(100);
}
