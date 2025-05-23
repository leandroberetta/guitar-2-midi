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

const char *noteNames[] = { "C", "C#", "D", "D#", "E", "F",
                            "F#", "G", "G#", "A", "A#", "B" };

void MIDI_MidiNoteToString(uint8_t midiNote, char *out) {
    if (midiNote > 127) {
        strcpy(out, "-");
        return;
    }
    int note = midiNote % 12;
    int octave = (midiNote / 12) - 1;
    sprintf(out, "%s%d", noteNames[note], octave);
}

uint8_t MIDI_FrequencyToMIDINote(float frequency) {
    if (frequency < 20.0f || frequency > 2000.0f) return INVALID_MIDI_NOTE;

    int midiNote = (int)(69 + 12 * log2f(frequency / 440.0f) + 0.5f);
    if (midiNote < 21 || midiNote > 108) return INVALID_MIDI_NOTE;

    return (uint8_t)midiNote;
}

void MIDI_SendNoteOn(uint8_t note, uint8_t velocity) {
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

void MIDI_SendNoteOff(uint8_t note) {
    uint8_t buffer[4] = {
        0x08,     // Cable 0, CIN = 8 (Note Off)
        0x80,     // Status: Note Off, Channel 0 (0x80 | 0)
        note,     // Note number
        0         // Velocity 0
    };

    while (USBD_LL_Transmit(&hUsbDeviceFS, 0x81, buffer, 4) != USBD_OK) {
        // Espera activa hasta que el endpoint esté libre
    }}

uint8_t MIDI_EnergyToVelocity(float energy) {
    const float ENERGY_MIN = 50.0f;
    const float ENERGY_MAX = 4000.0f;

    if (energy < ENERGY_MIN) return 1;
    if (energy > ENERGY_MAX) energy = ENERGY_MAX;

    uint8_t velocity = 1;
    if (energy < ENERGY_MIN) velocity = 1;
    else {
        float norm = (energy - ENERGY_MIN) / (ENERGY_MAX - ENERGY_MIN);
        if (norm > 1.0f) norm = 1.0f;
        velocity = (uint8_t)(sqrtf(norm) * 127.0f + 0.5f);
    }

    return (uint8_t)velocity;
}
