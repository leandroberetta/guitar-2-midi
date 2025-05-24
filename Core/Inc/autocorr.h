/*
 * autocorr.h
 *
 *  Created on: May 23, 2025
 *      Author: lberetta
 */

#ifndef INC_AUTOCORR_H_
#define INC_AUTOCORR_H_

#include <stdint.h>
#include <math.h>
#include <float.h>

#define SAMPLE_RATE     21340.0f
#define BUFFER_SIZE     256
#define MIN_FREQ        80.0f
#define MAX_FREQ        1000.0f

#define MIN_LAG   (int)(SAMPLE_RATE / MAX_FREQ)  // 24
#define MAX_LAG   (int)(SAMPLE_RATE / MIN_FREQ)  // 300

typedef struct {
    float frequency;
    float energy;
} FreqResult;

void ConvertADCToFloat(const uint16_t *adcBuffer, float *floatBuffer, int length);
FreqResult Autocorrelation_FindFundamentalFrequency(const uint16_t *adcBuffer);

#endif /* INC_AUTOCORR_H_ */
