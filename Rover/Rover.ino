#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile
// Pins
#define IN1 8
#define IN2 9
#define IN3 7
#define IN4 6
#define ENA 11
#define ENB 3
#define POWER_RX 13
#define M_IN3 4
#define M_IN4 5
#define M_ENB 13

int speed = 150;
int powerState;
// RH_ASK driver;
RH_ASK driver(2000, 12, 13, 5);  // ESP8266: do not use pin 11


void setup() {
  Serial.begin(115200);  // Debugging only
  if (!driver.init()) Serial.println("init failed");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(POWER_RX, INPUT);
  pinMode(M_IN3, OUTPUT);
  pinMode(M_IN4, OUTPUT);
  pinMode(M_ENB, OUTPUT);
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
    // SPEED CONTROL
    // if (typeof(msg) == int) {
    //   analogWrite(ENA, msg);
    //   analogWrite(ENB, msg);
    // } else {
      analogWrite(ENA, speed);
      analogWrite(ENB, speed);
      analogWrite(M_ENB, speed);
    // }
    // MOVEMENT
    if (msg == "Forward") {
      Serial.println("Motor Run");
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (msg == "Reverse") {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    } else if (msg == "Right") {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    } else if (msg == "Left") {
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    // LIFT
    } else if (msg == "Descend") {
      digitalWrite(M_IN3, LOW);
      digitalWrite(M_IN4, HIGH);
    } else if (msg == "Ascend") {
      digitalWrite(M_IN3, HIGH);
      digitalWrite(M_IN4, LOW);
    } else stop();
  }
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(M_IN3, LOW);
  digitalWrite(M_IN4, LOW);
}
