/*
 * midi.h
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#ifndef SRC_MIDI_H_
#define SRC_MIDI_H_

#include <stdint.h>
#include "arm_math.h"
#include "fft.h"

#define MIDI_NOTE_MIN 40
#define MIDI_NOTE_MAX 86
#define INVALID_MIDI_NOTE 255

void MIDI_SendNoteOn(uint8_t note, uint8_t velocity);
void MIDI_SendNoteOff(uint8_t note);
uint8_t MIDI_EnergyToVelocity(float32_t energy);
uint8_t MIDI_FrequencyToMIDINote(float32_t frequency);
void MIDI_MidiNoteToString(uint8_t midiNote, char *out);


#endif /* SRC_MIDI_H_ */
