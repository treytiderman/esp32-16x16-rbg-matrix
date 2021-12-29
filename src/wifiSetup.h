// Trey 12/09/21

// From Arduino
#include <Arduino.h>
#include <WiFi.h>

// Network credentials
const char* ssid = "----";
const char* password = "----";
IPAddress deviceIP; // IP Object

// AP Network credentials
const char* ap_ssid = "okayokayokay";
const char* ap_password = "okayokayokay";

// Connect to a WiFi network
void connectToWiFi() {

  Serial.print("\n\nConnecting to WiFi...");

  // Connect to Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    WiFi.setHostname("Trey-ESP32");
    Serial.print(".");
  }

  // Print IP Address
  deviceIP = WiFi.localIP();
  Serial.print("\nConnected to WiFi with IP: ");
  Serial.println(deviceIP);

}

// Create a WiFi network
void createWiFi() {

  Serial.print("\n\nCreating WiFi...");
  WiFi.mode(WIFI_AP_STA);
  WiFi.setHostname("Trey-ESP32");
  WiFi.softAPsetHostname("Trey-ESP32");
  WiFi.softAP(ap_ssid, ap_password);
  Serial.print("\nCreated WiFi with IP: ");
  deviceIP = WiFi.softAPIP();
  Serial.println(deviceIP);

}
