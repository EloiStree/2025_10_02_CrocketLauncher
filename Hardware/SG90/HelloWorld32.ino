#include <ESP32Servo.h>

Servo myServo;  // Create a servo object

void setup() {
  // Attach the servo to GPIO pin 18
  // Arguments: pin, minPulseWidth, maxPulseWidth
  // Default range: 500 µs to 2400 µs (good for SG90)
  myServo.attach(5, 500, 2400);
}

void loop() {
  // Move to 0°
  myServo.write(0);
  delay(1000);

  // Move to 90°
  myServo.write(90);
  delay(1000);

  // Move to 180°
  myServo.write(180);
  delay(1000);
}
