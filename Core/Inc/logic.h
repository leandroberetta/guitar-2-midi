/*
 * logic.h
 *
 *  Created on: May 23, 2025
 *      Author: lberetta
 */

#ifndef INC_LOGIC_H_
#define INC_LOGIC_H_

#include "arm_math.h"

#define SAME_NOTE_THRESHOLD 1.2f

typedef enum {
	IDLE_STATE,
	NOTE_PRESENT_STATE
} State;

void Logic_HandleFrequency(float32_t frequency, float32_t energy);

#endif /* INC_LOGIC_H_ */
