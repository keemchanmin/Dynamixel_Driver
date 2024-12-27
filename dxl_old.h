#ifndef __DXL_OLD_H__
#define __DXL_OLD_H__

#include <stdint.h>
#include <stdbool.h>


#define DIRECTION_PIN 2


void Dynamixel_Init(void);
void Dynamixel_SetGoalPosition(uint8_t id, uint16_t position);
void Dynamixel_SetMovingSpeed(uint8_t id, uint16_t speed);
uint16_t Dynamixel_GetPresentPosition(uint8_t id);

#endif 
