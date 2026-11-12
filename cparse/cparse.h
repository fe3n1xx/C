#ifndef CPARSE_H
#define CPARSE_H

#define MAX_LINE_LENGTH 1024

char **cp_parse(const char *fname, int *line_count);
void cp_free(char **lines, int line_count);

#endif