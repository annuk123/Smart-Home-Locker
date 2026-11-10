// // #include <SPI.h>
// // #include <MFRC522.h>
// // #include <Servo.h>
// // #include <Wire.h>
// // #include <Adafruit_GFX.h>
// // #include <Adafruit_SH110X.h>

// // // ---------- PINS ----------

// // const int SS_PIN = 10;
// // const int RST_PIN = 9;

// // const int SERVO_PIN = 6;
// // const int BUZZER_PIN = 8;

// // // ---------- OBJECTS ----------

// // MFRC522 rfid(SS_PIN, RST_PIN);
// // Servo lockServo;

// // Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

// // // ---------- LOCK POSITIONS ----------

// // const int LOCKED_POSITION = 0;
// // const int UNLOCKED_POSITION = 90;


// // void setup() {

// //   Serial.begin(9600);

// //   // Buzzer
// //   pinMode(BUZZER_PIN, OUTPUT);

// //   // Servo
// //   lockServo.attach(SERVO_PIN);
// //   lockServo.write(LOCKED_POSITION);

// //   // SPI + RFID
// //   SPI.begin();
// //   rfid.PCD_Init();

// //   // OLED
// //   if (!display.begin(0x3C, true)) {
// //     Serial.println("OLED not found!");

// //     while (true) {
// //       digitalWrite(BUZZER_PIN, HIGH);
// //       delay(100);
// //       digitalWrite(BUZZER_PIN, LOW);
// //       delay(900);
// //     }
// //   }

// //   // Startup screen
// //   display.clearDisplay();
// //   display.setTextColor(SH110X_WHITE);

// //   display.setTextSize(2);
// //   display.setCursor(10, 5);
// //   display.println("SMART");

// //   display.setCursor(10, 30);
// //   display.println("LOCK");

// //   display.display();

// //   // Startup beep
// //   tone(BUZZER_PIN, 1000, 150);
// //   delay(500);

// //   display.clearDisplay();

// //   display.setTextSize(1);
// //   display.setCursor(20, 10);
// //   display.println("System Ready");

// //   display.setCursor(15, 35);
// //   display.println("Scan RFID Card");

// //   display.display();

// //   Serial.println("Smart Lock Ready");
// // }


// // void loop() {

// //   // Check whether a new card is present
// //   if (!rfid.PICC_IsNewCardPresent()) {
// //     return;
// //   }

// //   // Read the card
// //   if (!rfid.PICC_ReadCardSerial()) {
// //     return;
// //   }

// //   Serial.print("Card UID: ");

// //   String uid = "";

// //   for (byte i = 0; i < rfid.uid.size; i++) {

// //     if (rfid.uid.uidByte[i] < 0x10) {
// //       Serial.print("0");
// //       uid += "0";
// //     }

// //     Serial.print(rfid.uid.uidByte[i], HEX);
// //     uid += String(rfid.uid.uidByte[i], HEX);
// //   }

// //   Serial.println();

// //   // Show UID on OLED

// //   display.clearDisplay();

// //   display.setTextSize(1);
// //   display.setCursor(0, 0);
// //   display.println("CARD DETECTED");

// //   display.setCursor(0, 20);
// //   display.println("UID:");

// //   display.setTextSize(2);
// //   display.setCursor(0, 38);
// //   display.println(uid);

// //   display.display();

// //   // Beep
// //   tone(BUZZER_PIN, 1200, 150);

// //   delay(2000);

// //   // Prepare RFID reader for next card
// //   rfid.PICC_HaltA();
// //   rfid.PCD_StopCrypto1();

// //   // Return to waiting screen
// //   display.clearDisplay();

// //   display.setTextSize(1);
// //   display.setCursor(20, 10);
// //   display.println("System Ready");

// //   display.setCursor(15, 35);
// //   display.println("Scan RFID Card");

// //   display.display();
// // }



// #include <Servo.h>

// Servo servo;

// const int SERVO_PIN = 6;
// const int BUZZER_PIN = 8;

// void setup() {
//   servo.attach(SERVO_PIN);
//   pinMode(BUZZER_PIN, OUTPUT);

//   Serial.begin(9600);
//   Serial.println("Testing servo and buzzer...");
// }

// void loop() {

//   Serial.println("Servo: 0 degrees");
//   servo.write(0);
//   tone(BUZZER_PIN, 1000);
//   delay(500);
//   noTone(BUZZER_PIN);
//   delay(1500);

//   Serial.println("Servo: 90 degrees");
//   servo.write(90);
//   tone(BUZZER_PIN, 1500);
//   delay(500);
//   noTone(BUZZER_PIN);
//   delay(1500);

