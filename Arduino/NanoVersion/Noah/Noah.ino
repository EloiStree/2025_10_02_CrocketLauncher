#include <Arduino.h>

#define RXD2 17   // U2RXD
#define TXD2 16   // U2TXD
#define LED  13   // On-board LED (GPIO13)

#define MANUAL_BUTTON_PIN  3   // Button pin with internal pull-up
#define MANUAL_BUTTON_MIDI  48   // Button pin with internal pull-up

bool var_is_pressing = false;


//If you inversed the cable order
// #define L298N_PIN1 35
// #define L298N_PIN2 36
// #define L298N_PIN3 37
// #define L298N_PIN4 38

#define L298N_PIN1 38
#define L298N_PIN2 37
#define L298N_PIN3 36
#define L298N_PIN4 35

bool use_classic_motor=true;
const float MOTOR_DELAY_CLOSE =2000;
const float MOTOR_DELAY_OPEN =1500;




void setup() {
  pinMode(LED, OUTPUT);
  pinMode(MANUAL_BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up
  pinMode(MANUAL_BUTTON_MIDI, INPUT_PULLUP); // Use internal pull-up

  pinMode(L298N_PIN1, OUTPUT);
  pinMode(L298N_PIN2, OUTPUT);
  pinMode(L298N_PIN3, OUTPUT);
  pinMode(L298N_PIN4, OUTPUT);


  Serial.begin(9600);  
  Serial.println("UART1 initialized.");

  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); 
  Serial.println("UART2 initialized.");
}


//---
void l298n_start_pressing(){

  if(!use_classic_motor) return;
  digitalWrite(L298N_PIN1, HIGH);
  digitalWrite(L298N_PIN2, LOW);
  digitalWrite(L298N_PIN3, HIGH);
  digitalWrite(L298N_PIN4, LOW);
}

void l298n_start_releasing(){

  if(!use_classic_motor) return;
  digitalWrite(L298N_PIN1, LOW);
  digitalWrite(L298N_PIN2, HIGH);
  digitalWrite(L298N_PIN3, LOW);
  digitalWrite(L298N_PIN4, HIGH);
}

void l298n_stop() {
  
  if(!use_classic_motor) return;
  digitalWrite(L298N_PIN1, LOW);
  digitalWrite(L298N_PIN2, LOW);
  digitalWrite(L298N_PIN3, LOW);
  digitalWrite(L298N_PIN4, LOW);
}


void l298n_press(){

 if(!use_classic_motor) return;
  l298n_start_pressing();
  delay(MOTOR_DELAY_CLOSE);
  l298n_stop();

}
void l298n_release(){
  
 if(!use_classic_motor) return;
  l298n_start_releasing();
  delay(MOTOR_DELAY_OPEN);
  l298n_stop()  ;
}


void press() {
  var_is_pressing = true;
  digitalWrite(LED, HIGH);  
  Serial.println("Pressing");
  l298n_press();
  delay(20);
  steps_close();
  delay(1000);
}

void release() {
  var_is_pressing = false;
  digitalWrite(LED, LOW);  
  Serial.println("Releasing");
  l298n_release();
  delay(20);
  steps_open();
  delay(1000);
}

void loop() {
  // Button handling with internal pull-up (LOW = pressed)
  if (digitalRead(MANUAL_BUTTON_PIN) == LOW && digitalRead(MANUAL_BUTTON_MIDI) == LOW) {
    if (!var_is_pressing) {
      press();
    }
    else if (var_is_pressing) {
      release();
    }
  }

   if (Serial.available()) {
      // Read the incoming data and send it to the Serial monitor
      byte incomingByte = Serial.read();
        char c = (char)incomingByte;
        Serial.print("Received: ");
        Serial.println(c);
  }


  // UART2 handling
  if (Serial2.available()) {
    char c = (char) Serial2.read();
    Serial.print("UART2 received: ");
    Serial.println(c);

    if (c == '1' || c == 'u' || c == 'U') {
      press();
    } 
    else if (c == '0' || c == 'd' || c == 'D') {
      release();
    }
  }
}
