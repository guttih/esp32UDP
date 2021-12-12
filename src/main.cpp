#include <Arduino.h>

#include <WiFi.h>
#include <WiFiUdp.h>




void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Starting UDP Server");
}

void loop() {
  static int i = 0;
  delay(1000);
  Serial.println(++i);
  // put your main code here, to run repeatedly:
}