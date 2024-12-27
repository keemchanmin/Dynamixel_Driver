#include "dxl.h"


static void Dynamixel_SendPacket(DynamixelDriver *driver, const uint8_t *packet, uint8_t length) 
{
    driver->setDirTx();         
    driver->uartWrite((uint8_t *)packet, length); 
    driver->setDirRx();        
}


void Dynamixel_SetGoalPosition(DynamixelDriver *driver, uint8_t id, uint16_t position) 
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

    Dynamixel_SendPacket(driver, packet, 9);
}


void Dynamixel_SetMovingSpeed(DynamixelDriver *driver, uint8_t id, uint16_t speed) 
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

    Dynamixel_SendPacket(driver, packet, 9);
}


uint16_t Dynamixel_GetPresentPosition(DynamixelDriver *driver, uint8_t id) 
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

    Dynamixel_SendPacket(driver, packet, 8);

    for (int i = 0; i < 10; i++) 
    {
        if (driver->uartAvailable() >= 8) 
        {
            uint8_t response[8];
            for (int j = 0; j < 8; j++) 
            {
                response[j] = driver->uartRead();
            }

            position = response[5] | (response[6] << 8);
            break;
        }
    }

    return position;
}

