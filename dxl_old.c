#include "dxl_old.h"
#include "Arduino.h"

static void setTxMode() 
{
    digitalWrite(DIRECTION_PIN, HIGH);
    delay(1);
}

static void setRxMode() 
{
    digitalWrite(DIRECTION_PIN, LOW);
    delay(1);
}

static void sendPacket(const uint8_t *packet, uint8_t length) 
{
    setTxMode();
    Serial2.write(packet, length);
    Serial2.flush();
    setRxMode();
}

void Dynamixel_Init(void) 
{
    pinMode(DIRECTION_PIN, OUTPUT);
    Serial2.begin(57600);
    setRxMode();
}


void Dynamixel_SetGoalPosition(uint8_t id, uint16_t position) 
{
    uint8_t packet[9];
    uint8_t positionL = position & 0xFF;
    uint8_t positionH = (position >> 8) & 0xFF;

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = id;
    packet[3] = 5; 
    packet[4] = 0x03; 
    packet[5] = 0x1E; 
    packet[6] = positionL;
    packet[7] = positionH;
    packet[8] = ~(id + 5 + 0x03 + 0x1E + positionL + positionH) & 0xFF; 

    sendPacket(packet, 9);
}


void Dynamixel_SetMovingSpeed(uint8_t id, uint16_t speed) 
{
    uint8_t packet[9];
    uint8_t speedL = speed & 0xFF;
    uint8_t speedH = (speed >> 8) & 0xFF;

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = id;
    packet[3] = 5; 
    packet[4] = 0x03; 
    packet[5] = 0x20; 
    packet[6] = speedL;
    packet[7] = speedH;
    packet[8] = ~(id + 5 + 0x03 + 0x20 + speedL + speedH) & 0xFF; 

    sendPacket(packet, 9);
}


uint16_t Dynamixel_GetPresentPosition(uint8_t id) 
{
    uint8_t packet[8];
    uint16_t position = 0;

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = id;
    packet[3] = 4; 
    packet[4] = 0x02; 
    packet[5] = 0x24; 
    packet[6] = 2; 
    packet[7] = ~(id + 4 + 0x02 + 0x24 + 2) & 0xFF; 

    sendPacket(packet, 8);

    delay(10); 
    if (Serial2.available() >= 8) 
    {
        uint8_t response[8];
        for (int i = 0; i < 8; i++) 
        {
            response[i] = Serial2.read();
        }

        position = response[5] | (response[6] << 8);
    }

    return position;
}


void Dynamixel_OnOffTorque(uint8_t id, bool state)
{
    uint8_t packet[8];

    packet[0] = 0xFF;
    packet[1] = 0xFF;
    packet[2] = id;
    packet[3] = 4; 
    packet[4] = 0x03; 
    packet[5] = 0x18; 
    packet[6] = state ? 1 : 0;
    packet[7] = ~(id + 4 + 0x03 + 0x18 + (state ? 1 : 0)) & 0xFF; 

    sendPacket(packet, 8);
}
