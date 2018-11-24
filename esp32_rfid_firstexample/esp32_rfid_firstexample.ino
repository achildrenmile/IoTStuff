#include <SPI.h>
#include <MFRC522.h>

const int RST_PIN = 22; // Reset pin
const int SS_PIN = 21; // Slave select pin
 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
 
void setup() {
  Serial.begin(9600); 
  while (!Serial); //wait for the serial port to answer
  SPI.begin(); 
  mfrc522.PCD_Init();
  mfrc522.PCD_DumpVersionToSerial(); //display card reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
}
 
void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
 
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
