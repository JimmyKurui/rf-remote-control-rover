
#include <RH_ASK.h>
#include <SPI.h>  // Not actually used but needed to compile

#define UP 8  //Movement
#define RIGHT 4
#define DOWN 7
#define LEFT 2
#define SPEED A0

int upState, downState, leftState, rightState, speedValue;
// RH_ASK driver;
RH_ASK driver(2000, 13, 12, 5);  // ESP8266: do not use pin 11

void setup() {
  Serial.begin(9600);  // Debugging only
  if (!driver.init())
    Serial.println("init failed");
  // Button
  pinMode(UP, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);
  pinMode(SPEED, INPUT);
}

void loop() {
  uint8_t buffer[2];
  char *msg1;
  char *msg2;
  int *msg;

  upState = digitalRead(UP);
  rightState = digitalRead(RIGHT);
  downState = digitalRead(DOWN);
  leftState = digitalRead(LEFT);
  // int states[] = ;
  int states [] = invert( (int[]){ upState, rightState, downState, leftState });
  
  // downState = invert(downState);
  // leftState = invert(leftState);
  // rightState = invert(rightState);

  speedValue = analogRead(SPEED);
  speedValue = map(speedValue, 0, 1023, 0, 249);

  if (upState == 1) {
    msg1 = "Forward";
  }
  if (downState == 1) {
    msg1 = "Reverse";
  }
  if (leftState == 1) {
    msg1 = "Left";
  }
  if (rightState == 1) {
    msg1 = "Right";
  }
  buffer[0] = encoder(msg1, strlen(msg1));
  buffer[1] = speedValue;

  Serial.print("Up: ");
  Serial.println(upState);
  Serial.print("Right ");
  Serial.println(rightState);
  Serial.print("Down: ");
  Serial.println(downState);
  Serial.print("Left: ");
  Serial.println(leftState);
  Serial.print("Pot: ");
  Serial.println(speedValue);
  Serial.print(msg1);
  Serial.println(buffer);  

  Serial.println("\n\n");

  // for(int i=0; i < sizeof(msg); i++) {

  // }
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();
  delay(200);
}

int invert(int states[]) {
  for (int i = 0; i < sizeof(states); i++) {
    if (states[i] == 1) {
      states[i] = 0;
    } else {
      states[i] = 1;
    }
  }
  return states;
}

int* encoder(char *msg, int *msg) {
    for (int i = 0; i < strlen(msg); i++) {
        msg[i] = (int) msg[i];
    }
    return msg;
}

