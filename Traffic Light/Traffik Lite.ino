const byte s1r = 13;
const byte s1a = 12;
const byte s1g = 11;
const byte s2r = 10;
const byte s2a = 9;
const byte s2g = 8;
const byte button1 = 7;


int systemState = 0;
int buttonpressed = 0;


void testandOutput() {
  Serial.begin(9600);
  pinMode(button1, INPUT);
  for (int i = 8; i < 14; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
    delay(150);
    digitalWrite(i, LOW);
    buttonpressed = digitalRead(button1);
  }
}

void resetlight() {
  for (int i = 8; i < 14; i++) {
    digitalWrite(i, LOW);
    delay(1);
    systemState = 0;
  }
}

void setup() {
  testandOutput();
}

void loop() {

  if (systemState == 0) {
    digitalWrite(s1r, HIGH);
    digitalWrite(s2r, HIGH);
    delay(5000);
    systemState = 1;
  } else if (systemState == 1) {
    digitalWrite(s1r, HIGH);
    digitalWrite(s2r, HIGH);
    digitalWrite(s2a, HIGH);
    delay(3000);
    systemState = 2;
  } else if (systemState == 2) {
    digitalWrite(s2r, LOW);
    digitalWrite(s2a, LOW);
    digitalWrite(s1r, HIGH);
    digitalWrite(s2g, HIGH);
    delay(10000);
    systemState = 3;
  } else if (systemState == 3) {
    digitalWrite(s2r, LOW);
    digitalWrite(s2g, LOW);
    digitalWrite(s1r, HIGH);
    digitalWrite(s2a, HIGH);
    delay(3000);
    systemState = 4;
  } else if (systemState == 4) {
    digitalWrite(s2a, LOW);
    digitalWrite(s1r, HIGH);
    digitalWrite(s2r, HIGH);
    delay(5000);
    systemState = 5;
  } else if (systemState == 5) {
    digitalWrite(s1r, HIGH);
    digitalWrite(s1a, HIGH);
    digitalWrite(s2r, HIGH);
    delay(3000);
    systemState = 6;
  } else if (systemState == 6) {
    digitalWrite(s1a, LOW);
    digitalWrite(s1r, LOW);
    digitalWrite(s1g, HIGH);
    digitalWrite(s2r, HIGH);
    delay(10000);
    systemState = 7;
  } else if (systemState == 7) {
    digitalWrite(s1r, LOW);
    digitalWrite(s1g, LOW);
    digitalWrite(s1a, HIGH);
    digitalWrite(s2r, HIGH);
    delay(3000);
    resetlight();
  }
}