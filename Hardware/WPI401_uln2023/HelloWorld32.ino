// Example for ESP32-S3 (Arduino core)
const int in1 = 4;   
const int in2 = 5;
const int in3 = 16;
const int in4 = 17;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void stepCW() {
  // basic 4-step sequence for 28BYJ-48
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);  digitalWrite(in3, LOW);  digitalWrite(in4, LOW);  delay(5);
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH); digitalWrite(in3, LOW);  digitalWrite(in4, LOW);  delay(5);
  digitalWrite(in1, LOW);  digitalWrite(in2, LOW);  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);  delay(5);
  digitalWrite(in1, LOW);  digitalWrite(in2, LOW);  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH); delay(5);
}

void loop() {
  stepCW();
}
