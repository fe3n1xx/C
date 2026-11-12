#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cparse.h"

char **cp_parse(const char *fname, int *line_count) {
    //
    FILE *file = fopen(fname, "r");
    if (file == NULL) { printf("CPARSE.H - FAILED TO OPEN FILE\n"); return NULL; }
    
    char **lines = NULL;
    char buffer[MAX_LINE_LENGTH];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // rem trailing \n
        buffer[strcspn(buffer, "\r\n")] = '\0';
        
        // resize array of string ptrs to hold 1 more ln
        char **temp = realloc(lines, (count + 1) * sizeof(char *));
        if (temp == NULL) {
            printf("CPARSE.H - MALLOC FAILED\n");
            // free prev alloc lns
            for (int i = 0; i < count; i++) free(lines[i]);
            free(lines);
            fclose(file);
            return NULL;
        }
        lines = temp;

        // alloc mem for str and cpy it over
        lines[count] = malloc(strlen(buffer) + 1);
        if (lines[count] == NULL) {
            printf("CPARSE.H - MALLOC FAILED");
            for (int i = 0; i < count; i++) free(lines[i]);
            free(lines);
            fclose(file);
            return NULL;
        }
        strcpy(lines[count], buffer);

        // increment line num
        count++;
    }
    fclose(file);
    *line_count = count; // pass tot ln cnt back to the caller
    return lines;
}

// Clean up memory
void cp_free(char **lines, int line_count) {
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }
    free(lines);
}