/*
 * logic.c
 *
 *  Created on: May 23, 2025
 *      Author: lberetta
 */

#include "stm32f4xx_hal.h"
#include "logic.h"
#include "fft.h"
#include "midi.h"
#include "oled.h"

State state = IDLE_STATE;

uint8_t currentNote = 0;
uint8_t lastVelocity = 0;

void Logic_HandleFrequency(float frequency, float energy) {
	if (energy > ENERGY_THRESHOLD) {
		uint8_t velocity = MIDI_EnergyToVelocity(energy);
		uint8_t midiNote = MIDI_FrequencyToMIDINote(frequency);

		if (midiNote != INVALID_MIDI_NOTE) {
			switch (state) {
			case IDLE_STATE:
				if (velocity > 10) {
					MIDI_SendNoteOn(midiNote, velocity);
					OLED_DrawMidiMessage(midiNote, velocity);

					currentNote = midiNote;
					state = NOTE_PRESENT_STATE;
				}

				break;
			case NOTE_PRESENT_STATE:
				if (velocity > 10) {
					if (midiNote != currentNote || velocity >= lastVelocity) {
						MIDI_SendNoteOff(currentNote);
						HAL_Delay(3);
						MIDI_SendNoteOn(midiNote, velocity);
						OLED_DrawMidiMessage(midiNote, velocity);

						lastVelocity = velocity;
						currentNote = midiNote;
					}
				}
				break;
			}
		}
	} else {
		if (state == NOTE_PRESENT_STATE) {
			MIDI_SendNoteOff(currentNote);
			OLED_FillScreen(0x00);

			state = IDLE_STATE;
		}
	}
}
