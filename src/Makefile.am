AUTOMAKE_OPTIONS = subdir-objects
bin_PROGRAMS = hello_digitalbox
include_HEADERS = util.h hello.h include/espeak-ng/espeak_ng.h include/espeak-ng/speak_lib.h
hello_digitalbox_SOURCES = util.c  ssml-fuzzer.c
hello_digitalbox_LDADD = libespeak-ng.la
hello_digitalbox_CFLAGS= -fsanitize=fuzzer  ${AM_CFLAGS}
hello_digitalbox_LDFLAGS= -fsanitize=fuzzer -static -lm ${PCAUDIOLIB_LIBS}

