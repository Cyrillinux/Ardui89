/*
 * DISLCAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef WEXITSTATUS
#ifdef MINGW32
#define WEXITSTATUS(w) (((w) & 0xC0000000) == 0)
#else
#define WEXITSTATUS(w) (((w) >> 8) & 0377)
#endif
#endif

int main(int argc, char **argv) {
    char cmdbuffer[4096];
    char sdccpath[4096];
    int err;
    sprintf((char *) sdccpath,"%s",dirname(argv[0]));
    // test
    if (argc<2) {
        printf("\nusage : fake_objcopy <args>...<args>\n\n");
        return 0;
    }
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "cmd /c \"%s\\..\\..\\..\\sdcc\\%s\\bin\\packihx.exe\" %s > %s", sdccpath, _SDCC_VERSION_, argv[1],  argv[2]);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer, "\"%s/../../../sdcc/%s/bin/packihx\" %s > %s", sdccpath, _SDCC_VERSION_, argv[1],  argv[2]);
#else
#error "OS not supported"
#endif
    err=system(cmdbuffer);
    if (err != 0) { // -1 means an error with the call itself
        int err = WEXITSTATUS(err);
        perror("fake_objcopy Error !");
    }
    return 0;
};

