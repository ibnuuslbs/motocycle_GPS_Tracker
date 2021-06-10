#include <SPI.h>
#include <MFRC522.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>  
#include <BlynkSimpleEsp32.h>
#define SS_PIN 21
#define RST_PIN 22
#define motocycleContact 2

MFRC522 mfrc522(SS_PIN, RST_PIN);  

float latitude , longitude;
String  lat_str , lng_str;
int contact = 0;

const char *ssid =  "Redmi 8";    
const char *pass =  "elektro16"; 

unsigned long interval=3000; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.

String content= "";

char auth[] = "PT2gEU1Bw3MP1dxyGl3Si0wK_25b7SvS"; 
WidgetMap myMap(V0); 
//SH1106 display(0x3c, 21, 22);
WiFiClient client;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");              // print ... till not connected
  }
  Serial.println("");
  Serial.println("WiFi connected");

  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V0, "clr");   
  SPI.begin();      // Initiate  SPI bus
  pinMode(motocycleContact, OUTPUT);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop() {
  gps_update();
  motocycle_contact();
  Blynk.run();
  delay(1000);
}
