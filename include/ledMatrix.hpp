// From Arduino
#include <Arduino.h>

// From Adafruit
#include <Adafruit_NeoPixel.h>

// Constants
#define LED_X 16
#define LED_Y 16
#define LED_COUNT 256
#define LED_PIN 22

// Matrix Object
Adafruit_NeoPixel Matrix(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Matrix helper functions
int indexToMatrix(int i) {
  int x = i%LED_X;
  int y = i/LED_Y;
  if (y%2 == 0) {
    return (LED_X-x-1)+(y*LED_X);
  }
  else {
    return x+(y*LED_X);
  }
}
int gridSnake(int x, int y) {
  if (y%2 == 0) {
    return (LED_X-x-1)+(y*LED_X);
  }
  else {
    return x+(y*LED_X);
  }
}
int grid(int x, int y) {
  return x+(y*LED_X);
}
int indexX (int i) {
  return i%LED_X;
}
int indexY (int i) {
  return i/LED_Y;
}
void pattern1(int brightness) {
  for(int y=0; y<LED_Y; y++) {
    for(int x=0; x<LED_X; x++) {

      int i = gridSnake(x, y);

      uint16_t hue = grid(x, y)*256;
      uint8_t sat = 255;
      uint8_t val = brightness;

      Matrix.setPixelColor(i, Matrix.ColorHSV(hue, sat, val));
      Matrix.show();
      delay(100);

    }
  }
  for(int y=0; y<LED_Y; y++) {
    for(int x=0; x<LED_X; x++) {

      int i = gridSnake(x, y);

      Matrix.setPixelColor(i, Matrix.Color(0, 0, 0));
      Matrix.show();
      delay(10);

    }
  }
}
void pattern2(int brightness) {
  for(int v=0; v<LED_COUNT; v++) {
    for(int y=0; y<LED_Y; y++) {

      for(int x=0; x<LED_X; x++) {

        int i = gridSnake(x, y);

        uint16_t hue = grid(x+indexX(v)%16, y+indexY(v)%16)*256;
        uint8_t sat = 255;
        uint8_t val = brightness;

        Matrix.setPixelColor(i, Matrix.ColorHSV(hue, sat, val));

      }
    }

    Matrix.show();
    delay(10);
  }
}

// Start Matrix
void ledMatrixSetup() {
  Matrix.begin();
  Matrix.clear();
}

// Set LED Matrix
void setMatrix(String colors[], int brightness) {

  // Loop through matrix
  for (int i = 0; i < LED_COUNT; i++) {

    // String to RGB int
    String color = colors[i];
    color.remove(0,5);
    color.remove(color.length()-2, 2);
    int comma_1 = color.indexOf(",");
    int comma_2 = color.indexOf(",", comma_1 + 1);
    String rS = color.substring(0, comma_1);
    String gS = color.substring(comma_1 + 2, comma_2);
    String bS = color.substring(comma_2 + 2);
    int r = rS.toInt();
    int g = gS.toInt();
    int b = bS.toInt();

    // Set Pixel
    Serial.println(brightness);
    Matrix.setPixelColor(indexToMatrix(i), Matrix.Color(r, g, b));
    Matrix.setBrightness(brightness);

  }

  // Show Changes
  Matrix.show();

}