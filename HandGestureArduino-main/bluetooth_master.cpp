#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#ifdef __BT_MASTER__
SoftwareSerial BTSerial(10, 11); // RX | TX

const int MPU_addr = 0x68;

float x, y, z; // store accelerometer data

/*
0: still
1: back
2: front
3: right
4: left
5: forward-right
6: forward-left
7: backward-left
8: backward-right
*/
int state = 0;

void get_accel(int16_t &AcX, int16_t &AcY, int16_t &AcZ);
void init_sensor();

void setup()
{
    while (!Serial)
        ;
    pinMode(9, OUTPUT);
    digitalWrite(9, HIGH);

    Serial.begin(9600);
    BTSerial.begin(9600);
    Serial.println("Started");

    Wire.begin();  // initialize i2c
    init_sensor(); // initialize mpu
}

void loop()
{
    int16_t xi, yi, zi;
    get_accel(xi, yi, zi);

    // filtering
    x = 0.99 * x + 0.01 * float(xi);
    y = 0.99 * y + 0.01 * float(yi);
    z = 0.99 * z + 0.01 * float(zi);

    // calculate roll and pitch
    float Roll = atan2(y, z) * 180.0 / PI;
    float Pitch = atan2(x, sqrt(y * y + z * z)) * 180.0 / PI;

    // get ranges.
    if (((Roll > -10 && Roll < 10) && (Pitch > -10 && Pitch < 10)))
        state = 0;
    else if ((Roll > -100 && Roll < 10) && (Pitch > -10 && Pitch < 10))
        state = 1;
    else if ((Roll > 10 && Roll < 100) && (Pitch > -10 && Pitch < 10))
        state = 2;
    else if ((Roll > -10 && Roll < 10) && (Pitch > 10 && Pitch < 100))
        state = 3;
    else if ((Roll > -10 && Roll < 10) && (Pitch > -100 && Pitch < 10))
        state = 4;
    else if ((Roll > 10 && Roll < 100) && (Pitch > 10 && Pitch < 50))
        state = 5;
    else if ((Roll > 10 && Roll < 100) && (Pitch > -50 && Pitch < 10))
        state = 6;
    else if ((Roll > -100 && Roll < 10) && (Pitch > -50 && Pitch < 10))
        state = 7;
    else if ((Roll > -100 && Roll < 10) && (Pitch > 10 && Pitch < 50))
        state = 8;

    // Serial.print(Roll);
    // Serial.print(", ");
    // Serial.println(Pitch);

    // replace print statements w communication send.
    switch (state)
    {
    case 0:
        Serial.println("still");
        break;
    case 1:
        Serial.println("back");
        break;
    case 2:
        Serial.println("front");
        break;
    case 3:
        Serial.println("right");
        break;
    case 4:
        Serial.println("left");
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

    BTSerial.write(state);
}

// begin communication with mpu
void init_sensor()
{
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission();
}

// get acceleration from mpu
void get_accel(int16_t &AcX, int16_t &AcY, int16_t &AcZ)
{
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission();
    Wire.requestFrom(MPU_addr, 6);
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
}
#endif // __BT_MASTER__