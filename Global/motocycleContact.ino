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
  if (content.substring(1) == idimam) {
    Serial.println("Access allowed");
    Serial.println();
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);    
    digitalWrite(buzzer, LOW);
    delay(100);    
    contact++;
  }
 
  else if ((content.substring(1) = !idimam) && (contact==0)) {
    Serial.println(" Access denied");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Access Denied! ");
    lcd.setCursor(0, 1);
    lcd.print("   Unknown ID   ");
    delay(5000);
  }

  if (contact==1) {
    lcd.clear();
    digitalWrite(motocycleContact, HIGH);    
    lcd.setCursor(0, 0);
    lcd.print(" Access allowed");
    lcd.setCursor(0, 1);
    lcd.print("Tap to turn off");
  }
  
  else {
    contact=0;
    start_lcd();
    digitalWrite(motocycleContact, LOW);
  }
  Serial.println(contact);
}
