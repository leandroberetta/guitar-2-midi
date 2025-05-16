/*
 * fft.c
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#include "fft.h"
#include "arm_math.h"

arm_rfft_fast_instance_f32 S;
float32_t hammingWindow[FFT_SIZE];

void initFFT() {
    arm_rfft_fast_init_f32(&S, FFT_SIZE);

    // Generar ventana de Hamming
    for (int i = 0; i < FFT_SIZE; i++) {
        hammingWindow[i] = 0.54f - 0.46f * cosf(2 * PI * i / (FFT_SIZE - 1));
    }
}

void processFFT(const uint16_t *adcBuffer, float *inputSignal, float *fftOutputComplex, float *fftMagnitudes) {
    // Calcular y remover offset DC dinámico
    float32_t mean = 0.0f;
    for (int i = 0; i < FFT_SIZE; i++) {
        mean += (float32_t)adcBuffer[i];
    }
    mean /= FFT_SIZE;

    // Convertir a flotante y aplicar ventana
    for (int i = 0; i < FFT_SIZE; i++) {
        float32_t centered = ((float32_t)adcBuffer[i] - mean) / 2048.0f;
        inputSignal[i] = centered * hammingWindow[i];
    }

    // Calcular FFT real
    arm_rfft_fast_f32(&S, inputSignal, fftOutputComplex, 0);

    // Obtener magnitudes
    arm_cmplx_mag_f32(fftOutputComplex, fftMagnitudes, FFT_SIZE / 2);
}

float findFundamentalFrequency(const float *fftMagnitudes) {
	int binMin = (int)(80.0f * FFT_SIZE / FS);
	int binMax = (int)(5000.0f * FFT_SIZE / FS);

	float maxValue = 0.0f;
	uint32_t maxIndex = 0;

	for (int i = binMin; i < binMax; i++) {
	    if (fftMagnitudes[i] > maxValue) {
	        maxValue = fftMagnitudes[i];
	        maxIndex = i;
	    }
	}

    return (maxIndex * FS) / FFT_SIZE;
}

float calculateEnergy(float *fftOutput, int size) {
    float totalEnergy = 0.0f;

    // Calcular índice mínimo y máximo de interés en frecuencia
    int binMin = (int)(80.0f * FFT_SIZE / FS);      // ~bin de 80 Hz
    int binMax = (int)(5000.0f * FFT_SIZE / FS);    // ~bin de 5 kHz

    if (binMax > size) binMax = size;

    for (int i = binMin; i < binMax; i++) {
        totalEnergy += fftOutput[i] * fftOutput[i];
    }

    return totalEnergy;
}
