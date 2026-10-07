# 📡 ESP8266 / ESP32 MQTT — IoT Publish & Subscribe Examples

A beginner-friendly repository for learning and implementing **MQTT communication using ESP8266 and ESP32**.

This repository contains practical examples of:

- ESP8266 with MQTT
- ESP32 with MQTT
- MQTT Publish
- MQTT Subscribe
- Publish + Subscribe together
- HiveMQ Cloud
- EMQX Cloud / EMQX Serverless
- Secure MQTT using TLS/SSL
- ESP32 device control through MQTT
- Real-time IoT communication

---
![Uploading image.png…]()


# 📌 What is MQTT?

**MQTT** stands for:

> **Message Queuing Telemetry Transport**

MQTT is a lightweight communication protocol specially designed for:

- Internet of Things (IoT)
- Embedded Systems
- Sensors
- ESP8266
- ESP32
- Raspberry Pi
- Industrial IoT
- Smart Home Automation
- GPS Tracking
- Remote Monitoring
- Robotics
- Cloud-connected devices

MQTT allows devices to send and receive data through a central server known as an **MQTT Broker**.

---

# 🧠 Why MQTT is Popular in IoT

Traditional HTTP communication generally works like:

```text
Device
   |
   | HTTP Request
   v
Server
   |
   | HTTP Response
   v
Device
```

The device must request the server whenever it needs information.

MQTT works differently.

```text
             MQTT Broker
            /           \
           /             \
          v               v
      ESP32            Dashboard
       |                   |
    Publish             Subscribe
```

Devices do not need to communicate directly with each other.

They communicate through the **MQTT Broker**.

This makes MQTT:

- Lightweight
- Fast
- Efficient
- Scalable
- Suitable for low-power devices
- Suitable for unreliable networks
- Excellent for real-time IoT applications

---

# 🏗️ MQTT Architecture

MQTT mainly has four important parts:

```text
Publisher
     |
     |
     v
 MQTT Broker
     |
     |
     v
Subscriber
```

## 1. Publisher

A Publisher sends data to a topic.

Example:

```text
ESP32 Temperature Sensor
```

publishes:

```text
30.5
```

to:

```text
home/temperature
```

---

## 2. Subscriber

A Subscriber listens to a particular topic.

Example:

```text
Mobile App
Web Dashboard
Node-RED
Another ESP32
```

can subscribe to:

```text
home/temperature
```

Whenever a new message is published, subscribers receive it automatically.

---

## 3. Broker

The MQTT Broker is the heart of MQTT communication.

Popular MQTT Brokers include:

- EMQX
- HiveMQ
- Mosquitto
- AWS IoT Core
- Azure IoT Hub
- ThingsBoard MQTT
- VerneMQ

The Broker receives messages from publishers and forwards them to subscribers.

Example:

```text
ESP32
   |
   | Publish = 30°C
   |
   v
EMQX Broker
   |
   +----------------+
   |                |
   v                v
Dashboard        Mobile App
```

---

# 📬 What is an MQTT Topic?

MQTT uses **Topics** instead of direct device addresses.

Example topic:

```text
home/temperature
```

Another example:

```text
home/light
```

or:

```text
factory/machine1/temperature
```

Topics can be organized hierarchically.

Example:

```text
mecatredz/
│
├── device01/
│   ├── temperature
│   ├── humidity
│   ├── gps
│   └── status
│
└── device02/
    ├── temperature
    ├── humidity
    └── status
```

---

# 📤 MQTT Publish

Publishing means:

> Sending a message to an MQTT topic.

Example:

```cpp
client.publish("home/temperature", "30");
```

Here:

```text
Topic   = home/temperature
Message = 30
```

---

# 📥 MQTT Subscribe

Subscribing means:

> Listening for messages arriving on a particular topic.

Example:

```cpp
client.subscribe("home/light");
```

Now if another device publishes:

```text
ON
```

to:

```text
home/light
```

the ESP32 can receive the command immediately.

---

# 🔄 Publish and Subscribe Together

One MQTT device can be both:

- Publisher
- Subscriber

at the same time.

Example:

```text
                 EMQX Broker
                /           \
               /             \
              v               v

ESP32 -------------------- Dashboard

Publish:
home/esp32/data
        --->

Subscribe:
home/esp32/cmd
        <---
```

ESP32 can send sensor data while also receiving commands.

---

# 💡 Practical Example

Suppose an ESP32 controls an LED.

ESP32 publishes:

