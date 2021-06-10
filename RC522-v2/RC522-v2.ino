
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 21
#define RST_PIN 22
#define kontakMotor 2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int contact = 0;

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  pinMode(kontakMotor, OUTPUT);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
void loop() 
{
  
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "04 7E 74 9A EB 2E 80") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    contact++;
//    digitalWrite(kontakMotor, HIGH);
//    delay(3000);
  }
 
 else   {
    Serial.println(" Access denied");
//    digitalWrite(kontakMotor, LOW);
//    delay(3000);
  }

  if (contact==1) {
    digitalWrite(kontakMotor, HIGH);
  }
  else {
    contact=0;
    digitalWrite(kontakMotor, LOW);
  }
  Serial.println(contact);
  delay(3000);
}   
