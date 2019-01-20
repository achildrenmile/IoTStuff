#include <Adafruit_NeoPixel.h>
 
#define PIN   16
#define LED_NUM 7
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);


void setup() 
{
  leds.begin(); // This initializes the NeoPixel library.
  Serial.begin(9600);
  changeledcolor(30,30,30);
}


void changeledcolor(float red, float green, float blue) 
{
  for(int pixel=0;pixel<LED_NUM;pixel++)
        leds.setPixelColor(pixel,leds.Color(red, green, blue));
  leds.show();
}
 
void loop() 
{
  //you can make the colours 255 but that is bright
  changeledcolor(255,255,255);
  delay(2000);
}
