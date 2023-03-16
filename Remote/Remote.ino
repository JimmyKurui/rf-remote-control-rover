
#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile
//Movement
#define UP 8
#define RIGHT 4
#define DOWN 7
#define LEFT 2
#define POWER_TX 13
#define SPEED 9
// Lift
#define ASCEND 11
#define DESCEND 13

int upState, downState, leftState, rightState, speedValue, speedState,
  powerState, ascendState, descendState;
// RH_ASK driver;
RH_ASK driver(2000, 13, 12, 5);  // ESP8266: do not use pin 11

void setup() {
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  // Button
  pinMode(UP, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(POWER_TX, INPUT);
  pinMode(SPEED, INPUT);
  pinMode(ASCEND, INPUT);
  pinMode(DESCEND, INPUT);
}

void loop() {
  const char *msg= "";
  // String msg;
  powerState = digitalRead(POWER_TX);
  upState = digitalRead(UP);
  rightState = digitalRead(RIGHT);
  downState = digitalRead(DOWN);
  leftState = digitalRead(LEFT);
  speedState = analogRead(LEFT);
  ascendState = digitalRead(ASCEND);
  descendState = digitalRead(DESCEND);
  // delay(50);
  int potValue = analogRead(SPEED);
  speedValue = map(potValue, 0, 1023, 0, 249);  
  
  if (upState == 1) {
    msg = "Forward";
  }
  if (downState == 1) {
    msg = "Reverse";
  }
  if (leftState == 1) {
    msg = "Left";
  }
  if (rightState == 1) {
    msg = "Right";
  }
  if (ascendState == 1) {
    msg = "Ascend";
  }
  if (descendState == 1) {
    msg = "Descend";
  }
  // msg = "Ascend";                      

  Serial.print("Up: "); Serial.println(upState);
  Serial.print("Right "); Serial.println(rightState);
  Serial.print("Down: "); Serial.println(downState);
  Serial.print("Left: "); Serial.println(leftState);
  Serial.print("Lift: "); Serial.print(ascendState); Serial.println(descendState);
  // for(int i=0; i<= sizeof(msgi++) {
  // Serial.print("Message: ");
  Serial.print(msg);
  // }
  Serial.println("\n\n");

  // for(int i=0; i < sizeof(msg); i++) {
    
  // }
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(200);
}
