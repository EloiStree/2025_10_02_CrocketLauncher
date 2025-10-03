Chat gpt proposition

----------


```
#include <WiFi.h>
#include <WiFiUdp.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const unsigned int localPort = 12345; // UDP port to listen on

WiFiUDP udp;
char incomingPacket[255];  // buffer for incoming packets

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  
  udp.begin(localPort); // start listening
  Serial.printf("Listening on UDP port %d\n", localPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = 0;
    Serial.printf("Received: %s\n", incomingPacket);
  }
}

```

If the esp is the wifi server


```
#include <WiFi.h>
#include <WiFiUdp.h>

const char* apSSID = "ESP32_AP";
const char* apPassword = "12345678";  // min 8 chars
const unsigned int localPort = 12345;  // UDP port

WiFiUDP udp;
char incomingPacket[255];

void setup() {
  Serial.begin(115200);

  // Start the ESP32 in AP mode
  WiFi.softAP(apSSID, apPassword);
  Serial.println("ESP32 AP started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Start UDP
  udp.begin(localPort);
  Serial.printf("Listening for UDP on port %d\n", localPort);
}

void loop() {
  int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, 255);
    if (len > 0) incomingPacket[len] = 0;
    
    Serial.printf("Received from %s:%d: %s\n",
                  udp.remoteIP().toString().c_str(),
                  udp.remotePort(),
                  incomingPacket);
    
    // Optional: send a response
    udp.beginPacket(udp.remoteIP(), udp.remotePort());
    udp.write("ACK from ESP32");
    udp.endPacket();
  }
  
  // Your main loop continues running without blocking
}
```
