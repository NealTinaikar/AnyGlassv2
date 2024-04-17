void wifiConnect(){
  isWIFIConnected = false;
//  char* ssid = "SETUP-E276";
//  char* password = "filter0318brick";
  Serial.print("Try to connect to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wi-Fi Connected!");
  isWIFIConnected = true;
  client.setInsecure();
}

bool getTimeFromNTP() {
  Serial.println("Getting time from NTP server...");
  
//  // Initialize UDP for NTP
  WiFiUDP udp;
  if (!udp.begin(localPort)) {
    Serial.println("Failed to initialize UDP");
    return false;
  }
  
  // Send an NTP request to the time server
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  packetBuffer[0] = 0b11100011;   // NTP request header
  packetBuffer[1] = 0;             // Unused
  packetBuffer[2] = 6;             // Start at transmit timestamp
  packetBuffer[3] = 0xEC;          // NTP version number
  if (!udp.beginPacket(ntpServer, 123)) { // NTP requests are to port 123
    Serial.println("Failed to begin packet");
    udp.stop();
    return false;
  }
  if (!udp.write(packetBuffer, NTP_PACKET_SIZE)) {
    Serial.println("Failed to write to packet");
    udp.stop();
    return false;
  }
  if (!udp.endPacket()) {
    Serial.println("Failed to end packet");
    udp.stop();
    return false;
  }
  
  // Wait for response
  delay(1000);
  int packetSize = udp.parsePacket();
  if (packetSize == 0) {
    Serial.println("No response from server");
    udp.stop();
    return false;
  }
  
  // Read response into buffer
  udp.read(packetBuffer, NTP_PACKET_SIZE);
  
  // Close the UDP connection
  udp.stop();

  // Extract the timestamp
  unsigned long secsSince1900 = (unsigned long)packetBuffer[40] << 24 | (unsigned long)packetBuffer[41] << 16 | (unsigned long)packetBuffer[42] << 8 | (unsigned long)packetBuffer[43];
  setTime(secsSince1900 - 2208988800UL); // Convert NTP timestamp to Unix timestamp

  return true;
}

void getTimeStrings(String &dateString, String &timeString) {
  // Construct date string
  dateString = String(year()) + "-" + (month() < 10 ? "0" : "") + String(month()) + "-" + (day() < 10 ? "0" : "") + String(day());
  
  // Construct time string
  timeString = (hour() < 10 ? "0" : "") + String(hour()) + ":" + (minute() < 10 ? "0" : "") + String(minute()) + ":" + (second() < 10 ? "0" : "") + String(second());
}
