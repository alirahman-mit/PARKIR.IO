#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN    21  
#define RST_PIN   22  

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200); // Kita andalkan komunikasi lewat kabel ini
  SPI.begin();
  mfrc522.PCD_Init(); 
  
  // Teks penanda untuk Python nanti
  Serial.println("SISTEM_RFID_READY");
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent()) return;
  if ( ! mfrc522.PICC_ReadCardSerial()) return;

  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uidString += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  uidString.toUpperCase();
  
  // Print UID ke Serial Port agar dibaca oleh Python di laptop
  Serial.print("RFID_KELUAR:");
  Serial.println(uidString);
  
  mfrc522.PICC_HaltA();
  delay(2000); 
}