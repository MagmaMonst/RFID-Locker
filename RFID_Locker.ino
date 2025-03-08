#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
const int IN1 = 5;
const int IN2 = 6;
void setup() {
  // put your setup code here, to run once:
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
Serial.println("Please scan your RFID card");
Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
if (! mfrc522.PICC_IsNewCardPresent()) {
  return;
}
if (! mfrc522.PICC_ReadCardSerial()) {
  return;
}
Serial.print("UID tag: ");
String content = "";
byte letter;
for (byte i = 0; i < mfrc522.uid.size; i++) {
  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
  Serial.print(mfrc522.uid.uidByte[i], HEX);
  content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
  content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
Serial.print("Status: ");
content.toUpperCase();
if (content.substring(1) == "43 AA B5 29") {
  Serial.println("Access granted");
  Serial.println();
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(10000);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  delay(200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}
else {
  Serial.println("Access denied");
  Serial.println();
  delay(3000);
}
}
