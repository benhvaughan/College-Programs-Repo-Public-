//Library's
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Constants
const byte ledRed = 10;
const byte ledGreen = 9;
const byte buzzer = 8;
const byte button = 0;
#define echoPin 7
#define trigPin 6

//Variables
String toplineLCD = "Alarm System";
String bottomlineLCD = "Set";
long duration;
int distance;
int buttonState = 0;

//Initialisation function
void initialisation() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(button,INPUT);
  buttonState = digitalRead(button);
  for (int i = 9; i < 11; i++) {
    pinMode(i, OUTPUT);
  }
  for (int i = 9; i < 11; i++) {
    digitalWrite(i, HIGH);
    delay(200);
    digitalWrite(i, LOW);
  }
  for (int i = 9; i < 11; i++) {
    digitalWrite(i, HIGH);
    tone(buzzer, 1250);
    delay(1000);
    digitalWrite(i, LOW);
    noTone(buzzer);
  }
  updateLCD();
  delay(2000);
  lcd.clear();
}

//LCD Update function
void updateLCD() {
  lcd.home();
  lcd.print(toplineLCD);
  lcd.setCursor(0, 1);
  lcd.print(bottomlineLCD);
  lcd.home();
}

void setup() {
  initialisation();
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.0133 / 2;
  toplineLCD = "Distance:";
  bottomlineLCD = (distance);
  updateLCD();
  Serial.println(distance);
  if (distance < 60) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    tone(buzzer, 700);
    delay(50);
    tone(buzzer, 700);
    delay(50);
  } else if (distance > 60) {
    noTone(buzzer);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
  }
}