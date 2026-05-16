/*
 * DISLCAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
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

// copy file
int cpyfile(char *srcfile, char *destfile) {
    char cmdbuffer[4096];
    if (srcfile[strlen(srcfile)-1]=='p') {
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "cmd /c copy %s %s\\%s.c /y", srcfile, destfile, basename(srcfile));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer, "cp -f %s %s/%s.c", srcfile, destfile, basename(srcfile));
#else
#error "OS not supported"
#endif
    } else {
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "cmd /c copy %s %s /y", srcfile, destfile);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer, "cp -f %s %s", srcfile, destfile);
#else
#error "OS not supported"
#endif
    }
    if (system(cmdbuffer)!= 0) { // -1 means an error with the call itself
        return -1;
        perror("fakelibraries Copy Error !");
    }
    return 0;
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

// test if file exists : return 1 if the file specified by the filename exists
int fileExists(const char *filename) {
    FILE *fp = fopen(filename, "r");
    int is_exist = 0;
    if (fp != NULL)
    {
        is_exist = 1;
        fclose(fp); // close the file
    }
    return is_exist;
}

int _8051libraryflag=0;

// Copy all .h and .c and .ccp to dest directory
int cpyheadandc(char *path, char *destdir) {
    DIR *dp;
    struct dirent *ep;
    dp = opendir(path);
    if (dp != NULL)
    {
        while ((ep = readdir (dp)) != NULL) {
            puts (ep->d_name);
            if (isDirectory(ep->d_name) && ep->d_name[0]!='.') {
                printf("--->%s\n",ep->d_name);
                if (!chdir(ep->d_name)) {
                    if (_8051libraryflag || fileExists("_8051_.conf")) {; // 8051 LIBRARY DETECTION
                        _8051libraryflag=1;                               // Copy ONLY 8051 compatible libraries
                        cpyheadandc(".", destdir);
                    }
                    _8051libraryflag=0;
                    printf("<---%s\n",ep->d_name);
                    chdir("..");
                }
            } else if (strstr(ep->d_name, ".c") || strstr(ep->d_name, ".cpp") || strstr(ep->d_name, ".h")) {
                printf("# Copying \"%s\" to \"%s\".\n",ep->d_name, destdir);
                cpyfile(ep->d_name, destdir);
            }
            
        }
      (void) closedir (dp);
      return 0;
    }
    else
    {
      perror ("Couldn't open the directory");
      return -1;
    }
}
int fakelibraries(char *libdest) {
    char currentpath[4096];
    char librariespath[4096];
    char cmdbuffer[4096];
    int err;
#if defined(_WIN32) || defined(_WIN64)
    sprintf(librariespath,"%s\\Documents\\Arduino\\libraries", getenv("USERPROFILE"));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(librariespath,"%s/Documents/Arduino/libraries", getenv("HOME"));
#else
#error "OS not supported"
#endif
    //current path
    //getcwd(currentpath, sizeof(currentpath));
    //Goto to src directory
    struct stat buffer;
    if (stat(libdest, &buffer)) { // test if path exist
#if defined(_WIN32) || defined(_WIN64)
        sprintf(cmdbuffer, "cmd /c mkdir %s", libdest);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
        sprintf(cmdbuffer, "mkdir %s", libdest);
#else
#error "OS not supported"
#endif
        system(cmdbuffer);
    }
    chdir(librariespath);
    cpyheadandc(".", libdest);
    chdir(currentpath);
    printf("fakelibraries Done.\n");
    return err;
}
/*
 * Main *
 */
