#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// This file is not present in the repo. Instead you will find 
// settings.h.example and a .gitignore that ignores settings.h.
// To configure. copy settings.h.example into settings.h and
// then make your edits there.
#include "settings.h"

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  pinMode(PIN_PWM_DAYLIGHT, OUTPUT);
  Serial.begin(115200);
  client.setServer(MQTT_ADDR, MQTT_PORT);
  client.setCallback(callback);
  analogWriteFreq(125);
  analogWrite(PIN_PWM_DAYLIGHT, 0);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("MidnightSun")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("Wifi connected.");
  } else {
    if(!client.connected()){
      if (client.connect("MidnightSun")){
        client.subscribe("midnightsun/brightness");
        client.subscribe("inTopic");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

  if (client.connected())
    client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {

  char buf[length];
  
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    buf[i] = (char)payload[i];
  }
  Serial.println();

  if(strcmp("midnightsun/brightness", topic) == 0) {
    //int level = atoi((char*)payload);
    char *ptr;
    long val = strtol(buf, &ptr, 10);

    int level = (int) val;
    Serial.print("read midnight sun brightness as ");
    Serial.println(level);
    analogWrite(PIN_PWM_DAYLIGHT, level);

  }

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
}
