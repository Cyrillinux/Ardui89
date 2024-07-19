/*
 * DISLCAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>

#ifndef WEXITSTATUS
#ifdef MINGW32
#define WEXITSTATUS(w) (((w) & 0xC0000000) == 0)
#else
#define WEXITSTATUS(w) (((w) >> 8) & 0377)
#endif
#endif

/*
 * Main *
 */
int main(int argc, char *argv[]) {
    struct stat statbuffer;
    struct _cc_parameters_ {
        char inofilename[4096];
        char cfilename[4096];
        char sketchpath[4096];
        char cflags[4096];
        char sdccpath[4096];
        char currentpath[4096];
        char tmpfile[4096];
    } cc_parameters;
    char cmdbuffer[4096];
    char argsbuffer[4096];
    char orgargsbuffer[4096];
    int err=0;
    // test
    if (argc<2) {
        printf("\nusage : fake_ld <args>...<args>\n\n");
        return 0;
    }
    // See all args
    for (int i = 0; i < argc; i++) {
                sprintf(orgargsbuffer, "%s %s", orgargsbuffer, argv[i]);
    };
    // Compiler path
    sprintf(cc_parameters.sdccpath,"%s",dirname(argv[0]));
    for (int i = 1; i < argc; i++) {
        // test args if option ?
        if (argv[i][0]=='-') {
            sprintf(argsbuffer, "%s %s", argsbuffer, argv[i]);
            if ((argv[i][1]=='o') || (strstr(argv[i], "--disable-warning")))  {
                sprintf(argsbuffer, "%s %s", argsbuffer, argv[++i]);
            }
        } else if (strstr(argv[i], ".ino.cpp.o")) {
            sprintf(cc_parameters.sketchpath,"%s",dirname(argv[i]));
            sprintf(cc_parameters.inofilename,"%s",argv[i]);
            strncpy(cc_parameters.tmpfile, argv[i], strlen(argv[i])-2);
            cc_parameters.tmpfile[strlen(argv[i])-2]=0;
            sprintf(argsbuffer, "%s %s.rel", argsbuffer, cc_parameters.tmpfile);
#if defined(_WIN32) || defined(_WIN64)
            sprintf(cmdbuffer, "cmd /c copy %s %s.rel /y",argv[i], cc_parameters.tmpfile);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(cmdbuffer, "cp -f %s %s.rel",argv[i], cc_parameters.tmpfile);
#else
#error "OS not supported"
#endif
            system(cmdbuffer);
        } else if (strstr(argv[i], ".i.c")) {
            //sprintf(cc_parameters.currentpath,"%s",dirname(argv[i]));
            sprintf(argsbuffer, "%s %s.c", argsbuffer, argv[i]);
        } else if (strstr(argv[i], ".o") && !strstr(argv[i], ".o.")) {
            strncpy(cc_parameters.tmpfile, argv[i], strlen(argv[i])-2);
            cc_parameters.tmpfile[strlen(argv[i])-2]=0;
            sprintf(argsbuffer, "%s %s.rel", argsbuffer, cc_parameters.tmpfile);
#if defined(_WIN32) || defined(_WIN64)
            sprintf(cmdbuffer, "cmd /c copy %s %s.rel /y",argv[i], cc_parameters.tmpfile);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(cmdbuffer, "cp -f %s %s.rel", argv[i], cc_parameters.tmpfile);
#else
#error "OS not supported"
#endif
            system(cmdbuffer);
        } else if (strstr(argv[i], ".a") && !strstr(argv[i], ".a.")) {
            sprintf(argsbuffer, "%s %s.lib", argsbuffer, argv[i]);
        } else sprintf(argsbuffer, "%s %s", argsbuffer, argv[i]);
    }
/*
 * ADD LIBRARIES AND MAIN OBJECTS
*/
    sprintf(argsbuffer, "%s %s/../libraries/libraries.a.lib", argsbuffer, cc_parameters.sketchpath);
    sprintf(argsbuffer, "%s %s/../core/Main89.cpp.rel", argsbuffer, cc_parameters.sketchpath);
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "cmd /c copy %s\\..\\core\\Main89.cpp.o %s\\..\\core\\Main89.cpp.rel /y",cc_parameters.sketchpath, cc_parameters.sketchpath);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer, "cp -f %s/../core/Main89.cpp.o %s/../core/Main89.cpp.rel",cc_parameters.sketchpath, cc_parameters.sketchpath);
#else
#error "OS not supported"
#endif
        system(cmdbuffer);
    
        // Debug series...
        //printf("My Arguments : %s\n", cc_parameters.inofilename);
        //chdir(cc_parameters.sketchpath);
 //     getcwd(cc_parameters.currentpath, sizeof(cc_parameters.currentpath));
 /*
        sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo FAKE_LD: * :ORG=%s: * :SDCC=%s/sdcc %s: * :OTHERS=%s %s %s %s: * :END;exit\"'", orgargsbuffer, cc_parameters.sdccpath, argsbuffer, cc_parameters.sketchpath, cc_parameters.inofilename, cc_parameters.cfilename, cc_parameters.cflags);
        system(cmdbuffer);
*/
    // CALL COMPILER
#if defined(_WIN32) || defined(_WIN64)
            sprintf(cmdbuffer, "cmd /c %s\\..\\..\\..\\sdcc\\%s\\bin\\sdcc.exe %s",cc_parameters.sdccpath, _SDCC_VERSION_, argsbuffer);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
        sprintf(cmdbuffer, "%s/../../../sdcc/%s/bin/sdcc %s",cc_parameters.sdccpath, _SDCC_VERSION_, argsbuffer);
#else
#error "OS not supported"
#endif          
        err=system(cmdbuffer);
        if (err != 0) { // -1 means an error with the call itself
            int err = WEXITSTATUS(err);
            perror("fake_ld Error !");
        }
    printf("fake_ld Done.\n");
    return err;
}
