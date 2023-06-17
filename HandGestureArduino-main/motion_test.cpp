#include <Arduino.h>
#include <motion.hpp>
#ifdef __MOTION_TEST__
void setup()
{
    _motor_init();
}

void loop()
{
    forward();
    delay(5000);
    stop();
    delay(5000);
    right();
    delay(5000);
    left();
    delay(5000);
}
#endif