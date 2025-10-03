HC05

[<img width="1233" height="659" alt="image" src="https://github.com/user-attachments/assets/c0af9bf7-7eb3-499b-80e5-49a36809c1ba" />](https://www.amazon.com.be/s?k=hc05&crid=1Y1IJYWA620DP&sprefix=hc05%2Caps%2C89&ref=nb_sb_noss_1
)
https://www.amazon.com.be/s?k=hc05&crid=1Y1IJYWA620DP&sprefix=hc05%2Caps%2C89&ref=nb_sb_noss_1


https://www.electronicwings.com/sensors-modules/bluetooth-module-hc-05-
https://www.amazon.com.be/s?k=hc05&crid=1Y1IJYWA620DP&sprefix=hc05%2Caps%2C89&ref=nb_sb_noss_1


``` ino
#include <Arduino.h>

#define RXD2 17   // GPIO16 (U2RXD)
#define TXD2 16   // GPIO17 (U2TXD)
#define LED 13    // On-board LED (GPIO13)

void setup() {
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);  
  Serial.println("UART1 initialized.");

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
  Serial.println("UART2 initialized.");
}

void press() {
  digitalWrite(LED, HIGH);  
    Serial.println("Pressing");
}

void release() {
  digitalWrite(LED, LOW);  
    Serial.println("Releasing");

}

void loop() {
  if (Serial2.available()) {
    char c = (char) Serial2.read();
    Serial.println(c);
    if (c == '1' || c == 'u' || c == 'U') {
      press();
    }
    if (c == '0' || c == 'd' || c == 'D') {
      release();
    }
  }
}

```
