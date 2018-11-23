#include <WiFiClientSecure.h>
#include <ThingerESP32.h>
#include <DHTesp.h>

#define USERNAME "<username>"
#define DEVICE_ID "<device_id>"
#define DEVICE_CREDENTIAL "<device_credential>"
#define SSID "<ssid>"
#define SSID_PASSWORD "<password>"
#define DHTPIN 16 //ensure the correct data pin
#define DHTTYPE DHTesp::DHT11

DHTesp dht;

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup() {
  dht.setup(DHTPIN,DHTTYPE);

  thing.add_wifi(SSID, SSID_PASSWORD);

  // read the dht data
  thing["officeparams"] >> [](pson& out){
    out["celsius"]=dht.getTemperature();
    out["humidity"]=dht.getHumidity();
  };

}

void loop() {
  thing.handle();
}