//   Serial.println("Servo: 180 degrees");
//   servo.write(180);
//   tone(BUZZER_PIN, 2000);
//   delay(500);
//   noTone(BUZZER_PIN);
//   delay(1500);
// }

// const int buzzerPin = 8;

// void setup() {
//   pinMode(buzzerPin, OUTPUT);
// }

// void loop() {
//   digitalWrite(buzzerPin, HIGH);
//   delay(1000);

//   digitalWrite(buzzerPin, LOW);
//   delay(1000);
// }


#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// ================= PINS =================

#define SS_PIN 10
#define RST_PIN 9

const int SERVO_PIN = 6;
const int BUZZER_PIN = 8;

// ================= OBJECTS =================

MFRC522 rfid(SS_PIN, RST_PIN);

Servo lockServo;

Adafruit_SH1106G display(128, 64, &Wire);

// ================= LOCK SETTINGS =================

const int LOCKED_POSITION = 0;
const int UNLOCKED_POSITION = 90;

// Your RFID UID
String authorizedUID = "59D71005";

// ================= FUNCTIONS =================

void showReadyScreen() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(20, 5);
  display.println("SMART LOCK");

  display.setCursor(10, 30);
  display.println("Scan your RFID card");

  display.display();
}

void accessGranted() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(15, 10);
  display.println("ACCESS GRANTED");

  display.setCursor(25, 35);
  display.println("UNLOCKED");

  display.display();

  // Short success beep
  digitalWrite(BUZZER_PIN, HIGH);
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);

  // Unlock
  lockServo.write(UNLOCKED_POSITION);

  delay(5000);

  // Lock again
  lockServo.write(LOCKED_POSITION);

  display.clearDisplay();
  display.setCursor(25, 25);
  display.println("LOCKED");
  display.display();

  delay(1000);

  showReadyScreen();
}

void accessDenied() {
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(20, 20);
  display.println("ACCESS DENIED");

  display.display();

  // Warning beeps
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }

  delay(1500);

  showReadyScreen();
}

// ================= SETUP =================

void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Servo starts locked
  lockServo.attach(SERVO_PIN);
  lockServo.write(LOCKED_POSITION);

  // RFID
  SPI.begin();
  rfid.PCD_Init();

  // OLED
  if (!display.begin(0x3C, true)) {
    Serial.println("OLED not found!");
    while (true);
  }

  // Startup screen
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(15, 10);
  display.println("SMART");

  display.setCursor(15, 35);
  display.println("LOCK");

  display.display();

  delay(1500);

  // Startup beep
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);

  showReadyScreen();

  Serial.println("Smart Lock Ready!");
}

// ================= LOOP =================

void loop() {

  // Wait for a new card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  // Read the card
  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Convert UID to String
  String currentUID = "";

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      currentUID += "0";
    }

    currentUID += String(rfid.uid.uidByte[i], HEX);
  }

  currentUID.toUpperCase();

  Serial.print("Card UID: ");
  Serial.println(currentUID);

  // Check authorization
  if (currentUID == authorizedUID) {

    Serial.println("ACCESS GRANTED");
    accessGranted();

  } else {

    Serial.println("ACCESS DENIED");
    accessDenied();
  }

  // Stop RFID communication
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// #include <SPI.h>
// #include <MFRC522.h>
// #include <Servo.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SH110X.h>

// // ================= PINS =================

// #define SS_PIN 10
// #define RST_PIN 9

// const int SERVO_PIN = 6;
// const int BUZZER_PIN = 8;


// // ================= OBJECTS =================

// MFRC522 rfid(SS_PIN, RST_PIN);

// Servo lockServo;

// Adafruit_SH1106G display(128, 64, &Wire);


// // ================= LOCK SETTINGS =================

// const int LOCKED_POSITION = 0;
// const int UNLOCKED_POSITION = 90;


// // ================= AUTHORIZED RFID =================

// String authorizedUID = "59D71005";


// // ================= UNLOCK STATE =================

// bool isUnlocked = false;

// unsigned long unlockStartTime = 0;

// const unsigned long UNLOCK_DURATION = 5000;


// // ================= FUNCTIONS =================


// // ---------- READY SCREEN ----------

// void showReadyScreen() {

//   display.clearDisplay();

//   display.setTextSize(1);
//   display.setTextColor(SH110X_WHITE);

//   display.setCursor(20, 5);
//   display.println("SMART LOCK");

//   display.setCursor(10, 30);
//   display.println("Scan your RFID card");

//   display.display();
// }


