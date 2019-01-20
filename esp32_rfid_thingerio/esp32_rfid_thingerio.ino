#include <SPI.h>
#include <MFRC522.h>
#include <WiFiClientSecure.h>
#include <ThingerESP32.h>

#define USERNAME "achildrenmile"
#define DEVICE_ID "rfid"
#define DEVICE_CREDENTIAL "123qweASD!"
#define SSID "Things"
#define SSID_PASSWORD "!!Lady0911!!"

const int RST_PIN = 22; // Reset pin
const int SS_PIN = 21; // Slave select pin
 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
 
void setup() {
  Serial.begin(9600); 
  while (!Serial); //wait for the serial port to answer
  SPI.begin(); 
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial(); //display card reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));

  thing.add_wifi(SSID, SSID_PASSWORD);

  // read the dht data
  thing["rfid"] >> [](pson& out){
    out["uuid"]=getID();
  };
}
unsigned long getID(){
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
    return -1;
  }
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}
 
void loop() {
  thing.handle();
//  // Look for new cards
//  if ( ! mfrc522.PICC_IsNewCardPresent()) 
//  {
//    return;
//  }
// 
//  // Select one of the cards
//  if ( ! mfrc522.PICC_ReadCardSerial()) {
//    return;
//  }
// 
//  // Dump debug info about the card; PICC_HaltA() is automatically called
//  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
