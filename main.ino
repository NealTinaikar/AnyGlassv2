// libraries
#include <I2S.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <ArduinoJson.h>
#include <ChatGPT.hpp>
#include <WiFiUdp.h>
#include <TimeLib.h>
#include <U8g2lib.h>  // Include the U8g2 library
#include <Trill.h>    // Include the Trill library

// chatgpt variables
String chatgpt_Q = "";
String chatgpt_R = "";
WiFiClientSecure client;
ChatGPT<WiFiClientSecure> chat_gpt(&client, "v1", "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");

// voice recording variables
#define SAMPLE_RATE 16000U
#define SAMPLE_BITS 16
#define WAV_HEADER_SIZE 44
#define VOLUME_GAIN 2
#define RECORD_TIME 10 // max 240
uint32_t record_size = (SAMPLE_RATE * SAMPLE_BITS / 8) * RECORD_TIME;
File file;
const char filename[] = "/recording.wav";

// wifi variables
bool isWIFIConnected;
const char* ssid = "SETUP-E276";
const char* password = "filter0318brick";
const char *ntpServer = "pool.ntp.org"; // NTP server to use
WiFiUDP udp;
unsigned int localPort = 2390;
const int NTP_PACKET_SIZE = 48;
byte packetBuffer[NTP_PACKET_SIZE];  
String curr_date = "";
String curr_time = "";

// trill bar variables
Trill bar;

// oled display variables
U8G2_SSD1306_64X32_1F_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);
  while (!Serial) ;
  
  I2S.setAllPins(-1, 42, 41, -1, -1);
  if (!I2S.begin(PDM_MONO_MODE, SAMPLE_RATE, SAMPLE_BITS)) {
    Serial.println("Failed to initialize I2S!");
    while (1) ;
  }
  if(!SD.begin(21)){
        Serial.println("Card Mount Failed");
        return;
  }
  
  wifiConnect();
  
  u8g2.begin();

  int ret = bar.setup(Trill::TRILL_BAR );
  if(ret != 0) {
    Serial.println("failed to initialise trillSensor");
    Serial.print("Error code: ");
    Serial.println(ret);
  } else {
    Serial.println("Initialized!");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
