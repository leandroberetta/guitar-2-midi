/*
 * fft.c
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#include "fft.h"

arm_rfft_fast_instance_f32 S;
float32_t hammingWindow[FFT_SIZE];

void FFT_Init() {
	arm_rfft_fast_init_f32(&S, FFT_SIZE);

	// Generar ventana de Hamming
	for (int i = 0; i < FFT_SIZE; i++) {
		hammingWindow[i] = 0.54f - 0.46f * cosf(2 * PI * i / (FFT_SIZE - 1));
	}
}

void FFT_Process(const uint16_t *adcBuffer, float32_t *inputSignal,
		float32_t *fftOutputComplex, float32_t *fftMagnitudes) {
	// Calcular y remover offset DC dinámico
	float32_t mean = 0.0f;
	for (int i = 0; i < FFT_SIZE; i++) {
		mean += (float32_t) adcBuffer[i];
	}
	mean /= FFT_SIZE;

	// Convertir a flotante y aplicar ventana
	for (int i = 0; i < FFT_SIZE; i++) {
		float32_t centered = ((float32_t) adcBuffer[i] - mean) / 2048.0f;
		inputSignal[i] = centered * hammingWindow[i];
	}

	// Calcular FFT
	arm_rfft_fast_f32(&S, inputSignal, fftOutputComplex, 0);

	// Obtener magnitudes
	arm_cmplx_mag_f32(fftOutputComplex, fftMagnitudes, FFT_SIZE / 2);
}

float32_t FFT_FindFundamentalFrequency(const float32_t *fftMagnitudes) {
//	int binMin = (int)(80.0f * FFT_SIZE / FS);
//	int binMax = (int)(5000.0f * FFT_SIZE / FS);
//
//	float maxValue = 0.0f;
//	uint32_t maxIndex = 0;
//
//	for (int i = binMin; i < binMax; i++) {
//	    if (fftMagnitudes[i] > maxValue) {
//	        maxValue = fftMagnitudes[i];
//	        maxIndex = i;
//	    }
//	}
//
//  return (maxIndex * FS) / FFT_SIZE;

	float32_t deltaF = FS / ADC_BUFFER_SIZE;

	// Encontrar el pico máximo (ignorando DC)
	int maxBin = 1;
	float maxVal = fftMagnitudes[1];
	for (int i = 2; i < ADC_BUFFER_SIZE / 2; i++) {
		if (fftMagnitudes[i] > maxVal) {
			maxVal = fftMagnitudes[i];
			maxBin = i;
		}
	}

	float32_t fc = maxBin * deltaF;

	// Buscar si hay energía en fc/2 (bin armónico inferior)
	uint8_t subharmonicBin = (uint8_t) ((fc / 2) / deltaF + 0.5f);
	float32_t subharmonicVal = 0;
	if (subharmonicBin > 1 && subharmonicBin < ADC_BUFFER_SIZE / 2) {
		subharmonicVal = fftMagnitudes[subharmonicBin];
	}

	// Si hay suficiente energía en el subarmónico, usar ese como fundamental
	if (subharmonicVal > 0.2f * maxVal) {
		fc = subharmonicBin * deltaF;
	}

	return fc;
}

float32_t FFT_CalculateEnergy(float32_t *fftOutput, uint16_t size) {
	float32_t totalEnergy = 0.0f;

	// Calcular índice mínimo y máximo de interés en frecuencia
	uint16_t binMin = (uint16_t) (80.0f * FFT_SIZE / FS);      // ~bin de 80 Hz
	uint16_t binMax = (uint16_t) (5000.0f * FFT_SIZE / FS);    // ~bin de 5 kHz

	if (binMax > size)
		binMax = size;

	for (int i = binMin; i < binMax; i++) {
		totalEnergy += fftOutput[i] * fftOutput[i];
	}

	return totalEnergy;
}
