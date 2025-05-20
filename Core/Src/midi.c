/*
 * midi.c
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#include <math.h>
#include "midi.h"
#include "usbd_core.h"

extern USBD_HandleTypeDef hUsbDeviceFS;

int frequencyToMIDINote(float frequency) {
	if (frequency < FREQ_MIN || frequency > FREQ_MAX) {
		return -1;  // Frecuencia fuera de rango
	}

	// Calcular la nota MIDI con la fórmula optimizada
	int midiNote = (int) (69 + 12 * log2f(frequency / 440.0f) + 0.5f); // Redondear al entero más cercano

	// Asegurarse de que la nota MIDI esté dentro del rango esperado
	if (midiNote < MIN_MIDI_NOTE || midiNote > MAX_MIDI_NOTE) {
		return -1;  // Nota MIDI no válida en este contexto
	}

	return midiNote;
}

void sendNoteOn(uint8_t note, uint8_t velocity) {
    uint8_t buffer[4] = {
        0x09,          // Cable 0, CIN = 9 (Note On)
        0x90,          // Status: Note On, Channel 0 (0x90 | 0)
        note,          // Note number
        velocity       // Velocity
    };

    while (USBD_LL_Transmit(&hUsbDeviceFS, 0x81, buffer, 4) != USBD_OK) {
        // Espera activa hasta que el endpoint esté libre
    }
}

void sendNoteOff(uint8_t note) {
    uint8_t buffer[4] = {
        0x08,     // Cable 0, CIN = 8 (Note Off)
        0x80,     // Status: Note Off, Channel 0 (0x80 | 0)
        note,     // Note number
        0         // Velocity 0
    };

    while (USBD_LL_Transmit(&hUsbDeviceFS, 0x81, buffer, 4) != USBD_OK) {
        // Espera activa hasta que el endpoint esté libre
    }}

uint8_t energyToVelocity(float energy) {
    const float ENERGY_MIN = 750.0f;
    const float ENERGY_MAX = 2000.0f;

    if (energy < ENERGY_MIN) return 1;
    if (energy > ENERGY_MAX) energy = ENERGY_MAX;

    uint8_t velocity = (uint8_t)(energy * 127.0f / ENERGY_MAX + 0.5f);

    return (uint8_t)velocity;
}
