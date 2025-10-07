#include <SoftwareSerial.h>
SoftwareSerial BT(10, 11);  // RX, TX

void setup() {
  Serial.begin(9600);     // USB Serial
  BT.begin(9600);         // Bluetooth Serial (HC-05 default baud)
}

void loop() {
  if (BT.available()) Serial.write(BT.read());
  if (Serial.available()) BT.write(Serial.read());
}
