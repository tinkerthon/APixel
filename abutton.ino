#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FS.h>

#define PIN_LED     5
#define PIN_ENABLE  4

const char *ssid = "AButton";

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(PIN_ENABLE, OUTPUT);
  
  initWiFi();
}

void loop() {
  server.handleClient();
  delay(50);
}

void initWiFi() {
  Serial.println();
  Serial.println();
  Serial.println("Startup");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);
  WiFi.begin(ssid); // not sure if need but works
  Serial.print("Access point started with name ");
  Serial.println(ssid);

  server.on("/", handleRoot);
  server.on("/index.html", handleRoot);
  server.begin();

  SPIFFS.begin();

}

void handleRoot() {
  Serial.println("Sending handleConfig");

  File dataFile = SPIFFS.open("/index.tpl", "r");
  server.streamFile(dataFile, "text/html");
  dataFile.close();
}

