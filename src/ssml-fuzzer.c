#include "include/espeak-ng/espeak_ng.h"
#include "include/espeak-ng/encoding.h"
#include "include/espeak-ng/speak_lib.h"

static int initialized = 0;

static int SynthCallback(short *wav, int numsamples, espeak_EVENT *events) {
        (void)wav; // unused
        (void)numsamples; // unused
        (void)events; // unused

        return 0;
}


/* See http://llvm.org/docs/LibFuzzer.html */
extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size);
extern int LLVMFuzzerInitialize(const int* argc, char*** argv);

char *filepath = NULL;

extern int LLVMFuzzerInitialize(const int* argc, char*** argv)
{
        (void)argc; // unused
        filepath = dirname(strdup((*argv)[0]));
        return 0;
}

extern int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
        if (!initialized) {
                const char *hasDataPath = getenv("ESPEAK_DATA_PATH");
                if (!hasDataPath) {
                        setenv("ESPEAK_DATA_PATH",filepath,0);
                }
                espeak_Initialize(AUDIO_OUTPUT_SYNCHRONOUS, 0, NULL, 0);
                espeak_SetSynthCallback(SynthCallback);
                initialized = 1;
        }

        int synth_flags = espeakCHARS_UTF8 | espeakPHONEMES | espeakSSML;
       char *str = malloc(size+1);
       memcpy(str, data, size);
       str[size] = 0;
       espeak_Synth((char*) str, size + 1, 0, POS_CHARACTER, 0,
                     synth_flags, NULL, NULL);
       free(str);

        return 0;
}