// // ---------- ACCESS GRANTED ----------

// void accessGranted() {

//   display.clearDisplay();

//   display.setTextSize(1);
//   display.setTextColor(SH110X_WHITE);

//   display.setCursor(15, 10);
//   display.println("ACCESS GRANTED");

//   display.setCursor(25, 35);
//   display.println("UNLOCKED");

//   display.display();


//   // Success beep
//   digitalWrite(BUZZER_PIN, HIGH);
//   delay(150);
//   digitalWrite(BUZZER_PIN, LOW);


//   // Unlock servo
//   lockServo.write(UNLOCKED_POSITION);


//   // Start timer
//   unlockStartTime = millis();

//   isUnlocked = true;

//   Serial.println("LOCK STATE: UNLOCKED");
// }


// // ---------- ACCESS DENIED ----------

// void accessDenied() {

//   display.clearDisplay();

//   display.setTextSize(1);
//   display.setTextColor(SH110X_WHITE);

//   display.setCursor(20, 20);
//   display.println("ACCESS DENIED");

//   display.display();


//   // Warning beeps
//   for (int i = 0; i < 3; i++) {

//     digitalWrite(BUZZER_PIN, HIGH);
//     delay(200);

//     digitalWrite(BUZZER_PIN, LOW);
//     delay(200);
//   }


//   delay(1500);

//   showReadyScreen();
// }


// // ================= SETUP =================

// void setup() {

//   Serial.begin(9600);


//   // ---------- BUZZER ----------

//   pinMode(BUZZER_PIN, OUTPUT);
//   digitalWrite(BUZZER_PIN, LOW);


//   // ---------- SERVO ----------

//   lockServo.attach(SERVO_PIN);
//   lockServo.write(LOCKED_POSITION);


//   // ---------- RFID ----------

//   SPI.begin();
//   rfid.PCD_Init();


//   // ---------- OLED ----------

//   Wire.begin();

//   display.begin(0x3C, true);


//   // ---------- STARTUP SCREEN ----------

//   display.clearDisplay();

//   display.setTextSize(2);
//   display.setTextColor(SH110X_WHITE);

//   display.setCursor(15, 10);
//   display.println("SMART");

//   display.setCursor(15, 35);
//   display.println("LOCK");

//   display.display();


//   delay(1500);


//   // Startup beep

//   digitalWrite(BUZZER_PIN, HIGH);
//   delay(100);
//   digitalWrite(BUZZER_PIN, LOW);


//   showReadyScreen();


//   Serial.println("Smart Lock V2 Ready!");
// }


// // ================= LOOP =================

// void loop() {


//   // ========================================
//   // NON-BLOCKING UNLOCK TIMER
//   // ========================================

//   if (isUnlocked &&
//       millis() - unlockStartTime >= UNLOCK_DURATION) {


//     // Lock servo again

//     lockServo.write(LOCKED_POSITION);


//     // Show locked message

//     display.clearDisplay();

//     display.setTextSize(1);
//     display.setTextColor(SH110X_WHITE);

//     display.setCursor(25, 25);
//     display.println("LOCKED");

//     display.display();


//     // Lock state finished

//     isUnlocked = false;

//     Serial.println("LOCK STATE: LOCKED");


//     delay(1000);

//     showReadyScreen();
//   }


//   // ========================================
//   // WHILE UNLOCKED, DON'T READ NEW CARDS
//   // ========================================

//   if (isUnlocked) {
//     return;
//   }


//   // ========================================
//   // RFID CHECK
//   // ========================================

//   if (!rfid.PICC_IsNewCardPresent()) {
//     return;
//   }


//   if (!rfid.PICC_ReadCardSerial()) {
//     return;
//   }


//   // ========================================
//   // READ UID
//   // ========================================

//   String currentUID = "";


//   for (byte i = 0; i < rfid.uid.size; i++) {

//     if (rfid.uid.uidByte[i] < 0x10) {
//       currentUID += "0";
//     }

//     currentUID += String(rfid.uid.uidByte[i], HEX);
//   }


//   currentUID.toUpperCase();


//   Serial.print("Card UID: ");
//   Serial.println(currentUID);


//   // ========================================
//   // STOP RFID COMMUNICATION
//   // ========================================

//   rfid.PICC_HaltA();
//   rfid.PCD_StopCrypto1();


//   // ========================================
//   // AUTHORIZATION
//   // ========================================

//   if (currentUID == authorizedUID) {

//     Serial.println("ACCESS GRANTED");

//     accessGranted();

//   } else {

//     Serial.println("ACCESS DENIED");

//     accessDenied();
//   }
// }