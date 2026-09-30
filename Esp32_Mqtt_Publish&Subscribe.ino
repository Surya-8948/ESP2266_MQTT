
#include <WiFi.h> // connect to wifi 
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* WIFI_SSID = "*********************";
const char* WIFI_PASS = "1234567890";

// HiveMQ Cloud Details
const char* MQTT_HOST = "*******************************";
const int   MQTT_PORT = 8883;
const char* MQTT_USER = "*********************************";
const char* MQTT_PASS = "*********************************";

// MQTT Topics
const char* PUB_TOPIC = "home/esp32/data";
const char* SUB_TOPIC = "home/esp32/cmd";

WiFiClientSecure secureClient;
PubSubClient mqtt(secureClient);

unsigned long lastPublish = 0;

void connectWiFi()
{
  Serial.print("Connecting WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

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

void mqttCallback(char* topic, byte* payload, unsigned int length)
{
  String message = "";

  for (int i = 0; i < length; i++)
    message += (char)payload[i];

  Serial.println("-------------------------");
  Serial.print("Topic : ");
  Serial.println(topic);

  Serial.print("Message : ");
  Serial.println(message);

  if (message == "ON")
  {
    digitalWrite(2, HIGH);
    Serial.println("LED ON");
  }

  else if (message == "OFF")
  {
    digitalWrite(2, LOW);
    Serial.println("LED OFF");
  }
}

void connectMQTT()
{
  while (!mqtt.connected())
  {
    Serial.print("Connecting MQTT...");

    if (mqtt.connect("ESP32_Client", MQTT_USER, MQTT_PASS))
    {
      Serial.println("Connected");

      mqtt.subscribe(SUB_TOPIC);

      Serial.print("Subscribed : ");
      Serial.println(SUB_TOPIC);
    }
    else
    {
      Serial.print("Failed, State = ");
      Serial.println(mqtt.state());

      delay(3000);
    }
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(2, OUTPUT);

  connectWiFi();

  // Testing ke liye
  secureClient.setInsecure();

  mqtt.setServer(MQTT_HOST, MQTT_PORT);
  mqtt.setCallback(mqttCallback);
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
    connectWiFi();

  if (!mqtt.connected())
    connectMQTT();

  mqtt.loop();

  if (millis() - lastPublish > 5000)
  {
    lastPublish = millis();

    String payload = "Hello From ESP32";

    mqtt.publish(PUB_TOPIC, payload.c_str());

    Serial.print("Published : ");
    Serial.println(payload);
  }
}
