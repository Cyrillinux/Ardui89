/*
 * DISLCAIMER OF ALL WARRANTIES *
 * Cyril BARBATO 2024-2026
 * NEW VERSION / NEW CODE : Read data from .mem file not from .hex
 * Not compatible with old version < 0.2.5
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    // Initialisation du buffer de debug de manière sécurisée
    char orgargsbuffer[4096] = "";
    for (int i = 0; i < argc; i++) {
        strcat(orgargsbuffer, " ");
        strcat(orgargsbuffer, argv[i]);
    }

    if (argc != 2) {
        fprintf(stderr, "\nusage : %s <file.mem>\n\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    unsigned long flash_size = 0;
    unsigned long ram_internal_used = 0;
    unsigned long ram_external_size = 0;
    unsigned long paged_ram_size = 0;

    char line[256];
    int in_internal_ram_map = 0;

    while (fgets(line, sizeof(line), file)) {
        
        // 1. Analyse de la carte de la RAM Interne
        if (strstr(line, "Internal RAM layout:")) {
            in_internal_ram_map = 1;
            continue;
        }
        
        if (in_internal_ram_map) {
            // Les lignes de la matrice commencent par 0x (ex: 0x00:|0|0|...)
            if (strncmp(line, "0x", 2) == 0) {
                // On cherche les caractères entre les pipes '|'
                for (int i = 5; line[i] != '\0' && line[i] != '\n'; i++) {
                    // Si ce n'est pas un espace, un pipe ou un retour à la ligne, c'est de la RAM occupée
                    if (line[i] != ' ' && line[i] != '|' && line[i] != '\r') {
                        ram_internal_used++;
                    }
                }
            } else if (strlen(line) > 1 && strncmp(line, "0-3:", 4) == 0) {
                // On est arrivé à la légende de la carte RAM, on arrête de compter
                in_internal_ram_map = 0;
            }
        }

        // 2. Analyse du tableau "Other memory" (PAGED RAM, EXTERNAL RAM, ROM)
        // SDCC aligne ses colonnes. On utilise des sscanf ciblés ou des décalages.
        if (strstr(line, "PAGED EXT. RAM")) {
            unsigned int start, end;
            unsigned long max;
            // On extrait les adresses en %x et les tailles en %lu (décimal !)
            sscanf(line + 19, "%x %x %lu %lu", &start, &end, &paged_ram_size, &max);
        }
        else if (strstr(line, "EXTERNAL RAM")) {
            // Si la RAM externe est à 0, Start et End sont vides (remplis d'espaces)
            // On vérifie le contenu de la zone "Start" (vers le caractère index 20)
            char sub_section[64];
            // On copie la fin de la ligne là où se trouvent la taille et le max
            // Dans le tableau SDCC, la colonne Size commence environ à l'index 38
            if (strlen(line) >= 45) {
                unsigned long val1 = 0, val2 = 0;
                int parsed = sscanf(line + 35, "%lu %lu", &val1, &val2);
                if (parsed == 2) {
                    ram_external_size = val1;
                }
            }
        }
        else if (strstr(line, "ROM/EPROM/FLASH")) {
            unsigned int start, end;
            unsigned long max;
            // Correction critique : %x pour l'hexa (0x0000), mais %lu pour la taille en décimal (2075) !
            sscanf(line + 19, "%x %x %lu %lu", &start, &end, &flash_size, &max);
        }
    }

    fclose(file);

    // Calculs des totaux pour le format avr-size
    // .text = Taille de la FLASH
    unsigned long total_text = flash_size;
    // .data = RAM totale (Interne occupée + Externe + Paged)
    unsigned long total_data = ram_internal_used + ram_external_size + paged_ram_size;
    // Taille totale globale simulée
    unsigned long total_overall = total_text + total_data;

    // Rendu sous forme de tableau style avr-size
    printf("section                     size        addr\n");
    printf(".data                 %10lu           0\n", total_data);
    printf(".text                 %10lu           0\n", total_text);
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
    printf("Total                 %10lu\n", total_text);

    // DEBUG
    /*
    char currentpath[4096];
    char cmdbuffer[4096];
    getcwd(currentpath, sizeof(currentpath));
    sprintf(cmdbuffer,"osascript -e 'tell app \"Terminal\" to do script \"echo FAKE_SIZE:PATH=%s:::::ORGARGS=%s:END;exit\"'", currentpath, orgargsbuffer);
    system(cmdbuffer);
    */

    return 0;
}
