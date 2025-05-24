	/*
 * autocorr.c
 *
 *  Created on: May 23, 2025
 *      Author: lberetta
 */

#include "autocorr.h"

static float floatBuffer[BUFFER_SIZE];

void ConvertADCToFloat(const uint16_t *adcBuffer, float *floatBuffer, int length) {
    float mean = 0.0f;

    // Calcular la media
    for (int i = 0; i < length; i++) {
        mean += (float)adcBuffer[i];
    }
    mean /= (float)length;

    // Restar la media para centrar en cero
    for (int i = 0; i < length; i++) {
        floatBuffer[i] = (float)adcBuffer[i] - mean;
    }
}

float CalculateEnergy(const float *buffer, int length) {
    float energy = 0.0f;
    for (int i = 0; i < length; i++) {
        energy += buffer[i] * buffer[i];
    }
    return energy;
}

FreqResult Autocorrelation_FindFundamentalFrequency(const uint16_t *adcBuffer) {
	FreqResult result = { .frequency = -1.0f, .energy = 0.0f };

    ConvertADCToFloat(adcBuffer, floatBuffer, BUFFER_SIZE);

    result.energy = CalculateEnergy(floatBuffer, BUFFER_SIZE);

    const float ENERGY_THRESHOLD = 200000.0f;
    if (result.energy < ENERGY_THRESHOLD) {
        return result;  // energía insuficiente, frecuencia inválida
    }

    float maxCorr = -FLT_MAX;
    int bestLag = -1;

    for (int lag = MIN_LAG; lag <= MAX_LAG; lag++) {
        float sum = 0.0f;
        for (int i = 0; i < BUFFER_SIZE - lag; i++) {
            sum += floatBuffer[i] * floatBuffer[i + lag];
        }

        if (sum > maxCorr) {
            maxCorr = sum;
            bestLag = lag;
        }
    }
    if (bestLag * 2 <= MAX_LAG) {
        if (floatBuffer[bestLag * 2] > 0.8f * floatBuffer[bestLag]) {
            bestLag = bestLag * 2;
        }
    }

    if (bestLag > 0) {
        result.frequency = SAMPLE_RATE / bestLag;
    }

    return result;
}

