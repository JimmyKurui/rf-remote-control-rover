// #include <VirtualWire.h>
#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile

RH_ASK driver(2000, 12, 13, 5);  // ESP8266: do not use pin 11

int in1 = 3;
int in2 = 5;
int in3 = 6;
int in4 = 9;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);  // For debugging only
  if (!driver.init())
    Serial.println("init failed");
    
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(9, LOW);
  digitalWrite(in3, LOW);
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  // Serial.println(buf);

    // driver.printBuffer("Got:", buf, buflen);

  if (driver.recv(buf, &buflen)) {  // Non-blocking
    Serial.print("Received: ");
    String msg;
    for (int i = 0; i < buflen; i++) {
      msg += (char)buf[i];
    }
    Serial.println(msg);

    if (buf[0] == '1') {
      digitalWrite(in1, HIGH);
    } else if (buf[0] == '0') {
      digitalWrite(in1, 0);
    }
    if (buf[0] == 'A') {
      digitalWrite(in2, HIGH);
    } else if (buf[0] == 'a') {
      digitalWrite(in2, 0);
    }
    if (buf[0] == 'B') {
      digitalWrite(in3, HIGH);
    } else if (buf[0] == 'b') {
      digitalWrite(in3, 0);
    }

    if (buf[0] == 'D') {
      digitalWrite(in4, HIGH);
    } else if (buf[0] == 'd') {
      digitalWrite(in4, LOW);
    }
  }
}
