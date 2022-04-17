/*
 * Copyright (C) 2018 Sascha Brawer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write see:
 *             <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <espeak-ng/espeak_ng.h>

/***** CONFIG *****/
#define ESPEAK_DATA_PATH	"/usr/lib/x86_64-linux-gnu/espeak-ng-data/"

#define BOLDRED(x)	"\x1b[31m\x1b[1m" x "\x1b[0m"

static int initialized = 0;

static int SynthCallback(short *wav, int numsamples, espeak_EVENT *events) {
	(void)wav; // unused
	(void)numsamples; // unused
	(void)events; // unused

	return 0;
}

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
	if (!initialized) {
		const char *hasDataPath = getenv("ESPEAK_DATA_PATH");
		if (!hasDataPath) {
			setenv("ESPEAK_DATA_PATH",ESPEAK_DATA_PATH,0);
		}
		espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, NULL, 0);
		const char *lang = getenv("FUZZ_LANG");
		if (lang == NULL)
		{
			fprintf(stderr, "\n" BOLDRED("[Please set up FUZZ_LANG env var before starting fuzzer]")"\n\n"));
			exit(1);
		}
        espeak_SetVoiceByName(lang);
		initialized = 1;
		fprintf(stderr, "LANGUAGE FUZZED = %s\n", lang);

	}

	char *str = malloc(size+1);
	memcpy(str, data, size);
	str[size] = 0;
	int synth_flags = espeakCHARS_AUTO ;
    espeak_Synth((char*) str, size+1, 0, POS_CHARACTER, 0,
                synth_flags, NULL, NULL);
    free(str);


	return 0; 	
}
