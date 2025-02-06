#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Configurações de Wifi
const char* ssid = "Zeni-net";
const char* password = "lofibatata";

// Configurações do MQTT Broker
const char* mqtt_server = "perspex.ddns.net";
const int port = 1883;
const char* topic = "lampada/lucas";

WiFiClient espClient;
PubSubClient client(espClient);

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
    // if (String(topic) == topic) {
    //     Serial.print("Changing output to ");
    //     if(messageTemp == "on"){
    //         Serial.println("on");
    //         digitalWrite(ativacaoPin, HIGH);
    //     }
    //     else if(messageTemp == "off"){
    //         Serial.println("off");
    //         digitalWrite(ativacaoPin, LOW);
    //     }
    // }
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
            // client.subscribe(topic);
        } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}



const int fotoresistor = 34;



void setup() {
    Serial.begin(9600);
    pinMode(fotoresistor, INPUT);
    // pinMode(ativacaoPin, OUTPUT);

    setup_wifi();
    client.setServer(mqtt_server, port);
    client.setCallback(callback);
}


int iluminacao_anterior = 0;

const int limite = 2000;

void loop() {
    // Conexão com a internet
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    // Realiza leitura
    int iluminacao = analogRead(fotoresistor);

    // Print Status
    Serial.print("Iluminacao (RAW): ");
    Serial.println(iluminacao);
    if (iluminacao >= limite) {
        Serial.println("Status: Lampada Ligada");
    } else {
        Serial.println("Status: Lampada Desligada");
    }
    Serial.println("====================================\n");


    // Detectar ativação no sinal
    if (iluminacao_anterior <= limite && iluminacao > limite) {
        client.publish(topic, "1");
    
    // Detectar desativação no sinal
    } else if (iluminacao_anterior > limite && iluminacao <= limite) {
        client.publish(topic, "0");
    }

    // Salvar iluminacao anterior
    iluminacao_anterior = iluminacao;
      
    delay(100); 
}