```text
home/esp32/status
```

Message:

```text
ONLINE
```

Dashboard sends command:

```text
home/esp32/cmd
```

Message:

```text
ON
```

ESP32 receives the command and switches the LED ON.

Then Dashboard can send:

```text
OFF
```

and ESP32 switches the LED OFF.

---

# 🌎 MQTT Works Over the Internet

MQTT is not limited to a local Wi-Fi network.

Cloud MQTT Brokers allow devices anywhere in the world to communicate.

Example:

```text
ESP32
Lucknow
   |
   |
 Internet
   |
   v
EMQX Cloud
   |
   |
 Internet
   |
   v
Dashboard
Delhi
```

Both devices only need an Internet connection.

---

# ☁️ MQTT Cloud Brokers

This repository can be used with MQTT brokers such as:

## EMQX Cloud

Suitable for scalable IoT applications.

Features may include:

- MQTT Broker
- TLS encryption
- Authentication
- ACL
- WebSocket
- Device connections
- Monitoring
- Cloud deployment

---

## HiveMQ Cloud

Another popular cloud MQTT platform.

Useful for:

- Learning MQTT
- ESP32
- ESP8266
- IoT testing
- TLS MQTT communication

---

## Mosquitto

Mosquitto is an open-source MQTT Broker.

It can run on:

```text
Windows
Linux
Raspberry Pi
VPS
Docker
Local Computer
```

---

# 🔐 MQTT Ports

Common MQTT ports are:

| Port | Protocol | Security |
|---:|---|---|
| 1883 | MQTT | No TLS |
| 8883 | MQTT over TLS | Secure |
| 8083 / others | MQTT WebSocket | Depends on broker |
| 8084 / others | Secure WebSocket | TLS |

For production projects, TLS should normally be preferred.

---

# 🔒 MQTT over TLS

Normal MQTT:

```text
ESP32
   |
MQTT
Port 1883
   |
Broker
```

Secure MQTT:

```text
ESP32
   |
MQTT + TLS
Port 8883
   |
Broker
```

TLS encrypts communication between the device and MQTT Broker.

For ESP32, secure MQTT commonly uses:

```cpp
#include <WiFiClientSecure.h>
```

Example:

```cpp
WiFiClientSecure secureClient;
PubSubClient mqtt(secureClient);
```

For testing:

```cpp
secureClient.setInsecure();
```

⚠️ `setInsecure()` disables certificate verification and is convenient for testing, but proper CA certificate verification is recommended for production deployments.

---

# 📚 Required Arduino Libraries

For ESP32:

```cpp
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
```

For ESP8266:

```cpp
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
```

Install:

### PubSubClient

Arduino IDE:

```text
Sketch
→ Include Library
→ Manage Libraries
```

Search:

```text
PubSubClient
```

Install the library by **Nick O'Leary**.

---

# 📂 Repository Files

## `Esp8266_MQTT.ino`

MQTT example for ESP8266.

Useful for learning:

- Wi-Fi connection
- MQTT connection
- Publishing
- Subscribing
- ESP8266 IoT communication

---

## `Esp32_Mqtt_Publish&Subscribe.ino`

ESP32 MQTT example demonstrating both:

```text
Publish
+
Subscribe
```

Useful for learning bidirectional MQTT communication.

Example:

```text
ESP32 ---- Sensor Data ----> Broker

ESP32 <---- Commands -------- Broker
```

---

## `Esp32_Emqx_Mqtt.ino`

ESP32 example for **EMQX Cloud / Serverless MQTT**.

Uses:

```text
MQTT TLS
Port 8883
```

and:

```cpp
WiFiClientSecure
```

---

# ⚙️ MQTT Configuration

Before uploading the code, configure your Wi-Fi credentials.

```cpp
const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
```

Then configure MQTT Broker details.

```cpp
const char* MQTT_HOST = "YOUR_MQTT_HOST";
const int MQTT_PORT = 8883;

const char* MQTT_USER = "YOUR_USERNAME";
const char* MQTT_PASS = "YOUR_PASSWORD";
```

Example Broker hostname:

```text
xxxxxxxx.emqxsl.com
```

Do not write:

```text
https://xxxxxxxx.emqxsl.com
```

MQTT host should normally be only the hostname.

---

# 🔄 Basic MQTT Program Flow

Typical ESP32 MQTT program:

