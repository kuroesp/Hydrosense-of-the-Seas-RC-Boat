
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin Bluetooth
int bluetoothTx = 10;
int bluetoothRx = 11;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

// Pin motor driver
int in1 = 2;  // Motor kanan
int in2 = 3;
int in3 = 4;  // Motor kiri
int in4 = 5;

const int trigPin = 7;
const int echoPin = 8;
const int buzzerPin = 13;
int potPin = A0;

int enA = 6; // PWM untuk motor kanan
int enB = 9; // PWM untuk motor kiri
char command;
int speed;
int oldValue = 0, newValue = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HydroSense");
  lcd.setCursor(0, 1);
  lcd.print(" of the Seas");
  delay(3000);
  lcd.clear();

  String message = "by AK-Zonix Marine  ";
  for (int i = 0; i < message.length() - 15; i++) {
    lcd.setCursor(0, 0);
    lcd.print(message.substring(i, i + 16));
    delay(600);
  }

  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop() {
  // === ULTRASONIC SENSOR ===
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 26000);
  int distance;

  if (duration == 0) {
    distance = -1; // tidak ada pantulan
  } else {
    distance = duration / 58;
  }
  newValue = distance;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance :");

  if (distance == -1) {
    lcd.setCursor(0, 1);
    lcd.print("Out of Range");
    bluetooth.println("Out of Range");
  } else if (distance < 20) {
    lcd.setCursor(0, 1);
    lcd.print("Tidak Terdeteksi");
    bluetooth.println("Tidak Terdeteksi");
  } else {
    lcd.setCursor(0, 1);
    lcd.print(distance);
    lcd.print(" cm");
    bluetooth.println(distance);
  }

  // === BUZZER ===
  if (distance >= 100) {
    digitalWrite(buzzerPin, HIGH);
    delay(500);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  } else if (distance >= 50 && distance <= 99) {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
    delay(100);
  } else if (distance >= 30 && distance <= 49) {
    digitalWrite(buzzerPin, HIGH);
    delay(50);
    digitalWrite(buzzerPin, LOW);
    delay(50);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);

  // === POTENSIO KECEPATAN ===
  int potValue = analogRead(potPin);
  speed = map(potValue, 0, 1023, 0, 255);

  // === KONTROL BLUETOOTH ===
  if (bluetooth.available() > 0) {
    command = bluetooth.read();
    oldValue = newValue;

    Serial.print("Perintah diterima: ");
    Serial.println(command);

    if (command == 'F') {
      maju();
    } else if (command == 'B') {
      mundur();
    } else if (command == 'R') {
      belokKanan();
    } else if (command == 'L') {
      belokKiri();
    } else {
      berhenti();
    }
  }

  delay(200);
}

// === Fungsi Kontrol Motor ===
void maju() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  Serial.println("Maju");
}

void mundur() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  Serial.println("Mundur");
}

// Belok kanan smooth: motor kiri lebih cepat
void belokKanan() {
  analogWrite(enA, speed / 2);
  analogWrite(enB, speed);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  Serial.println("Belok Kanan");
}

// Belok kiri smooth: motor kanan lebih cepat
void belokKiri() {
  analogWrite(enA, speed);
  analogWrite(enB, speed / 2);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  Serial.println("Belok Kiri");
}

void berhenti() {
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  Serial.println("Berhenti");
}



/*
///MANUAL CODE (FROM WIRE)////////////////////////////////////////////

// Pin motor
const int Motor1A = 2; // Motor kiri
const int Motor1B = 3;
const int Motor2A = 4; // Motor kanan
const int Motor2B = 5;
int potPin = A0;

int enA = 6;
int enB = 9;

long duration;
float distance;
char command;
int speed;


void setup() {
  // Set semua pin sebagai OUTPUT
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor2B, OUTPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT); 
}

void loop() {

  int potValue = analogRead(potPin);
  speed = map(potValue, 0, 1023, 0, 255);

  // Maju
  maju();
  delay(2000);

  // Kanan
  kanan();
  delay(2000);

  // Mundur
  mundur();
  delay(2000);

  // Kiri
  kiri();
  delay(2000);

  // Stop sebentar
  stopMotor();
  delay(1000); // Berhenti 1 detik

  // Lanjut lagi ke awal (loop otomatis)
}


// === Fungsi kontrol motor ===
void maju() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
}

void mundur() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

void kiri() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
}

void kanan() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

void stopMotor() {
  analogWrite(enA, speed);
  analogWrite(enB, speed);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
}
////////////////////////////////////////////////////////////////////////
*/
