/*
 * midi.h
 *
 *  Created on: May 16, 2025
 *      Author: lberetta
 */

#ifndef SRC_MIDI_H_
#define SRC_MIDI_H_

#include <stdint.h>

#define FREQ_MIN 82.0f
#define FREQ_MAX 4200.0f
#define MIN_MIDI_NOTE 40
#define MAX_MIDI_NOTE 108
#define INVALID_MIDI_NOTE 255

void MIDI_SendNoteOn(uint8_t note, uint8_t velocity);
void MIDI_SendNoteOff(uint8_t note);
uint8_t MIDI_EnergyToVelocity(float energy);
uint8_t MIDI_FrequencyToMIDINote(float frequency);
void MIDI_MidiNoteToString(uint8_t midiNote, char *out);


#endif /* SRC_MIDI_H_ */
