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

void initFFT(void);
void processFFT(const uint16_t *adcBuffer, float *inputSignal, float *fftOutputComplex, float *fftMagnitudes);
float findFundamentalFrequency(const float *fftMagnitudes);
float calculateEnergy(float *fftMagnitudes, int size);

#endif /* SRC_FFT_H_ */
