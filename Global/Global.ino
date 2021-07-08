#include <SPI.h>
#include <MFRC522.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp32.h>
#include <WiFiClient.h>

#define sirine 25
#define buzzer 26
#define SS_PIN 21
#define RST_PIN 22
#define I2C_SDA 33
#define I2C_SCL 32
#define motocycleContact 5


float latitude , longitude;
String  lat_str , lng_str;
String idimam = "04 7E 74 9A EB 2E 80";
int contact = 0;
int wifi_ctr = 0;
int lcdColumns = 16;
int lcdRows = 2;


const char *ssid =  "Redmi 8";    
const char *pass =  "elektro16"; 
char auth[] = "LCvzg2cSHrs944ll1Gy1mGXSBkvpVDtd"; 

WidgetMap myMap(V0); 
WiFiClient client;
MFRC522 mfrc522(SS_PIN, RST_PIN);  
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);  


void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();                     
  lcd.backlight();
  pinMode(sirine, OUTPUT);
  pinMode(sirine, HIGH);
  pinMode(buzzer, OUTPUT);
  delay(10);
  Serial.begin(9600);   // Initiate a serial communication
  Serial.println("Connecting to ");
  lcd.setCursor(0,0);
  lcd.print("Connecting to...");
  lcd.setCursor(0,1);
  lcd.print(ssid);
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    delay(500);
    Serial.print("."); 
                
  }
  
  Serial.println("");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Connected to  ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  Serial.println("WiFi connected");
  
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  
  Blynk.begin(auth, ssid, pass);
  Blynk.virtualWrite(V0, "clr");   
  SPI.begin();      // Initiate  SPI bus
  pinMode(motocycleContact, OUTPUT);
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  start_lcd();
}

void loop() {

  if (WiFi.status() == WL_CONNECTED) {
    gps_update();
    motocycle_contact();
    Blynk.run();
    delay(1000);
  }

  if (WiFi.status() == WL_DISCONNECTED) {
    WiFi.begin(ssid, pass); 
    while (WiFi.status() != WL_CONNECTED) {
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);
      Serial.print(".");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Connecting to...");
      lcd.setCursor(0,1);
      lcd.print(ssid);
    }
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Connected to  ");
    lcd.setCursor(0, 1);
    lcd.print(ssid);
  }
}
