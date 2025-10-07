#include <SoftwareSerial.h>


// #define RXD2 10   // U2RXD
// #define TXD2 11   // U2TXD
#define RXD2 11   // U2RXD
#define TXD2 10   // U2TXD
SoftwareSerial BT(RXD2, TXD2);  // RX, TX

#define LED  13   // On-board LED (GPIO13)

#define MANUAL_BUTTON_PIN  7   // Button pin with internal pull-up
#define MANUAL_BUTTON_MIDI  8   // Button pin with internal pull-up

bool var_is_pressing = false;



//#define DRV8871_PIN1 4
//#define DRV8871_PIN2 5

#define DRV8871_PIN1 5
#define DRV8871_PIN2 4


// Speed in milliseconds per step (smaller = faster)
int stepDelay = 5;  

bool use_classic_motor=true;
const float MOTOR_DELAY_CLOSE =2000;
const float MOTOR_DELAY_OPEN =1500;





void setup() {
  pinMode(LED, OUTPUT);
  pinMode(MANUAL_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up
  pinMode(MANUAL_BUTTON_MIDI, INPUT_PULLUP); // Use internal pull-up

  pinMode(DRV8871_PIN1, OUTPUT);
  pinMode(DRV8871_PIN2, OUTPUT);
 

  Serial.begin(9600);  
  Serial.println("UART1 initialized.");

  BT.begin(9600);
  Serial.println("UART2 initialized.");
}






//---
void DRV8871_start_pressing(){

 if(!use_classic_motor) return;
  digitalWrite(DRV8871_PIN1, HIGH);
  digitalWrite(DRV8871_PIN2, LOW);

}
void DRV8871_start_releasing(){

 if(!use_classic_motor) return;
  digitalWrite(DRV8871_PIN1, LOW);
  digitalWrite(DRV8871_PIN2, HIGH);
}

void DRV8871_stop() {
  
 if(!use_classic_motor) return;
  digitalWrite(DRV8871_PIN1, LOW);
  digitalWrite(DRV8871_PIN2, LOW);

}


void DRV8871_press(){

 if(!use_classic_motor) return;
  DRV8871_start_pressing();
  delay(MOTOR_DELAY_CLOSE);
  DRV8871_stop();

}
void DRV8871_release(){
  
 if(!use_classic_motor) return;
  DRV8871_start_releasing();
  delay(MOTOR_DELAY_OPEN);
  DRV8871_stop()  ;
}


void press() {
  var_is_pressing = true;
  digitalWrite(LED, HIGH);  
  Serial.println("Pressing");
  DRV8871_press();
  
}

void release() {
  var_is_pressing = false;
  digitalWrite(LED, LOW);  
  Serial.println("Releasing");
  DRV8871_release();
  
}

void loop() {

    press();
    delay(3000);
    release();
    delay(3000);

  // // Button handling with internal pull-up (LOW = pressed)
  // if (digitalRead(MANUAL_BUTTON_PIN) == LOW && digitalRead(MANUAL_BUTTON_MIDI) == LOW) {
  //   if (!var_is_pressing) {
  //     press();
  //   }
  //   else if (var_is_pressing) {
  //     release();
  //   }
  // }

  //  if (Serial.available()) {
  //     // Read the incoming data and send it to the Serial monitor
  //     byte incomingByte = Serial.read();
  //       char c = (char)incomingByte;
  //       Serial.print("Received: ");
  //       Serial.println(c);
  // }


  // // UART2 handling
  // if (BT.available()) {
  //       byte incomingByte = BT.read();
  //       BT.write(incomingByte);
  //     char c = (char) byte;
  //     Serial.print("UART2 received: ");
  //     Serial.println(c);

  //     if (c == '1' || c == 'u' || c == 'U') {
  //       press();
  //     } 
  //     else if (c == '0' || c == 'd' || c == 'D') {
  //       release();
  //     }
  // }
}
