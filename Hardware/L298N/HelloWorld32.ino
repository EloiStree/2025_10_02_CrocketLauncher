#define IN1 35
#define IN2 36
#define IN3 37
#define IN4 38

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void motorAForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void motorABackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
}

void motorAStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

// Function to move Motor B
void motorBForward() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void motorBBackward() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void motorBStop() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  motorAForward();
  motorBForward();
  delay(2000);

  motorABackward();
  motorBBackward();
  delay(2000);

  motorAStop();
  motorBStop();
  delay(1000);
}
