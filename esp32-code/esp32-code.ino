#include <WiFi.h>
#include <PubSubClient.h>
//#include "EC.h"


void ECsetup();
void ECloop();

const char* ssid = "Gamer";
const char* password = "MikOgMak!";

const char* mqtt_server = "192.168.0.96";  // HA IP
const char* mqtt_user = "mqtt";
const char* mqtt_pass = "mqtt";

WiFiClient espClient;
PubSubClient client(espClient);

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void connectMQTT() {
  while (!client.connected()) {
    client.connect("esp32_bme", mqtt_user, mqtt_pass);
    if (!client.connected()) {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  connectWiFi();
  client.setServer(mqtt_server, 1883);
  connectMQTT();
  ECsetup();
}

void loop() {
  ECloop();
  if (!client.connected()) connectMQTT();
  client.loop();

  float t = millis();

  char payload[100];
  snprintf(payload, sizeof(payload),
           "{\"millis\":%.2f}",
           t);

  client.publish("home/esp32/asdf", payload);

  delay(2000); // send every 2s
}
