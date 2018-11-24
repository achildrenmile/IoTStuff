#include <Adafruit_NeoPixel.h>
 
#define PIN   16 //21
#define LED_NUM 7
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);
 
 
void setup() 
{
  leds.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  randomSeed(analogRead(A0));
}
 
 
void loop() 
{
  //you can make the colours 255 but that is bright
  int redRandom = random(250);
  int greenRandom = random(250);
  int blueRandom = random(250);
  int ledRandom = random(7);
  leds.setPixelColor(ledRandom, leds.Color(redRandom, greenRandom, blueRandom));
  leds.show();
  delay(250);
}
