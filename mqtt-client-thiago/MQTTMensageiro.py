from flask import Flask, request, render_template
import paho.mqtt.client as mqtt

app = Flask(__name__)

# Configuração do MQTT
mqtt_broker = "perspex.ddns.net"  # Coloque o endereço do seu broker MQTT
mqtt_port = 1883

# Inicializando o cliente MQTT
client = mqtt.Client()

# Callbacks para verificar conexão
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("✅ Conectado ao broker MQTT com sucesso!")
    else:
        print(f"❌ Erro ao conectar ao broker. Código de erro: {rc}")

client.on_connect = on_connect

# Conectar ao broker MQTT ao iniciar o Flask
print("🔄 Tentando conectar ao broker MQTT...")
client.connect(mqtt_broker, mqtt_port, 60)
client.loop_start()  # Mantém a conexão ativa

@app.route("/", methods=["GET", "POST"])
def pagina():
    if request.method == "POST":
        topico = request.form["topico"]
        mensagem = request.form["mensagem"]

        try:
            print(f"📤 Publicando mensagem: '{mensagem}' para o tópico '{topico}'")
            result = client.publish(topico, mensagem)
            result.wait_for_publish()  # Aguarda confirmação da publicação

            if result.rc != mqtt.MQTT_ERR_SUCCESS:
                raise Exception("Erro ao publicar a mensagem")

            return render_template("PaginaMQTTClient.html", sucesso=True, mensagem=mensagem, topico=topico)

        except Exception as e:
            print(f"❌ Erro ao enviar mensagem MQTT: {e}")
            return render_template("PaginaMQTTClient.html", sucesso=False, erro=str(e))
        
    return render_template("PaginaMQTTClient.html", sucesso=False)

if __name__ == "__main__":
    try:
        app.run(debug=True)
    finally:
        client.loop_stop()  # Para o loop MQTT ao encerrar a aplicação
        client.disconnect()  # Fecha a conexão com o broker

 