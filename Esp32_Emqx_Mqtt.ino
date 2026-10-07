#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

//=========================
// WiFi Credentials
//=========================
const char* ssid     = "";
const char* password = "";

//=========================
// EMQX Serverless
//=========================
const char* mqtt_server = "";   // Example: abc123.ala.us-east-1.emqxsl.com
const int   mqtt_port   = 8883;

const char* mqtt_user = "";
const char* mqtt_pass = "";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("] : ");

  for (int i = 0; i < length; i++)
    Serial.print((char)payload[i]);

  Serial.println();
}

void connectWiFi()
{
  Serial.print("Connecting WiFi");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Connecting MQTT...");

    String clientId = "ESP32-" + String((uint32_t)ESP.getEfuseMac(), HEX);

    if (client.connect(clientId.c_str(), mqtt_user, mqtt_pass))
    {
      Serial.println("Connected");

      client.subscribe("mecatredz/test");

      client.publish("mecatredz/test", "ESP32 Connected");
    }
    else
    {
      Serial.print("Failed, rc=");
      Serial.println(client.state());

      delay(3000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  connectWiFi();

  // Testing only
  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop()
{
  if (!client.connected())
    reconnect();

  client.loop();

  static unsigned long last = 0;

  if (millis() - last > 5000)
  {
    last = millis();

    String msg = "Hello EMQX " + String(millis());

    client.publish("mecatredz/test", msg.c_str());

    Serial.println(msg);
  }
}
