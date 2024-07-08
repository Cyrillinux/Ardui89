/*
 * DISLCAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Structure pour stocker les informations de chaque section
typedef struct {
    char name[32];
    unsigned int size;
    unsigned int addr;
} Section;

void print_section(const char* name, unsigned int size, unsigned int addr) {
    printf("%-40s %-10u 0x%08x\n", name, size, addr);
}

int main(int argc, char *argv[]) {
    
    // DEBUG
    char *orgargsbuffer = (char*) malloc(sizeof(char)*4096);
    char *cmdbuffer = (char*) malloc(sizeof(char)*4096);
    char currentpath[4096];
    // See all args
    for (int i = 0; i < argc; i++) {
                sprintf(orgargsbuffer, "%s %s", orgargsbuffer, argv[i]);
    };
    getcwd(currentpath, sizeof(currentpath));
    //sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo FAKE_SIZE:PATH=%s:ORGARGS=%s:END;exit\"'", currentpath, orgargsbuffer);
    //system(cmdbuffer);
    free(cmdbuffer);
    free(orgargsbuffer);
    // DEBUG END
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file.hex>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    Section sections[100]; // Assuming there won't be more than 100 sections
    int section_count = 0;
    unsigned int total_size = 0;
    unsigned int base_address = 0;

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != ':') continue; // Each line must start with ':'

        unsigned int length, address, type;
        sscanf(line + 1, "%02x%04x%02x", &length, &address, &type);

        if (type == 0x01) break; // End Of File record
        if (type == 0x04) { // Extended Linear Address Record
            sscanf(line + 9, "%04x", &base_address);
            base_address <<= 16;
            continue;
        }

        if (type != 0x00) continue; // Only process data records

        unsigned int absolute_address = base_address + address;
        unsigned int section_exists = 0;

        // Check if this section already exists
        for (int i = 0; i < section_count; i++) {
            if (sections[i].addr == absolute_address) {
                sections[i].size += length;
                section_exists = 1;
                break;
            }
        }

        // If section does not exist, create a new one
        if (!section_exists) {
            snprintf(sections[section_count].name, sizeof(sections[section_count].name), "section_%d", section_count + 1);
            sections[section_count].size = length;
            sections[section_count].addr = absolute_address;
            section_count++;
        }

        total_size += length;
    }

    fclose(file);

    // Print the section information
    //printf("%-40s %-10s %-10s\n", "section", "size", "addr");
    //for (int i = 0; i < section_count; i++) {
    //    print_section(sections[i].name, sections[i].size, sections[i].addr);
    //}

    // Print the total size
    //printf("%-40s %-10u\n", "Total", total_size);

    printf("section                     size        addr\n");
    printf(".data                          0           0\n");
    printf(".text                 %10u           0\n", total_size);
    printf(".bss                           0           0\n");
    printf(".comment                       0           0\n");
    printf(".note.gnu.avr.deviceinfo       0           0\n");
    printf(".debug_aranges                 0           0\n");
    printf(".debug_info                    0           0\n");
    printf(".debug_abbrev                  0           0\n");
    printf(".debug_line                    0           0\n");
    printf(".debug_frame                   0           0\n");
    printf(".debug_str                     0           0\n");
    printf(".debug_loc                     0           0\n");
    printf(".debug_ranges                  0           0\n");
    printf("Total                 %10u\n", total_size);

    return 0;
}
