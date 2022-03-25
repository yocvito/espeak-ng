#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include <espeak-ng/espeak_ng.h>
#include <espeak-ng/speak_lib.h>

#define DICT_NAME       "fuzzdict"

extern int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
    // write fuzzer input to file (file argument to function)
    char path[PATH_MAX] = { 0 };
    snprintf(path, sizeof path, "%s_rules.txt", DICT_NAME);

    int fd  = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        exit(1);
    }
    write(fd, Data, Size);
    close(fd);

    espeak_ng_ERROR_CONTEXT context = NULL;
    espeak_ng_CompileDictionary("./", DICT_NAME, NULL, 0x1, &context);
    return 0;
}