int main(int argc, char *argv[]) {
    struct stat statbuffer;
    struct _cc_parameters_ {
        char inofilename[4096];
        char currentfilename[4096];
        char sketchpath[4096];
        char cflags[4096];
        char sdccpath[4096];
        char currentpath[4096];
    } cc_parameters;
    char cmdbuffer[4096];
    char argsbuffer[4096];
    char orgargsbuffer[4096];
    
    //Init
    int err=0;
    int includesflag=0;
    
    sprintf(cc_parameters.currentpath, ".");
    sprintf(cc_parameters.sketchpath, ".");
    
    // test
    if (argc<2) {
        printf("\nusage : fake_cpp <args>...<args>\n\n");
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
            } else if ((argv[i][1]=='I') && (includesflag==0)) includesflag=1; // INCLUDES FILES FLAGS
        } else if (strstr(argv[i], ".ino.cpp") && !strstr(argv[i], ".ino.cpp.")) {
            sprintf(cc_parameters.inofilename,"%s",argv[i]);
            sprintf(cc_parameters.sketchpath,"%s",dirname(argv[i]));
#if defined(_WIN32) || defined(_WIN64)
            sprintf(argsbuffer, "%s %s\\..\\%s.c", argsbuffer, cc_parameters.sketchpath, basename(cc_parameters.inofilename));
            sprintf(cmdbuffer, "cmd /c copy %s %s\\..\\%s.c /y", cc_parameters.inofilename, cc_parameters.sketchpath, basename(cc_parameters.inofilename));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(argsbuffer, "%s %s/../%s.c", argsbuffer, cc_parameters.sketchpath, basename(cc_parameters.inofilename));
            sprintf(cmdbuffer, "cp -f %s %s/../%s.c", cc_parameters.inofilename, cc_parameters.sketchpath, basename(cc_parameters.inofilename));
#else
#error "OS not supported"
#endif
            err=system(cmdbuffer);
            if (err != 0) { // -1 means an error with the call itself
                int err = WEXITSTATUS(err);
                perror("fake_cpp Fake Error '.ino.cpp' !");
            }
#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(cc_parameters.currentpath, "%s/../libraries",cc_parameters.sketchpath);
            sprintf(argsbuffer, "%s -I%s",argsbuffer, cc_parameters.currentpath);
            fakelibraries(cc_parameters.currentpath);
#elif defined(_WIN32) || defined(_WIN64)
            sprintf(cc_parameters.currentpath, "%s\\..\\libraries", cc_parameters.sketchpath);
            sprintf(argsbuffer, "%s -I%s",argsbuffer, cc_parameters.currentpath);
            fakelibraries(cc_parameters.currentpath);
           
#else
#error "OS not supported"
#endif
            printf("Copy libraries Done.\n");
        } else if (strstr(argv[i], ".cpp") && !strstr(argv[i], ".cpp.")) {
            sprintf(cc_parameters.currentfilename,"%s",argv[i]);
            sprintf(cc_parameters.currentpath,"%s",dirname(argv[i]));
#if defined(_WIN32) || defined(_WIN64)
            sprintf(argsbuffer, "%s %s\\..\\%s.c", argsbuffer, cc_parameters.currentpath, basename(cc_parameters.currentfilename));
            sprintf(cmdbuffer, "cmd /c copy %s %s\\..\\%s.c /y",  cc_parameters.currentfilename, cc_parameters.currentpath, basename(cc_parameters.currentfilename));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(argsbuffer, "%s %s/../%s.c", argsbuffer, cc_parameters.currentpath, basename(cc_parameters.currentfilename));
            sprintf(cmdbuffer, "cp -f %s %s/../%s.c", cc_parameters.currentfilename, cc_parameters.currentpath, basename(cc_parameters.currentfilename));
#else
#error "OS not supported"
#endif
            err=system(cmdbuffer);
            if (err != 0) { // -1 means an error with the call itself
                int err = WEXITSTATUS(err);
                perror("fake_cpp Fake Error '.cpp' !");
            }
        } else {sprintf(argsbuffer, "%s %s", argsbuffer, argv[i]);}
        /*if (strstr(argv[i], "core")) {
            sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo FAKE_CPP:CODE CALLED:%s;exit\"'", argv[i]);
            system(cmdbuffer);
        }
        */
    }
        // IF FILES FLAGS INCLUDE DETECTED / ADD SKECTH PATH
        if (includesflag)  {
            sprintf(argsbuffer, "%s -I%s -I%s", argsbuffer,  cc_parameters.currentpath, cc_parameters.sketchpath);
        }
        // Debug series...
        //printf("My Arguments : %s\n", cc_parameters.inofilename);
        //chdir(cc_parameters.sketchpath);
/*
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer,"start cmd /k echo \"BEGIN:FAKE_CPP:::ORG=%s:::SDCC=%s/sdcc %s:::END;exit\"", orgargsbuffer, cc_parameters.sdccpath, argsbuffer);
    system(cmdbuffer);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo BEGIN:FAKE_CPP:::ORG=%s:::SDCC=%s/sdcc %s:::END;exit\"'", orgargsbuffer, cc_parameters.sdccpath, argsbuffer);
    system(cmdbuffer);
#else
#error "OS not supported"
#endif
*/
    // end debug series lines
    
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
            perror("fake_cpp Error !");
        }
    printf("fake_cpp Done.\n");
    return err;
}
