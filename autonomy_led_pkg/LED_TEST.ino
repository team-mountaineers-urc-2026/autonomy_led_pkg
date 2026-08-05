#define RED_PIN 10
#define GREEN_PIN 9
#define BLUE_PIN 11

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // All off (common anode = HIGH is off)
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
}

void loop() {
  // Red
  digitalWrite(RED_PIN, LOW);
  delay(1000);
  digitalWrite(RED_PIN, HIGH);

  // Green
  digitalWrite(GREEN_PIN, LOW);
  delay(1000);
  digitalWrite(GREEN_PIN, HIGH);

  // Blue
  digitalWrite(BLUE_PIN, LOW);
  delay(1000);
  digitalWrite(BLUE_PIN, HIGH);

  // All on (white)
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  delay(1000);

  // All off
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);
  delay(1000);
}