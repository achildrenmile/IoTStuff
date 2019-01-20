#include <Adafruit_NeoPixel.h>
#include <WiFiClientSecure.h>
#include <ThingerESP32.h>
#include <DHTesp.h>

#define USERNAME "achildrenmile"
#define DEVICE_ID "alarm"
#define DEVICE_CREDENTIAL "vmDfg3VJklSc"
#define SSID "Things"
#define SSID_PASSWORD "!!Lady0911!!"
#define PIN   16 //21
#define LED_NUM 7
const byte buzzerPin = 18;
 
int freq = 2000;
int channel = 0;
int resolution = 8;
int dutyCycle = 128;
 
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
      Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
 
const byte sensorPin = 17;
 
SemaphoreHandle_t syncSemaphore;
 
void IRAM_ATTR handleInterrupt() {
  xSemaphoreGiveFromISR(syncSemaphore, NULL);
}
int count=0; 
void setup() {
 
  Serial.begin(115200);
  leds.begin();
  turnledsgreen();
  //syncSemaphore = xSemaphoreCreateBinary();

  pinMode(sensorPin, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, CHANGE);
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(buzzerPin, channel);

  thing.add_wifi(SSID, SSID_PASSWORD);
  // read the dht data
  thing["alarm"] >> [](pson& out){
    out["countsincestart"]=count;
  };
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
  
    thing.handle();

    delay(2);
    if(digitalRead(sensorPin)){
      Serial.println("Motion detected");
       turnledsred();
       ledcWrite(channel, dutyCycle);   
      count++;
    }else{
 
      Serial.println("Motion stoped");
      turnledsgreen();
      ledcWrite(channel, 0);
 
    }
 
}
