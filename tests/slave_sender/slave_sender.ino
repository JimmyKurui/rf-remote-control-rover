/*
 Arduino                     Transmitter
  GND--------------------------GND
  D12--------------------------Data
  5V---------------------------VCC

*/

#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile

int buttonPin = 8;
int buttonState;

//int buzzerPin = 8;
//  int ledPin = 9;

// RH_ASK driver;
RH_ASK driver(2000, 13, 12, 5);  // ESP8266: do not use pin 11

void setup() {
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  // Button
  pinMode(buttonPin, INPUT_PULLUP);
  //pinMode(buzzerPin, OUTPUT);
  //  pinMode(ledPin, OUTPUT);
}

void loop() {
  const char *msg = "11";

  buttonState = digitalRead(buttonPin);
  delay(50);
  if (buttonState == 1) {
    msg = "On";
  } else {
    msg = "Off";
    // digitalWrite(ledPin, HIGH);
    //digitalWrite(buzzerPin, HIGH);
  }

  Serial.print("Message: ");
  Serial.println(buttonState);
  Serial.println(msg);
  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(200);
}