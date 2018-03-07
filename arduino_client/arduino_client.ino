#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
char server[] = "https://us-central1-emilyplusplus-iot-helper.cloudfunctions.net";    // name address for Google (using DNS)

IPAddress ip(192, 168, 0, 177);
EthernetClient client;

void setup() {
  Serial.begin(9600);
  while (!Serial) { }

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  delay(1000);
  Serial.println("connecting...");

  if (client.connect(server, 80)) {
    Serial.println("connected");
    client.println("GET /yt-subscribers HTTP/1.1");
    client.println("Host: https://us-central1-emilyplusplus-iot-helper.cloudfunctions.net");
    client.println("Connection: close");
    client.println();
  } else {
    Serial.println("connection failed");
  }
}

void loop() {
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    while (true);
  }
}
