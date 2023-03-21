#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);
  if (!rf_driver.init()) {
    Serial.println("RF driver failed to initialize!");
  }
}

void loop() {
  const char* messages[2] = {"Hello", "World"};
  uint8_t message_lengths[2] = {strlen(messages[0]), strlen(messages[1])};
  uint8_t total_length = message_lengths[0] + message_lengths[1];
  
  uint8_t message[total_length];
  memcpy(message, messages[0], message_lengths[0]);
  memcpy(message + message_lengths[0], messages[1], message_lengths[1]);
  
  rf_driver.send(message, total_length);
  rf_driver.waitPacketSent();
  
  Serial.println("Messages sent!");
  delay(1000);
}

// ======================== Receiver ======================
#include <RH_ASK.h>
#include <SPI.h>

RH_ASK rf_driver;

void setup() {
  Serial.begin(9600);
  if (!rf_driver.init()) {
    Serial.println("RF driver failed to initialize!");
  }
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  
  if (rf_driver.recv(buf, &len)) {
    Serial.print("Received messages: ");
    Serial.print((char*)buf);
    Serial.print(" ");
    Serial.println((char*)(buf + strlen((char*)buf) + 1));
  }
}



