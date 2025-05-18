
#ifndef __OLED_H__
#define __OLED_H__

#include "stm32f4xx_hal.h"

#define OLED_ADDRESS (0x3C << 1)

void OLED_Init(I2C_HandleTypeDef *hi2c);
void OLED_FillScreen(uint8_t pattern);
void OLED_DrawChar(uint8_t x, uint8_t page, char c);
void OLED_DrawString(uint8_t x, uint8_t page, const char* str);
void OLED_DrawMidiMessage(uint8_t note, uint8_t velocity);

#endif // __OLED_H__
