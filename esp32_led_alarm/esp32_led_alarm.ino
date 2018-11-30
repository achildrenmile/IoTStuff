#include <Adafruit_NeoPixel.h>

#define PIN   16 //21
#define LED_NUM 7
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
      Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);
 
const byte sensorPin = 17;
 
SemaphoreHandle_t syncSemaphore;
 
void IRAM_ATTR handleInterrupt() {
  xSemaphoreGiveFromISR(syncSemaphore, NULL);
}
 
void setup() {
 
  Serial.begin(115200);
  leds.begin();
  turnledsgreen();
  syncSemaphore = xSemaphoreCreateBinary();

  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, CHANGE);
}

void turnledsgreen() 
{
  changeledcolor(0,5,0);
}

void turnledsred() 
{
  changeledcolor(5,0,0);
}

void changeledcolor(float red, float green, float blue) 
{
  for(int pixel=0;pixel<7;pixel++)
        leds.setPixelColor(pixel,leds.Color(red, green, blue));
  leds.show();
}

void loop() {
 
    xSemaphoreTake(syncSemaphore, portMAX_DELAY);
 
    if(digitalRead(sensorPin)){
      Serial.println("Motion detected");
       turnledsred();
    }else{
 
      Serial.println("Motion stoped");
      turnledsgreen();
    }
 
}
