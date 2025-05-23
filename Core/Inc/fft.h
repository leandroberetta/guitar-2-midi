/*
 * fft.h
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#ifndef SRC_FFT_H
#define SRC_FFT_H

#include <stdint.h>

#define ADC_BUFFER_SIZE 4096
#define FFT_SIZE 4096
#define FS 21340.0f
#define ENERGY_THRESHOLD 50.0f

void FFT_Init(void);
void FFT_Process(const uint16_t *adcBuffer, float *inputSignal, float *fftOutputComplex, float *fftMagnitudes);
float FFT_FindFundamentalFrequency(const float *fftMagnitudes);
float FFT_CalculateEnergy(float *fftMagnitudes, int size);

#endif /* SRC_FFT_H_ */
