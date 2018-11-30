const byte sensorPin = 17;
const byte buzzerPin = 18;
 
int freq = 2000;
int channel = 0;
int resolution = 8;
int dutyCycle = 128;
 
SemaphoreHandle_t syncSemaphore;
 
void IRAM_ATTR handleInterrupt() {
  xSemaphoreGiveFromISR(syncSemaphore, NULL);
}
 
void setup() {
 
  Serial.begin(115200);
 
  syncSemaphore = xSemaphoreCreateBinary();
 
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), handleInterrupt, CHANGE);
 
  ledcSetup(channel, freq, resolution);
  ledcAttachPin(buzzerPin, channel);
 
}
 
void loop() {
 
    xSemaphoreTake(syncSemaphore, portMAX_DELAY);
 
    if(digitalRead(sensorPin)){
 
      Serial.println("Motion detected");
      ledcWrite(channel, dutyCycle);
 
    }else{
 
      Serial.println("Motion stoped");
      ledcWrite(channel, 0);
 
    }
 
}
