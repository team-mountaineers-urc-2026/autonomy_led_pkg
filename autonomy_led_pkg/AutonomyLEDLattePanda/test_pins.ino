void setup() {
  Serial.begin(9600);
  for (int pin = 2; pin <= 13; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // start all off
  }
}

void loop() {
  if (Serial.available() > 0) {
    int temp = Serial.read();
    
    // Turn all pins off first
    for (int pin = 2; pin <= 13; pin++) {
      digitalWrite(pin, HIGH);
    }

    // '0'-'9' tests pins 2-11, 'a' = 12, 'b' = 13
    int targetPin = -1;
    if (temp >= '0' && temp <= '9') {
      targetPin = temp - '0' + 2; // '0'=pin2, '1'=pin3 ... '9'=pin11
    } else if (temp == 'a') {
      targetPin = 12;
    } else if (temp == 'b') {
      targetPin = 13;
    }

    if (targetPin != -1) {
      digitalWrite(targetPin, LOW); // pull LOW to light up
      Serial.print("Pin ");
      Serial.print(targetPin);
      Serial.println(" ON");
    }
  }
}