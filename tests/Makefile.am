AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = ssml_fuzzer my_fuzzer
include_HEADERS = ../src/include/espeak-ng/espeak_ng.h ../src/include/espeak-ng/speak_lib.h
ssml_fuzzer_SOURCES =  ssml-fuzzer.c 
ssml_fuzzer_LDADD = ../src/libespeak-ng.la
ssml_fuzzer_CFLAGS= -fsanitize=address,fuzzer  ${AM_CFLAGS}
ssml_fuzzer_LDFLAGS= -fsanitize=fuzzer -static -lm ${PCAUDIOLIB_LIBS}
my_fuzzer_SOURCES =  my_fuzzer.c 
my_fuzzer_LDADD = ../src/libespeak-ng.la
my_fuzzerr_CFLAGS= -fsanitize=address,fuzzer -O2 -fno-omit-frame-pointer -g -fsanitize-coverage=edge,trace-pc-guard,indirect-calls,trace-cmp,trace-div,trace-gep  ${AM_CFLAGS}
my_fuzzer_LDFLAGS= -fsanitize=address,fuzzer -static -lm  -fsanitize-coverage=edge,trace-pc-guard,indirect-calls,trace-cmp,trace-div,trace-gep  ${PCAUDIOLIB_LIBS}

