#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile
// Pins
#define ENA 2  //Movement
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6
#define ENB 7
#define ULTRASONIC A0  //Sensors
#define C_ENA 8        // Cleaner spindle
#define C_IN1 9
#define C_IN2 10
#define C_PC 11  // Power clean

int speed = 150;
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

  pinMode(ULTRASONIC, OUTPUT);

  pinMode(C_IN1, OUTPUT);
  pinMode(C_IN2, OUTPUT);
  pinMode(C_ENA, OUTPUT);
  pinMode(C_PC, OUTPUT);
}

void loop() {
  char mg = "rtrre";
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  Serial.println("Motor Run");
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(3000);
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

    // MOVEMENT
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    if (msg == "Forward") {
      Serial.println("Motor Run");
      // digitalWrite(IN1, HIGH);
      // digitalWrite(IN2, LOW);
      // digitalWrite(IN3, HIGH);
      // digitalWrite(IN4, LOW);
      movement(HIGH, 0, HIGH, 0);
    } else if (msg == "Reverse") {
      // digitalWrite(IN1, LOW);
      // digitalWrite(IN2, HIGH);
      // digitalWrite(IN3, LOW);
      // digitalWrite(IN4, HIGH);
      movement(0, HIGH, 0, HIGH);
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
    } else stop();
  }
}
void movement(int out1 = LOW, int out2 = LOW, int out3 = LOW, int out4 = LOW) {
  digitalWrite(IN1, out1);
  digitalWrite(IN2, out2);
  digitalWrite(IN3, out3);
  digitalWrite(IN4, out4);
}

void speed(char msg) {
  if (typeof(msg) == int) {
    analogWrite(ENA, msg);
    analogWrite(ENB, msg);
  } else {
    analogWrite(ENA, speed);
    analogWrite(ENB, speed);
    analogWrite(C_ENA, speed);
  }
}

void stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  digitalWrite(C_IN1, LOW);
  digitalWrite(C_IN2, LOW);
}

void powerclean(int state = 0) {
  if (state == 1) digitalWrite(C_PC, HIGH);
}
