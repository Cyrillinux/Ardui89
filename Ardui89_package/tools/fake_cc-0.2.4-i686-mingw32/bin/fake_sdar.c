/*
 * DISLCAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024-2025
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
    char search_pattern[256];
    snprintf(search_pattern, sizeof(search_pattern), "\"%s\"", key);
    
    char *found = strstr(json, search_pattern);
    if (!found) {
        return -1;
    }
    
    found = strchr(found, ':');
    if (!found) {
        return -1;
    }
    found += 1; // Skip past ':'
    
    // Skip whitespace
    while (*found == ' ' || *found == '\t' || *found == '\n' || *found == '\r') {
        found++;
    }
    
    // Handle null values
    if (strncmp(found, "null", 4) == 0) {
        value[0] = '\0';
        return 0;
    }
    
    // Handle string values (with quotes)
    if (*found == '"') {
        found++; // Skip opening quote
        char *end = strchr(found, '"');
        if (!end) {
            return -1;
        }
        strncpy(value, found, end - found);
        value[end - found] = '\0';
    } else {
        // Handle non-string values
        char *end = found;
        while (*end != ',' && *end != '}' && *end != ']' && *end != '\0' &&
               *end != '\n' && *end != '\r' && *end != ' ' && *end != '\t') {
            end++;
        }
        strncpy(value, found, end - found);
        value[end - found] = '\0';
    }
    
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
    
    printf("DEBUG: filename json = %s\n", filename);
    
    if (fileread(filename, json)) {
        return -1;
    }
    
    // Initialize includeslist
    includeslist[0] = '\0';
    
    const char *keys[] = { "Sourcefile", "Include", "Includepath" };
    
    // Find each object in the JSON array
    char *pos = json;
    char *object_start;
    int object_count = 0;
    
    // Skip to first '{'
    pos = strchr(pos, '{');
    
    while (pos != NULL && object_count < 10) { // Limite à 10 objets pour sécurité
        object_start = pos;
        
        // Find the end of this object
        int brace_count = 1;
        char *object_end = pos + 1;
        while (*object_end && brace_count > 0) {
            if (*object_end == '{') brace_count++;
            else if (*object_end == '}') brace_count--;
            object_end++;
        }
        
        if (brace_count != 0) break; // Malformed JSON
        
        // Extract object content
        size_t object_len = object_end - object_start;
        char object_content[2048];
        strncpy(object_content, object_start, object_len);
        object_content[object_len] = '\0';
        
        printf("Item %d:\n", object_count + 1);
        
        // Extract Includepath specifically
        if (jsongetvalue(object_content, "Includepath", value) == 0 && strlen(value) > 0) {
            char temp[8192];
            snprintf(temp, sizeof(temp), "%s -I%s", includeslist, value);
            strcpy(includeslist, temp);
            printf("  Includepath: %s\n", value);
        } else {
            printf("  Includepath: null or empty\n");
        }
        
        // Pour debug, afficher les autres valeurs aussi
        if (jsongetvalue(object_content, "Sourcefile", value) == 0) {
            printf("  Sourcefile: %s\n", strlen(value) > 0 ? value : "null");
        }
        
        if (jsongetvalue(object_content, "Include", value) == 0) {
            printf("  Include: %s\n", strlen(value) > 0 ? value : "empty");
        }
        
        object_count++;
        
        // Find next object
        pos = strchr(object_end, '{');
    }
    
    return 0;
}
// makelibrariesobj
int makelibrariesobj(char *objslist, char *sdccpath, char *libpath, char *includespath){
    char cmdbuffer[8192];
    DIR *dp;
    struct dirent *ep;
    objslist[0]='\0';
    dp = opendir(".");
    if (dp != NULL)
    {
        while ((ep = readdir (dp)) != NULL) {
            printf(" File found : %s\n", ep->d_name);
            if (ep->d_name[strlen(ep->d_name)-1]=='c') {
                printf("%s\n",ep->d_name);
                sprintf(objslist, "%s %s.o", objslist, ep->d_name);
#if defined(_WIN32) || defined(_WIN64)
                sprintf(cmdbuffer, "cmd /c %s\\..\\..\\..\\sdcc\\%s\\bin\\sdcc.exe -DARDUINO_ARCH_8051 -c -mmcs51 --std-c99 --model-small --opt-code-size --disable-warning 110 --disable-warning 283 %s -o %s.o %s", sdccpath, _SDCC_VERSION_, ep->d_name, ep->d_name, includespath);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
                sprintf(cmdbuffer, "%s/../../../sdcc/%s/bin/sdcc -DARDUINO_ARCH_8051 -c -mmcs51 --std-c99 --model-small --opt-code-size --disable-warning 110 --disable-warning 283 %s -o %s.o %s",  sdccpath, _SDCC_VERSION_, ep->d_name, ep->d_name, includespath);
#else
#error "OS not supported"
#endif
                printf(" Exec : %s\n", cmdbuffer);
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
    // test
    if (argc<3) {
        printf("\nusage : fake_sdar <args> <args>\n\n");
        return 0;
    }
#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(sdccpath,"%s/sdcc/%s/bin",dirname(dirname(dirname(dirname(argv[0])))), _SDCC_VERSION_);
#elif defined(_WIN32) || defined(_WIN64)
    sprintf(sdccpath,"%s\\sdcc\\%s\\bin",dirname(dirname(dirname(dirname(argv[0])))), _SDCC_VERSION_);
#else
#error "OS not supported"
#endif
    for (int i = 1; i < argc; i++) {
        sprintf(argsbuffer,"%s %s", argsbuffer, argv[i]);
        // test args if option ?
        if (strstr(argv[i], "core.a.lib")) { // Get libpath
            sprintf(sketchpath,"%s",dirname(dirname(argv[i])));
#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
            sprintf(libpath,"%s/libraries", sketchpath);
#elif defined(_WIN32) || defined(_WIN64)
            sprintf(libpath,"%s\\libraries", sketchpath);
            /*
            sprintf(cmdbuffer,"start cmd /k echo \"BEGIN:FAKE_SDAR:SKETCH PATH=%s, LIB PATH=%s:::END;exit\"'", sketchpath, libpath);
            system(cmdbuffer);
            */
