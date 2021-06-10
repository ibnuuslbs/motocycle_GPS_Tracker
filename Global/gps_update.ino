void gps_update() {
  
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6);
        longitude = gps.location.lng();
        lng_str = String(longitude , 6);
        Serial.print("Latitude = ");
        Serial.println(lat_str);
        Serial.print("Longitude = ");
        Serial.println(lng_str);

        Blynk.virtualWrite(V0, 1, latitude, longitude, "Lokasi Imam");
      }
//     delay(1000);
     Serial.println();  
    }
  }
}
