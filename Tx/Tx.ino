#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile

// RH_ASK driver;
RH_ASK driver(2000, 13, 12, 5);  // ESP8266: do not use pin 11

const char *msg = "On";
int up = 2;
int down = 3;
int left = 4;
int right = 5;
int state, state3, state2, state4 = 0;
int LED = 14;

void setup() {
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);  // For debugging only
  if (!driver.init())
    Serial.println("init failed");
  // vw_set_ptt_inverted(true);
  // vw_set_tx_pin(12);
  // vw_setup(4000);
}

void loop() {
  state = digitalRead(up);
  state2 = digitalRead(down);
  state3 = digitalRead(left);
  state4 = digitalRead(right);
  Serial.print("Sent: ");
  Serial.println(state);
  Serial.println(state2);
  Serial.println(state3);
  Serial.println(state4);
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
    
  if (state == HIGH) {
    msg = "UP";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, LOW);
  } else {
    msg = "up";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, HIGH);
  }
  if (state2 == HIGH) {
    msg = "DOWN";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, LOW);
  } else {
    msg = "down";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, HIGH);
  }
  if (state3 == HIGH) {
    msg = "LEFT";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, LOW);
  } else {
    msg = "left";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, HIGH);
  }
  if (state4 == HIGH) {
    msg = "RIGHT";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, HIGH);
  } else {
    msg = "right";
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    digitalWrite(LED, LOW);
  }
}
