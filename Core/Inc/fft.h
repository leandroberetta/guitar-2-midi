/*
 * fft.h
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#ifndef SRC_FFT_H
#define SRC_FFT_H

#include <stdint.h>
#include "arm_math.h"

#define FFT_SIZE 1024
#define ADC_BUFFER_SIZE FFT_SIZE
#define FS 21340.0f
#define ENERGY_THRESHOLD 1.0f
#define ENERGY_MAX 1000.0f

void FFT_Init(void);
void FFT_Process(const uint16_t *adcBuffer, float32_t *inputSignal, float32_t *fftOutputComplex, float32_t *fftMagnitudes);
float32_t FFT_FindFundamentalFrequency(const float32_t *fftMagnitudes);
float32_t FFT_CalculateEnergy(float32_t *fftMagnitudes, uint16_t size);

#endif /* SRC_FFT_H_ */
