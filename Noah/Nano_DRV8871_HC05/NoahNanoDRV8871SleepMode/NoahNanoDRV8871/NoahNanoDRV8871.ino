#include <SoftwareSerial.h>
#include <avr/sleep.h>

#define RXD2 3
#define TXD2 2
SoftwareSerial BT(RXD2, TXD2);  // RX, TX

#define LED 13
#define DRV8871_PIN1 11
#define DRV8871_PIN2 10

bool use_classic_motor = true;

// Motor timing in milliseconds
const unsigned long MOTOR_DELAY_CLOSE = 2000;
const unsigned long MOTOR_DELAY_OPEN  = 1500;
const unsigned long RELEASE_WAIT_TIME = 3000;  // <-- wait time (n seconds) before pressing again

bool var_is_pressing = false;
bool motorRunning = false;
bool pressing = false;
bool waitingAfterRelease = false;  // <-- track waiting state
unsigned long actionStart = 0;
unsigned long waitStart = 0;

void setup() {
    pinMode(LED, OUTPUT);
    pinMode(DRV8871_PIN1, OUTPUT);
    pinMode(DRV8871_PIN2, OUTPUT);

    BT.begin(9600);
}

void DRV8871_start_pressing() {
    if (!use_classic_motor) return;
    digitalWrite(DRV8871_PIN1, HIGH);
    digitalWrite(DRV8871_PIN2, LOW);
}

void DRV8871_start_releasing() {
    if (!use_classic_motor) return;
    digitalWrite(DRV8871_PIN1, LOW);
    digitalWrite(DRV8871_PIN2, HIGH);
}

void DRV8871_stop() {
    if (!use_classic_motor) return;
    digitalWrite(DRV8871_PIN1, LOW);
    digitalWrite(DRV8871_PIN2, LOW);
}

void startPress() {
    var_is_pressing = true;
    pressing = true;
    digitalWrite(LED, HIGH);
    DRV8871_start_pressing();
    actionStart = millis();
    motorRunning = true;
}

void startRelease() {
    var_is_pressing = false;
    pressing = false;
    digitalWrite(LED, LOW);
    DRV8871_start_releasing();
    actionStart = millis();
    motorRunning = true;
}

void loop() {
    unsigned long now = millis();

    // Stop motor when its movement duration is done
    if (motorRunning) {
        if (pressing && now - actionStart >= MOTOR_DELAY_CLOSE) {
            DRV8871_stop();
            motorRunning = false;
        } 
        else if (!pressing && now - actionStart >= MOTOR_DELAY_OPEN) {
            DRV8871_stop();
            motorRunning = false;

            // If we just finished a release triggered by 'R', start waiting
            if (waitingAfterRelease == false) {
                waitingAfterRelease = true;
                waitStart = millis();
            }
        }
    }

    // After waiting period, start pressing again
    if (waitingAfterRelease && (now - waitStart >= RELEASE_WAIT_TIME)) {
        startPress();
        waitingAfterRelease = false;
    }

    // UART2 handling (Bluetooth)
    if (BT.available()) {
        char c = (char)BT.read();
        BT.write(c);  // Echo back

        if (c == '1' || c == 'u' || c == 'U') startPress();
        else if (c == '0' || c == 'd' || c == 'D') startRelease();
        else if (c == 't' || c == 'T') startPress();
        else if (c == 'r' || c == 'R') {
            // Start the release, then wait n seconds before pressing again
            startRelease();
            waitingAfterRelease = false; // reset wait state
        }
    }

    // Sleep when idle
    if (!motorRunning && !waitingAfterRelease && !BT.available()) {
        set_sleep_mode(SLEEP_MODE_IDLE);
        sleep_enable();
        sleep_cpu();
        sleep_disable();
    }
}