```text
START
  |
  v
Connect Wi-Fi
  |
  v
Connect MQTT Broker
  |
  v
Subscribe Topics
  |
  v
Run MQTT Loop
  |
  +---- Publish Sensor Data
  |
  +---- Receive Commands
  |
  +---- Reconnect if disconnected
```

---

# 🧩 MQTT Callback Function

Incoming subscribed messages are handled using a callback function.

Example:

```cpp
void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.print("Topic: ");
    Serial.println(topic);

    Serial.print("Message: ");

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }

    Serial.println();
}
```

If Dashboard sends:

```text
ON
```

ESP32 can check:

```cpp
if(message == "ON")
{
    digitalWrite(2, HIGH);
}
```

---

# 🔁 Why `client.loop()` is Important

This line is extremely important:

```cpp
client.loop();
```

It allows the MQTT client to:

- Receive subscribed messages
- Maintain MQTT connection
- Handle incoming packets
- Keep the connection alive

Therefore it should be called repeatedly inside:

```cpp
void loop()
```

---

# 🔌 MQTT Reconnection

IoT devices can lose:

- Wi-Fi
- Internet
- MQTT Broker connection

A reliable project should reconnect automatically.

Typical logic:

```cpp
if (!client.connected())
{
    reconnect();
}

client.loop();
```

---

# 🆔 MQTT Client ID

Every connected MQTT client should have a unique Client ID.

Example:

```text
ESP32_001
ESP32_002
ESP32_003
```

If two MQTT clients connect to the same broker with the same Client ID, one connection may replace/disconnect the other depending on broker behavior.

For many devices, generate unique IDs using:

- MAC Address
- Chip ID
- Device Serial Number

Example:

```text
MECATREDZ_ESP32_AA11BB22
```

---

# 📊 QoS — Quality of Service

MQTT supports different message delivery levels.

## QoS 0

```text
At most once
```

Fastest.

Message may occasionally be lost.

Good for frequently updated sensor data.

Example:

```text
Temperature
Humidity
GPS live location
```

---

## QoS 1

```text
At least once
```

Broker confirms delivery.

Message can possibly arrive more than once, so applications should tolerate duplicates.

Good for:

```text
Alerts
Device status
Important sensor events
```

---

## QoS 2

```text
Exactly once
```

Highest delivery guarantee.

More network overhead.

Useful where duplicate processing must be strongly avoided.

---

# 💾 Retained Messages

MQTT can store the latest message on a topic using the **retain flag**.

Example:

```text
device/001/status = ONLINE
```

If this message is retained, a new subscriber can immediately receive the latest stored value instead of waiting for the next publish.

Useful for:

- Relay state
- Device status
- Configuration
- Last sensor value

---

# ❤️ MQTT Last Will and Testament — LWT

MQTT supports a feature called:

```text
Last Will and Testament
```

Suppose ESP32 suddenly loses power.

The device cannot manually publish:

```text
OFFLINE
```

So while connecting, it can tell the Broker:

> If I disconnect unexpectedly, publish OFFLINE on my status topic.

Example:

```text
device/001/status
```

Broker publishes:

```text
OFFLINE
```

This is very useful for IoT device monitoring.

---

# 🃏 MQTT Wildcards

MQTT supports wildcard subscriptions.

## `+` Single Level Wildcard

Subscribe:

```text
home/+/temperature
```

Matches:

```text
home/room1/temperature
home/room2/temperature
home/kitchen/temperature
```

---

## `#` Multi-Level Wildcard

Subscribe:

```text
home/#
```

Matches:

```text
home/light
home/fan
home/kitchen/temp
home/room1/humidity
```

This is very useful for dashboards and monitoring applications.

---

# 🏭 Recommended Topic Structure

For professional IoT projects, use structured topic names.

Example:

```text
company/project/deviceId/data
company/project/deviceId/status
company/project/deviceId/command
company/project/deviceId/config
```

Example:

```text
mecatredz/smartbin/bin001/data
mecatredz/smartbin/bin001/status
mecatredz/smartbin/bin001/command
```

For GPS Tracker:

```text
mecatredz/gps/tracker001/location
mecatredz/gps/tracker001/status
mecatredz/gps/tracker001/command
```

---

# 📦 Sending JSON Through MQTT

Instead of sending different values separately:

```text
temperature = 30
humidity = 65
gas = 200
```

JSON can be used:

```json
{
  "device": "ESP32_01",
  "temperature": 30.5,
  "humidity": 65,
  "gas": 200
}
```

Publish to:

```text
mecatredz/device01/data
```

