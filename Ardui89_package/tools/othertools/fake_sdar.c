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
// Function to extract a value from JSON given a key
int jsongetvalue(const char *json, const char *key, char *value) {
    char *found = strstr(json, key);
    if (!found) {
        return -1;
    }
    found = strchr(found, ':');
    if (!found) {
        return -1;
    }
    found += 1; // Skip past ':'
    while (*found == ' ' || *found == '"') {
        found++; // Skip any spaces or quotes
    }
    char *end = found;
    while (*end != '"' && *end != ',' && *end != '}' && *end != '\0') {
        end++;
    }
    strncpy(value, found, end - found);
    value[end - found] = '\0';
    return 0;
}

// Function to read the entire content of a file into a string
int fileread(const char *filename, char *content) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Unable to open file %s\n", filename);
        return -1;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    fread(content, 1, length, file);
    content[length] = '\0';

    fclose(file);
    return 0;
}
// Get json includes data
int jsongetincludesdata(char *filename, char *includeslist) {
    char json[8192];
    char value[4096];
    if (fileread(filename, json)) {
        return -1;
    }
    const char *keys[] = { "Sourcefile", "Include", "Includepath" };
    int n_items = 3; // Number of JSON objects in the array
    const char *pos = json;
    for (int i = 0; i < n_items; i++) {
        printf("Item %d:\n", i + 1);
        //for (int j = 0; j < 3; j++) {
            jsongetvalue(pos, keys[/*j*/2], value);
            sprintf(includeslist, "%s -I%s", includeslist, strlen(value) ? value : ".");
        //}
        pos = strchr(pos + 1, '{');
        if (!pos) break; // No more objects
    }
    return 0;
}
// makelibrariesobj
int makelibrariesobj(char *objslist, char *sdccpath, char *libpath, char *includespath){
    char cmdbuffer[8192];
    DIR *dp;
    struct dirent *ep;
    dp = opendir(".");
    if (dp != NULL)
    {
        while ((ep = readdir (dp)) != NULL) {
            if (ep->d_name[strlen(ep->d_name)-1]=='c') {
                printf("%s\n",ep->d_name);
                sprintf(objslist, "%s %s.o", objslist, ep->d_name);
#if defined(_WIN32) || defined(_WIN64)
                sprintf(cmdbuffer, "cmd /c %s/sdcc.exe -DARDUINO_ARCH_8051 -c -mmcs51 --std-c99 --model-small --opt-code-size --disable-warning 110 --disable-warning 283 %s -o %s.o %s", sdccpath, ep->d_name, ep->d_name, includespath);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
                sprintf(cmdbuffer, "%s/sdcc -DARDUINO_ARCH_8051 -c -mmcs51 --std-c99 --model-small --opt-code-size --disable-warning 110 --disable-warning 283 %s -o %s.o %s",  sdccpath, ep->d_name, ep->d_name, includespath);
#else
#error "OS not supported"
#endif
                printf("Exec : %s\n", cmdbuffer);
                system(cmdbuffer);
            }
        }
        (void) closedir (dp);
    }
    else
    {
        perror ("Couldn't open the directory");
        return -1;
    }
    printf("Objs list : %s.\n", objslist);
    return 0;
}
/*
 * Main *
 */
int main(int argc, char *argv[]) {
    char sketchpath[4096];
    char sdccpath[4096];
    char currentpath[4096];
    char cmdbuffer[4096];
    char objslist[4096];
    char argsbuffer[4096];
    char includeslist[4096];
    char libpath[4096];
    int err;
    // test
    if (argc<3) {
        printf("\nusage : fake_sdar <args> <args>\n\n");
        return 0;
    }
    sprintf(sdccpath,"%s",dirname(argv[0]));
    for (int i = 1; i < argc; i++) {
        sprintf(argsbuffer,"%s %s", argsbuffer, argv[i]);
        // test args if option ?
        if (strstr(argv[i], "core.a.lib")) { // Get libpath
            sprintf(sketchpath,"%s",dirname(dirname(argv[i])));
            sprintf(libpath,"%s/libraries",dirname(dirname(argv[i])));
        }
    }
    // Get includes files
    sprintf(cmdbuffer, "%s/includes.cache", sketchpath);
    jsongetincludesdata(cmdbuffer, includeslist);
    sprintf(includeslist, "%s -I.", includeslist);
    // current path
    getcwd(currentpath, sizeof(currentpath));
    /*
    // See args for debug
    sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo FAKE_SDAR:ORG=%s:PWD=%s:SDAR=%s/sdcc %s:OTHER:%s:END;exit\"'", argsbuffer, currentpath, sdccpath, argsbuffer, includeslist);
    system(cmdbuffer);
     */
    //Goto to src directory
    chdir(libpath);
    makelibrariesobj(objslist, sdccpath, libpath, includeslist);
#if defined(_WIN32) || defined(_WIN64)
                sprintf(cmdbuffer, "cmd /c %s/sdar.exe rcs %s/libraries.a.lib %s", sdccpath, libpath, objslist);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
                sprintf(cmdbuffer, "%s/sdar rcs  %s/libraries.a.lib %s", sdccpath, libpath, objslist);
#else
#error "OS not supported"
#endif
    system(cmdbuffer);
#if defined(_WIN32) || defined(_WIN64)
                sprintf(cmdbuffer, "cmd /c %s/sdar.exe %s", sdccpath, argsbuffer);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
                sprintf(cmdbuffer, "%s/sdar %s", sdccpath, argsbuffer);
#else
#error "OS not supported"
#endif
    system(cmdbuffer);
    //Goto to org path
    chdir(currentpath);
    printf("fake_libraries Done.\n");
    return err;
}
