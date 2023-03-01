/*
 (Receiver is connected on PIN 11

 Arduino                     Receiver
  GND--------------------------GND
  D11--------------------------Data
  5V---------------------------VCC
*/

#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile

// RH_ASK driver;
RH_ASK driver(2000, 12, 13, 5);  // ESP8266: do not use pin 11

int buzzerPin = 8;
int ledPin = 9;

void setup() {
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))  // Non-blocking
  {

    // driver.printBuffer("Got:", buf, buflen);
    // Message with a good checksum received, dump it.
    Serial.print("Received: ");
    String msg;
    for (int i = 0; i < buflen; i++) {
      msg += (char)buf[i];
    }
    Serial.println(msg);

    if (msg == "On") {
      tone(buzzerPin, 100);
      digitalWrite(ledPin, HIGH);
    } else {
      noTone(buzzerPin);
      digitalWrite(ledPin, LOW);
    }
  }
}