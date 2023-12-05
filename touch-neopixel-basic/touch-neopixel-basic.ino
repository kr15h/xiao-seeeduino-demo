#include "Adafruit_FreeTouch.h"
#include <Adafruit_NeoPixel.h>
#define TOUCH_PIN A0
#define NPIX_PIN D10
#define NPIX_COUNT 1
#define NPIX_RGBW   ((3 << 6) | (1 << 4) | (0 << 2) | (2)) // Took some time to decypher this

Adafruit_FreeTouch touch = Adafruit_FreeTouch(TOUCH_PIN, OVERSAMPLE_4, RESISTOR_50K, FREQ_MODE_NONE);
Adafruit_NeoPixel pixels(NPIX_COUNT, NPIX_PIN, NPIX_RGBW + NEO_KHZ800);

// NeoPixel control
char channel = 'w';
bool btouch = false;
int r = 0;
int g = 0; 
int b = 0;
int w = 255;

void setup() {
  Serial.begin(115200);
  //while (!Serial);
  Serial.println("QTouch Test");

  pinMode(LED_BUILTIN, OUTPUT);

  if (!touch.begin()) {
    Serial.print("Failed to begin QTouch on pin ");
    Serial.println(TOUCH_PIN);
  }

  // Start NeoPixels
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();
}

void loop() {
  int result = touch.measure();
  Serial.println(result);

  if (result > 900 && !btouch) {
    btouch = true;
    
    r = 0;
    g = 0;
    b = 0;
    w = 0;

    if (channel == 'w') {
      channel = 'r';
      r = 255;
    } else if (channel == 'r') { 
      channel = 'g';
      g = 255;
    } else if (channel == 'g') {
      channel = 'b';
      b = 255;
    } else if (channel == 'b') {
      channel = 'w';
      w = 255;
    }
  } else if (result <= 900) {
    btouch = false;
  }
    
  for(int i = 0; i < NPIX_COUNT; i++){
    pixels.setPixelColor(i, pixels.Color(r,g,b,w)); // Moderately bright green color.
  }
  pixels.show();
  
  delay(40);
}
