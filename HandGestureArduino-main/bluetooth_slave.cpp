#include <Arduino.h>
#ifdef __BT_SLAVE__
#include <SoftwareSerial.h>
#define MOTION_H_IMPLEMENTATION
#include "motion.hpp"

SoftwareSerial BTSerial(10, 11); // RX | TX

// Slave Address: 98D3,36,F5AA76
unsigned long long currentMillis = millis();
unsigned long long prevMillis = 0;
bool led_state = 0;

int x;

void _flash_led(const unsigned int interval);

void setup()
{
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);
    _motor_init();
    Serial.begin(9600);
    BTSerial.begin(9600);
}

void loop()
{
    if (BTSerial.available() > 0)
    {
        x = BTSerial.read();

        switch (x)
        {
        case 0:
            Serial.println("still");
            stop();
            break;
        case 1:
            Serial.println("back");
            backward();
            break;
        case 2:
            Serial.println("front");
            forward();
            break;
        case 3:
            Serial.println("right");
            right();
            break;
        case 4:
            Serial.println("left");
            left();
            break;
        case 5:
            Serial.println("forward right");
            break;
        case 6:
            Serial.println("forward left");
            break;
        case 7:
            Serial.println("back left");
            break;
        case 8:
            Serial.println("back right");
            break;
        default:
            break;
        }
    }
}

void _flash_led(const unsigned int interval)
{
    currentMillis = millis();
    if (currentMillis - prevMillis >= interval)
    {
        prevMillis = currentMillis;
        digitalWrite(LED_BUILTIN, led_state);
        led_state = !led_state;
    }
}
#endif