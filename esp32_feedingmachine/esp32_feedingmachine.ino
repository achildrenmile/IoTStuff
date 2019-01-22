#include <WiFiClientSecure.h>
#include <ThingerESP32.h>
#include <Stepper.h>

#define USERNAME "<username>"
#define DEVICE_ID "<device_id>"
#define DEVICE_CREDENTIAL "<device_credential>"
#define SSID "<ssid>"
#define SSID_PASSWORD "<password>"
#define DHTPIN 16 //ensure the correct data pin
 
const int stepsPerRevolution = 2050; // change this to fit the number of steps per revolution
const int buttonPIN=17;

// initialize the stepper library on pins 15,2,0,4
Stepper myStepper(stepsPerRevolution, 16,21,18,22); 
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

int stepCount = 0; // number of steps the motor has taken
 
void setup() {
 myStepper.setSpeed(14);
 pinMode(buttonPIN, INPUT_PULLUP);
 thing.add_wifi(SSID, SSID_PASSWORD);
 thing["dispense"] <<  [](pson& in){ bool disp=in; if(disp) dispense(); };
}
 
void dispense() {
// step one step:
vibrate(3);
myStepper.step(-500);
vibrate(3);
myStepper.step(1000);
}

void vibrate(int times)
{
  for(int i;i<times;i++) 
  {
    myStepper.step(-35);
    delay(10);
    myStepper.step(35);
    delay(10);
  }
}

void loop() {
    thing.handle();
    if(digitalRead(buttonPIN)==0) {
      dispense();
    }
}

