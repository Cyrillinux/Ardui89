/* DISCLAIMER OF ALL WARRANTIES */
/* Tool fore create json package */
/* Cyril Barbato 2024*/
#include <stdio.h>
#include <stdlib.h>
#include "sha256.h"

void print_sha256(unsigned char hash[SHA256_DIGEST_LENGTH]) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
//    printf("\n");
}

long int findSize(char file_name[])
{
    // opening the file in read mode
    FILE* fp = fopen(file_name, "r");
  
    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }
  
    fseek(fp, 0L, SEEK_END);
  
    // calculating the size of the file
    long int res = ftell(fp);
  
    // closing the file
    fclose(fp);
  
    return res;
}

int main(int argc, char *argv[]) {
    
    SHA256_CTX sha256;
    
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <filename> <host> <url>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        perror("Unable to open file");
        return 1;
    }

    fseek(file, 0L, SEEK_END);
    long int res = ftell(file);
    printf("{\n");
    if (res != -1) printf("    \"size\": \"%ld\",\n", res);
 
    fseek(file, 0L, SEEK_SET);
    
    sha256_init(&sha256);

    const int bufSize = 32768;
    unsigned char *buffer = malloc(bufSize);
    if (!buffer) {
        fprintf(stderr, "Unable to allocate buffer\n");
        fclose(file);
        return 1;
    }

    int bytesRead = 0;
    while ((bytesRead = fread(buffer, 1, bufSize, file))) {
        sha256_update(&sha256, buffer, bytesRead);
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    sha256_finalize(&sha256);

    sha256_read(&sha256, hash);
   
   
    printf("    \"checksum\": \"SHA-256:");
    print_sha256(hash);
    printf("\",\n");
    printf("    \"archiveFileName\": \"%s\",\n", argv[1]);
    printf("    \"url\": \"%s\",\n", argv[3]);
    printf("    \"host\": \"%s\"\n", argv[2]);
    printf("}\n");
    fclose(file);
    free(buffer);

    return 0;
}
