#include <Arduino.h>

#ifdef __BT_CONFIG__
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

void setup()
{
    pinMode(9, OUTPUT); // this pin will pull the HC-05 pin 34 (key pin) HIGH to switch module to AT mode
    digitalWrite(9, HIGH);
    Serial.begin(38400);
    Serial.println("Enter AT commands:");
    BTSerial.begin(38400); // HC-05 default speed in AT command more
}

void loop()
{
    if (BTSerial.available())
    {
        Serial.write(BTSerial.read());
    }

    if (Serial.available())
    {
        BTSerial.write(Serial.read());
    }
}
#endif