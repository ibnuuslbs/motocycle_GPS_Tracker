#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <Wire.h>               // Only needed for Arduino 1.6.5 and earlier
//#include<SH1106.h> 
//#include <BlynkSimpleEsp32.h>
float latitude , longitude;
String  lat_str , lng_str;
//const char *ssid =  "Redmi 8";     // Enter your WiFi Name
//const char *pass =  "elektro16"; // Enter your WiFi Password
//char auth[] = "PT2gEU1Bw3MP1dxyGl3Si0wK_25b7SvS"; 
//WidgetMap myMap(V0); 
//SH1106 display(0x3c, 21, 22);
//WiFiClient client;
TinyGPSPlus gps;
HardwareSerial SerialGPS(1);
void setup()
{
  Serial.begin(9600);
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, pass);
//  while (WiFi.status() != WL_CONNECTED)
//  {
//    delay(500);
//    Serial.print(".");              // print ... till not connected
//  }
//  Serial.println("");
//  Serial.println("WiFi connected");
  //display.init();
  //display.flipScreenVertically();
  //display.setFont(ArialMT_Plain_10);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
//  Blynk.begin(auth, ssid, pass);
//  Blynk.virtualWrite(V0, "clr"); 
}
void loop() {
//  for (int i = 1; i<=10; i++) {
    while (SerialGPS.available() > 0) {
      if (gps.encode(SerialGPS.read()))
      {
        if (gps.location.isValid())
        {
          Serial.println();
//          Serial.println("Pengujian GPS ke-" + String(i));
          latitude = gps.location.lat();
          lat_str = String(latitude , 6);
          longitude = gps.location.lng();
          lng_str = String(longitude , 6);
          Serial.print("Latitude = ");
          Serial.println(lat_str);
          Serial.print("Longitude = ");
          Serial.println(lng_str);
          

//        Blynk.virtualWrite(V0, 1, latitude, longitude, "Lokasi Imam");
        //display.display();
      }
     delay(60000);
     Serial.println();  
    }
//    Serial.println();
//    delay(60000);
  }  
//  Blynk.run();
    
// }
}
