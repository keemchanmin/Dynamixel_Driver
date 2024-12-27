#ifndef __DXL_H__
#define __DXL_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct 
{
    void (*setDirTx)(void); 
    void (*setDirRx)(void); 
    void (*uartWrite)(uint8_t *data, uint8_t length); 
    uint8_t (*uartRead)(void); 
    uint8_t (*uartAvailable)(void); 
} DynamixelDriver;


void Dynamixel_Init(DynamixelDriver *driver);
void Dynamixel_SetGoalPosition(uint8_t id, uint16_t position);
void Dynamixel_SetMovingSpeed(uint8_t id, uint16_t speed);
uint16_t Dynamixel_GetPresentPosition(uint8_t id);

#endif 
