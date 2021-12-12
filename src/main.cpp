#include <Arduino.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include "json.h"

#include "config.h"

WiFiUDP udp;

int rp;

#define BUFFERSIZE 3
char pktbuf[BUFFERSIZE+1]; //buffer to store udp data +1 to add the end-of-string marker '\0'
int didReadLength;
char rx_val;
String message;

void connectToWifi()
{
    WiFi.hostname(gHostName);
    WiFi.begin(getSSIDName(), getSSIDPassword());
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("Connection failed! rebooting...");
        ESP.restart();
    }

    Serial.println(String("Status: Connected. IP Address: ") + WiFi.localIP().toString());
    udp.begin(gUdpPort);
    Serial.println(String("Opening UDP port at: ") + gUdpPort);
}

void setup()
{
    Serial.begin(115200);
    delay(1000);
    Serial.println("Starting UDP Server");
    Serial.println("Connecting to wifi");
    connectToWifi();
}



void loop()
{
    rp = udp.parsePacket();
    if (!rp)
    {
        if (Serial.available() > 0)
        {
            rx_val = Serial.read();
            Serial.print("udp_send: ");
            Serial.println(rx_val);
            // udp.beginPacket(udpAddress, udpPort);
            // udp.write(rx_val);
             udp.endPacket();
        }
    }
    else
    {
        message = "";
        while (udp.available())
        {
            didReadLength = udp.read(pktbuf, BUFFERSIZE);
            // Serial.println();Serial.print(didReadLength);
            while (didReadLength > 0)
            {
                //Serial.print(", ");Serial.print(didReadLength);
                // pktbuf[BUFFERSIZE]='\0';
                for (int i = 0; i < didReadLength; i++)
                {
                    message += pktbuf[i];
                }
                didReadLength = udp.read(pktbuf, BUFFERSIZE);
            }
        }
        if ((int)message.charAt(message.length()-1) == 10) {
            //the last red buffer filled completely so LF will be the last char red, which should not be part of the message.
            message.remove(message.length()-1);
        }
        Json jsonMessage(message.c_str() );
        if (jsonMessage.isValid()) {
            Serial.println(jsonMessage.toTree());
        } else {
            Serial.println("\nMessage is not a valid JSON message.");
        }
        Serial.print("----- Message begin -----\n\"");Serial.print(message);Serial.print("\"\n----- Message endof -----\n");
        
    }
}