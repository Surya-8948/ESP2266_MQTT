#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

const char* ssid = "Vimal";
const char* password = "1234567890";

const char* mqtt_server = ".s1.eu.hivemq.cloud";
const int mqtt_port = 8883;

const char* mqtt_user = "*******************";
const char* mqtt_pass = "*******************";

WiFiClientSecure espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected");
  Serial.println(WiFi.localIP());

  // Test only
  espClient.setInsecure();

  client.setServer(mqtt_server, mqtt_port);

  Serial.println("Connecting MQTT...");

  if (client.connect("ESP8266-Test", mqtt_user, mqtt_pass)) {
    Serial.println(" MQTT Connected");
    client.publish("test/hello", "Hello from ESP8266");
  } else {
    Serial.print(" MQTT Failed, rc=");
    Serial.println(client.state());
  }
}

void loop() {
  client.loop();
}
