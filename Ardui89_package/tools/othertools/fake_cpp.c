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
// copy file
int cpyfile(char *srcfile, char *destfile) {
    char cmdbuffer[4096];
    if (srcfile[strlen(srcfile)-1]=='p') {
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "cmd /c copy %s %s/%s.c /y", srcfile, destfile, basename(srcfile));
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
                    cpyheadandc(".", destdir);
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
    sprintf(librariespath,"%s/Documents/Arduino/libraries",getenv("USERPROFILE"));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(librariespath,"%s/Documents/Arduino/libraries",getenv("HOME"));
#else
#error "OS not supported"
#endif
    // current path
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
        char cfilename[4096];
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
        } else if (strstr(argv[i], ".ino.cpp")) {
            sprintf(cc_parameters.sketchpath,"%s",dirname(argv[i]));
            sprintf(cc_parameters.inofilename,"%s",argv[i]);
            //strncpy(cmdbuffer, argv[i], strlen(argv[i])-8);
            //sprintf(cc_parameters.cfilename, "%s.c", argv[i]); // Replace .ino by .c in argv file name
            sprintf(argsbuffer, "%s %s/../%s.c", argsbuffer, cc_parameters.sketchpath, basename(argv[i]));
#if defined(_WIN32) || defined(_WIN64)
            sprintf(cmdbuffer, "cmd /c copy %s %s/../%s.c /y", argv[i], cc_parameters.sketchpath, basename(argv[i]));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(cmdbuffer, "cp -f %s %s/../%s.c", argv[i], cc_parameters.sketchpath, basename(argv[i]));
#else
#error "OS not supported"
#endif
            err=system(cmdbuffer);
            if (err != 0) { // -1 means an error with the call itself
                int err = WEXITSTATUS(err);
                perror("fake_cpp Fake Error '.ino.cpp' !");
            }
            sprintf(cmdbuffer, "%s/../libraries",cc_parameters.sketchpath);
            fakelibraries(cmdbuffer);
            sprintf(argsbuffer, "%s -I%s/../libraries",argsbuffer, cc_parameters.sketchpath);
            printf("Copy libraries Done.\n");
        } else if (strstr(argv[i], ".cpp") && !strstr(argv[i], ".cpp.")) {
            sprintf(cc_parameters.currentpath,"%s",dirname(argv[i]));
            //sprintf(cc_parameters.inofilename,"%s",argv[i]);
            //strncpy(cmdbuffer, argv[i],strlen(argv[i])-4);
            //sprintf(cc_parameters.cfilename, "%s.c", argv[i]); // Replace .ino by .c in argv file name
            sprintf(argsbuffer, "%s %s/../%s.c", argsbuffer, cc_parameters.currentpath, basename(argv[i]));
#if defined(_WIN32) || defined(_WIN64)
            sprintf(cmdbuffer, "cmd /c copy %s %s/../%s.c /y", argv[i], cc_parameters.currentpath, basename(argv[i]));
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(cmdbuffer, "cp -f %s %s/../%s.c", argv[i], cc_parameters.currentpath, basename(argv[i]));
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
        sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo BEGIN:FAKE_CPP:::ORG=%s:::SDCC=%s/sdcc %s:::END;exit\"'", orgargsbuffer, cc_parameters.sdccpath, argsbuffer);
        system(cmdbuffer);
         */
        /*sprintf(cmdbuffer,"echo \"-%s %s %s %s-\">%s/../arduino_stc_sdcc_info%ld.txt", cc_parameters.sketchpath, cc_parameters.inofilename, cc_parameters.cfilename, cc_parameters.cflags, cc_parameters.sketchpath, millis());
        system(cmdbuffer);
         */
    // end debug series lines
    
    // CALL COMPILER
#if defined(_WIN32) || defined(_WIN64)
            sprintf(cmdbuffer, "cmd /c %s/sdcc.exe %s",cc_parameters.sdccpath, argsbuffer);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
        sprintf(cmdbuffer, "%s/sdcc %s",cc_parameters.sdccpath, argsbuffer);
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
