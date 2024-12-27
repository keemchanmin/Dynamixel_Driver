#include "dxl.h"

#define DIRECTION_PIN 2

void setTxMode() 
{
    digitalWrite(DIRECTION_PIN, HIGH);
    delay(1);
}

void setRxMode() 
{
    digitalWrite(DIRECTION_PIN, LOW);
    delay(1);
}

void uartWrite(uint8_t *data, uint8_t length)
 {
    Serial2.write(data, length);
}

uint8_t uartRead()
 {
    while (!Serial2.available());
    
    return Serial2.read();
}

uint8_t uartAvailable() 
{
    return Serial2.available();
}

DynamixelDriver dxl = { setTxMode, setRxMode,uartWrite,uartRead, uartAvailable };

void setup() 
{
    pinMode(DIRECTION_PIN, OUTPUT);
    Serial2.begin(115200);
    
    Dynamixel_Init(&dxl);
    Dynamixel_SetGoalPosition(&dxl, 1, 512);
    Dynamixel_SetMovingSpeed(&dxl, 1, 100); 
}

void loop()
 {
    Serial.println(Dynamixel_GetPresentPosition(&dxl, 1);); 
    delay(1000);
}