This approach is very useful for dashboards and cloud applications.

---

# ⚡ MQTT vs HTTP

| Feature | MQTT | HTTP |
|---|---|---|
| Architecture | Publish/Subscribe | Request/Response |
| IoT Friendly | Excellent | Good |
| Protocol Overhead | Low | Higher |
| Real-Time Control | Excellent | Moderate |
| Persistent Connection | Yes | Usually request-based |
| Sensor Data | Excellent | Good |
| Device Commands | Excellent | Possible |
| Low Bandwidth Networks | Excellent | Less efficient |
| Image/File Upload | Not ideal | Excellent |
| REST APIs | No | Excellent |

---

# 🚀 Why MQTT is Better for Many IoT Applications

Imagine 1000 ESP32 devices.

With HTTP, devices may continuously make requests:

```text
ESP32 → Server
ESP32 → Server
ESP32 → Server
```

With MQTT, devices maintain a lightweight connection:

```text
ESP32
ESP32
ESP32
   \ 
    \
   MQTT Broker
```

Broker handles message distribution.

Therefore MQTT is excellent for:

- Thousands of devices
- Telemetry
- Remote commands
- Low bandwidth
- Real-time communication
- Event-driven applications

---

# 📷 Should MQTT Be Used for ESP32-CAM Images?

Technically MQTT can transport binary data.

However, continuously sending large images directly through MQTT is generally not the most efficient architecture.

A better IoT architecture is:

```text
Dashboard
   |
   | MQTT
   | CAPTURE
   v
ESP32-CAM
   |
   | HTTPS
   v
Cloud Server / Storage
   |
   | Image URL
   v
MQTT Broker
   |
   v
Dashboard
```

Use:

```text
MQTT → Commands, status, alerts, sensor data

HTTPS → Images and larger files
```

This gives better scalability.

---

# 🛰️ Example GPS Tracker Architecture

```text
GPS Module
   |
   v
ESP32
   |
   | MQTT
   v
EMQX
   |
   +----------------+
   |                |
   v                v
Web Dashboard    Mobile App
```

Example topic:

```text
tracker/device001/location
```

Payload:

```json
{
  "lat": 26.8467,
  "lng": 80.9462,
  "speed": 35.5
}
```

---

# 🏠 Home Automation Example

```text
Mobile Dashboard
       |
       | MQTT
       v
    Broker
       |
       v
     ESP32
       |
       +---- Light
       +---- Fan
       +---- Relay
       +---- AC
```

Topics:

```text
home/light/set
home/fan/set
home/ac/set
```

Commands:

```text
ON
OFF
```

---

# 🗑️ Smart Bin Example

```text
Ultrasonic
Gas Sensor
Temperature
     |
     v
   ESP32
     |
     v
MQTT Broker
     |
     v
Dashboard
```

Topics:

```text
smartbin/bin01/fill
smartbin/bin01/gas
smartbin/bin01/status
smartbin/bin01/location
```

---

# 🌐 MQTT WebSocket

Normal ESP32 MQTT clients connect using MQTT TCP.

Web browsers cannot normally open raw MQTT TCP connections directly.

Therefore browser dashboards generally use:

```text
MQTT over WebSocket
```

Architecture:

```text
ESP32
   |
MQTT TCP
   |
   v
EMQX / HiveMQ
   |
MQTT WebSocket
   |
   v
HTML + JavaScript Dashboard
```

This allows the same MQTT Broker to communicate with:

- ESP32
- ESP8266
- Web Dashboard
- Mobile Application
- Node-RED
- Python
- Cloud services

---

# 🔐 MQTT Authentication

Production MQTT systems should use authentication.

Example:

```text
Username
Password
```

Broker checks:

```text
Is this device allowed to connect?
```

Advanced systems can also use:

- Certificates
- JWT
- API authentication
- External databases

---

# 🛡️ ACL — Access Control List

ACL controls what each device can Publish or Subscribe to.

Example:

Device:

```text
ESP32_001
```

Allowed:

```text
Publish:
device/001/data

Subscribe:
device/001/command
```

Not allowed:

```text
device/002/command
```

This improves IoT security.

---

# 📈 Scaling MQTT

One Broker can handle many:

```text
Devices
Topics
Publishers
Subscribers
Applications
```

Example:

```text
1000 ESP32 Devices
      |
      v
MQTT Broker
      |
      +---- Web Dashboard
      |
      +---- Mobile App
      |
      +---- Database
      |
      +---- Node-RED
      |
      +---- AI Application
```

