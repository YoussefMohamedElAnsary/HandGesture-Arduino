#include <Arduino.h>
#ifdef __BT_MASTER_TEST__
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(10, 11); // RX | TX

#define ledPin 9

void setup()
{
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);

    Serial.begin(9600);
    BTSerial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop()
{
    BTSerial.write('x');
    delay(100);
}
#endif