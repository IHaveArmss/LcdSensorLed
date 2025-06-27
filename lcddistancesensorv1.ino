#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 13, 6, 7, 8, A0); // RS, E, D4, D5, D6, D7

const int trigPin = 9;
const int echoPin = 10;
const int ledPins[] = {2, 3, 4, 5};

long duration;
int distance;

void setup() {
  analogWrite(11, 75); // <-- bring back contrast setting!
  lcd.begin(16, 2);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600);
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
  delay(1000);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.034 / 2;
  }

  Serial.print("Distance: ");
  if (distance == -1) {
    Serial.println("Out of range");
  } else {
    Serial.print(distance);
    Serial.println(" cm");
  }

  // LCD Output
  lcd.setCursor(0, 0);
  if (distance == -1) {
    lcd.print("Out of range    ");
  } else {
    lcd.print("Distance: ");
    if (distance < 100) lcd.print(" ");
    lcd.print(distance);
    lcd.print(" cm   ");
  }

  lcd.setCursor(0, 1);
  lcd.print("                "); // clear second line

  // LEDs
  digitalWrite(ledPins[0], distance > 25);
  digitalWrite(ledPins[1], distance > 50);
  digitalWrite(ledPins[2], distance > 75);
  digitalWrite(ledPins[3], distance > 100);

  delay(200);
}
