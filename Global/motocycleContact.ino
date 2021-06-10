void motocycle_contact() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "04 7E 74 9A EB 2E 80") {
    Serial.println("Authorized access");
    Serial.println();
    contact++;
  }
 
  else {
    Serial.println(" Access denied");
  }

  if (contact==1) {
    digitalWrite(motocycleContact, HIGH);
  }
  else {
    contact=0;
    digitalWrite(motocycleContact, LOW);
  }
  Serial.println(contact);
}