The actual supported number of concurrent devices/messages depends on:

- Broker
- Cloud plan
- Hardware
- Network
- Message rate
- Message size
- QoS
- TLS overhead

---

# 🧪 Testing MQTT

MQTT can be tested using:

- MQTTX
- MQTT Explorer
- EMQX WebSocket Client
- HiveMQ Web Client
- Node-RED
- Python
- Another ESP32

Example test:

Subscribe:

```text
home/esp32/data
```

Then ESP32 publishes:

```text
Hello MQTT
```

The MQTT client should immediately receive the message.

---

# ❌ Common MQTT Problems

## MQTT State `-4`

Usually indicates:

```text
MQTT connection timeout
```

Check:

- Broker hostname
- Internet connection
- MQTT port
- Firewall
- TLS configuration

---

## Wrong Port

If using:

```text
8883
```

use TLS:

```cpp
WiFiClientSecure
```

If using:

```text
1883
```

normally use:

```cpp
WiFiClient
```

depending on broker configuration.

---

## Wrong Broker Host

Correct:

```text
xxxxx.emqxsl.com
```

Wrong:

```text
https://xxxxx.emqxsl.com
```

---

## Authentication Failure

Check:

```text
Username
Password
Authentication database
ACL permissions
```

---

## Device Connects and Immediately Disconnects

Check whether multiple devices are using the same:

```text
Client ID
```

Every active MQTT client should have a unique ID.

---

# 🔧 Typical ESP32 MQTT Structure

```cpp
void setup()
{
    connectWiFi();

    mqtt.setServer(MQTT_HOST, MQTT_PORT);

    mqtt.setCallback(callback);
}

void loop()
{
    if (!mqtt.connected())
    {
        connectMQTT();
    }

    mqtt.loop();

    // Publish sensor data here
}
```

---

# 🔥 Real-World Applications

MQTT is widely suitable for projects such as:

### Smart Home

```text
Light
Fan
AC
Door
Security
```

### Industrial IoT

```text
Machine Temperature
RPM
Vibration
Power
Fault Monitoring
```

### Smart Agriculture

```text
Soil Moisture
Water Pump
Temperature
Humidity
Weather
```

### Smart City

```text
Smart Bins
Street Lights
Air Quality
Parking
Traffic Monitoring
```

### GPS Tracking

```text
Vehicle Tracking
Asset Tracking
Geo-Fencing
SOS Tracker
```

### Robotics

```text
Robot Commands
Telemetry
Battery Status
Sensor Data
Remote Control
```

---

# 🧠 Recommended IoT Architecture

For a professional IoT system:

```text
                    ┌─────────────────┐
                    │   Web Dashboard │
                    └────────┬────────┘
                             │
                       WebSocket MQTT
                             │
                             v

ESP32 ───────────────> MQTT Broker <──────── Mobile App
   │                       │
   │                       │
Sensors                 Database
   │                       │
   │                       v
   │                    History
   │
   └──── HTTPS ───────> File/Image Server
```

Recommended usage:

```text
MQTT
├── Sensor Data
├── Commands
├── Alerts
├── GPS
├── Device Status
└── Configuration

HTTPS
├── Images
├── Audio
├── Firmware
└── Large Files
```

---

# 🚀 Future Improvements

This repository can be extended with:

- MQTT JSON communication
- Multiple ESP32 devices
- MQTT Dashboard
- Node-RED
- GPS Tracker
- ESP32-CAM integration
- EMQX Cloud
- HiveMQ Cloud
- Device authentication
- ACL
- QoS examples
- Retained messages
- Last Will & Testament
- OTA Firmware Update
- MQTT + Database
- MQTT + AI
- MQTT + WebSocket Dashboard

---

# 👨‍💻 Author

**Surya Mani Bajpai**

Electronics Engineer  
Embedded Systems • IoT • Robotics • PCB Design


Lucknow, Uttar Pradesh, India

GitHub:

`Surya-8948`

---

# ⭐ Support

If this repository helps you understand MQTT and IoT communication:

⭐ **Star this repository**

🍴 **Fork the repository**

🧪 Experiment with the examples

🚀 Build your own IoT projects

---

# 📜 License

This project is available under the **MIT License**.

---

## ❤️ Happy Learning

```text
ESP8266 / ESP32
       +
      MQTT
       +
     Cloud
       =
 Powerful IoT System 🚀
```

**Learn • Build • Experiment • Innovate**
