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
#define ENERGY_THRESHOLD 800.0f

void sendNoteOn(uint8_t note, uint8_t velocity);
void sendNoteOff(uint8_t note);
uint8_t energyToVelocity(float energy);
int frequencyToMIDINote(float frequency);

#endif /* SRC_MIDI_H_ */
