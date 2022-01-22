// Trey 12/09/21

// From Arduino
#include <Arduino.h>

// From ESPAsyncWebServer-esphome
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Index.html
#include <webPage.hpp>
#include <ledMatrix.hpp>

// HTML Server
AsyncWebServer webServer(80);
String colors[256];
int brightness = 10;

// Web page if request is not found
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

// AJAX Handling
void webServerAPI() {

  // Get Colors of ID from the Server - /getColors?id
  webServer.on("/api/v0/getColors", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // Print Request
    int paramsNum = request->params();
    Serial.print("Request:\t/api/v0/getColors?");
    for(int i = 0; i < paramsNum; i++) {
      AsyncWebParameter* p = request->getParam(i);
      Serial.print(p->name());
      if (p->value() != "") {
        Serial.print("=");
        Serial.print(p->value());
      }
      if (i == paramsNum-1) {
        Serial.print("\n");
      } else {
        Serial.print("&");
      }
    }

    // Handle Requests
    if (request->hasParam("matrix")) {
      String response = "{\"colors\":[";
      for (int i = 0; i < 256; i++) {
        response += colors[i];
        if (i != 255) {
          response += ",";
        }
        else {response += "]}";}
      }
      
      Serial.println("Response:\t" + response);
      request->send(200, "text/plain", response);
    }

  });

  // Get Text Content of ID from the Server - /api/v0/getColors?id
  webServer.on("/api/v0/sendColors", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // Save Param values to colors[] and send colors[] back to client
    String response = "{\"colors\":[";
    int numParam = request->params();
    for(int i = 0; i < numParam; i++) {
      AsyncWebParameter* p = request->getParam(i);
      String val = p->value();
      if (val != "") {
        // colors[i] = val;
        colors[i] = "\"" + val + "\"";
        response += colors[i];
        if (i != numParam-1) {
          response += ",";
        }
        else {response += "]}";}
      }
    }
    setMatrix(colors, brightness);
    request->send(200, "text/plain", response); // Send Response


    // Print Request & Response
    Serial.print("Request:\t/api/v0/sendColors?");
    for(int i = 0; i < numParam; i++) {
      AsyncWebParameter* p = request->getParam(i);
      Serial.print(p->name());
      if (p->value() != "") {
        Serial.print("=");
        Serial.print(p->value());
      }
      if (i == numParam-1) {
        Serial.print("\n");
      } else {
        Serial.print("&");
      }
    }
    Serial.println("Response:\t" + response);

  });

  // Get Text Content of ID from the Server - /api/v0/getBrightness?id
  webServer.on("/api/v0/getBrightness", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // Print Request
    int paramsNum = request->params();
    Serial.print("Request:\t/api/v0/getBrightness?");
    for(int i = 0; i < paramsNum; i++) {
      AsyncWebParameter* p = request->getParam(i);
      Serial.print(p->name());
      if (p->value() != "") {
        Serial.print("=");
        Serial.print(p->value());
      }
      if (i == paramsNum-1) {
        Serial.print("\n");
      } else {
        Serial.print("&");
      }
    }

    // Handle Requests
    if (request->hasParam("brightness")) {
      String response = String(brightness);
      Serial.println("Response:\t" + response);
      request->send(200, "text/plain", response);
    }

  });

  // Send Value of ID to the Server - /api/v0/sendBrightness?id=value
  webServer.on("/api/v0/sendBrightness", HTTP_GET, [] (AsyncWebServerRequest *request) {

    // Print Request
    int paramsNum = request->params();
    Serial.print("Request:\t/api/v0/sendBrightness?");
    for(int i = 0; i < paramsNum; i++) {
      AsyncWebParameter* p = request->getParam(i);
      Serial.print(p->name());
      if (p->value() != "") {
        Serial.print("=");
        Serial.print(p->value());
      }
      if (i == paramsNum-1) {
        Serial.print("\n");
      } else {
        Serial.print("&");
      }
    }

    // Handle Requests
    if (request->hasParam("brightness")) {
      String response = "OK";
      AsyncWebParameter* p = request->getParam(0);
      brightness = p->value().toInt();
      Serial.println("Response:\t" + response);
      request->send(200, "text/plain", response);
    }

  });

}

// Start Web Server / Handle requests
void startWebServer() {

  // Send Web Page
  webServer.on("/", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
    Serial.print("Web page loaded by: ");
    Serial.println(request->client()->remoteIP());
  });

  // Server API (What to do with http requests)
  webServerAPI();

  // Start Web Server
  webServer.onNotFound(notFound);
  webServer.begin();

}



// END