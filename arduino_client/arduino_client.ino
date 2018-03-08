#include <SPI.h>
#include <EthernetV2_0.h>

byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "https://us-central1-emilyplusplus-iot-helper.cloudfunctions.net"; // Google

EthernetClient client;
#define W5200_CS  10
#define SDCARD_CS 4
void setup() {
  Serial.begin(9600);
  pinMode(SDCARD_CS,OUTPUT);
  digitalWrite(SDCARD_CS,HIGH);//Deselect the SD card
   while (!Serial) {
    ;
  }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for(;;)
      ;
  }

  delay(1000);
  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /yt-subscribers HTTP/1.0");
    client.println();
  } 
  else {
    Serial.println("connection failed");
  }
}

void loop()
{
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    for(;;)
      ;
  }
}

