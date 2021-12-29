// Trey 12/09/21

// From Arduino
#include <Arduino.h>
#include <WiFi.h>

// Network credentials
const char* ssid = "Trey-ATT";
const char* password = "okayokay";
IPAddress deviceIP; // IP Object

// AP Network credentials
const char* ap_ssid = "okay_ap_esp32";
const char* ap_password = "okayokay9";

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