#else
#error "OS not supported"
#endif
        }
    }
    // Get includes files
#if defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer, "%s/includes.cache", sketchpath);
#elif defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "%s\\includes.cache", sketchpath);
#else
#error "OS not supported"
#endif
    jsongetincludesdata(cmdbuffer, includeslist);
    sprintf(includeslist, "%s -I.", includeslist);
    // current path
    getcwd(currentpath, sizeof(currentpath));
    //Goto to src directory
    chdir(libpath);
    makelibrariesobj(objslist, sdccpath, libpath, includeslist);
/*
    // DEBUG
   #if defined(_WIN32) || defined(_WIN64)
       sprintf(cmdbuffer,"start cmd /k echo \"BEGIN:FAKE_SDAR:ORG=%s:PWD=%s:SDAR=%s\\sdar.exe %s:OTHER:includeslist=%s objslist=%s libpath=%s:END;exit\"'", argsbuffer, currentpath, sdccpath, argsbuffer, includeslist, objslist, libpath);
   #elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
       sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo FAKE_SDAR:ORG=%s:PWD=%s:SDAR=%s/sdar %s:OTHER:%s:END;exit\"'", argsbuffer, currentpath, sdccpath, argsbuffer, includeslist);
   #else
   #error "OS not supported"
   #endif
       system(cmdbuffer);
   // END DEBUG
*/
#if defined(_WIN32) || defined(_WIN64)
    sprintf(cmdbuffer, "cmd /c %s\\sdar.exe rcs %s\\libraries.a.lib %s", sdccpath, libpath, objslist);
    //sprintf(cmdbuffer,"start cmd /k echo \"BEGIN:CMD=%s\"", cmdbuffer);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
    sprintf(cmdbuffer, "%s/sdar rcs  %s/libraries.a.lib %s", sdccpath, libpath, objslist);
#else
#error "OS not supported"
#endif
    system(cmdbuffer);
#if defined(_WIN32) || defined(_WIN64)
                sprintf(cmdbuffer, "cmd /c %s\\sdar.exe %s", sdccpath, argsbuffer);
#elif defined(__APPLE__) || defined(__MACH__) || defined(__linux__)
                sprintf(cmdbuffer, "%s/sdar %s", sdccpath, argsbuffer);
#else
#error "OS not supported"
#endif
    system(cmdbuffer);
    //Goto to org path
    chdir(currentpath);
    printf("fake_libraries Done.\n");
    return 0;
}
