# CPARSE
CPARSE is a project that parses through lines of a file in c <br>
Example program - Gets the second line of a file called test.txt <br>
```
#include <stdio.h>
#include "cparse.h"

int main() {
    char bole[256] = "test.txt";
    int line_count = 3;
    char **lines = cp_parse(bole, &line_count); // use cp_parse function to get the lines into an array called lines
    printf("%s\n", lines[1]); // output the second line of the file
    cp_free(lines, line_count); // always free the memory!!!!
    return 0;
}
```
If this is the contents of text.txt:
```
HELLO, WORLD!
THIS IS MY PROGRAM!
```
The program will output:
```
THIS IS MY PROGRAM!
```
# FUNCTIONS
There is 2 cparse functions:
```
cp_parse(file, line_count);
```
and
```
cp_free(lines, line_count);
```
# COMPILATION
Always include cparse.c and cparse.h somewhere in your project folder <br>
Compiling test.c to a executable called test.cx, then running it (GCC)
```
gcc test.c cparse.c -o test.cx && ./test.cx
```
Made by fe3n1xx, any errors or issues please contact me! <br>
ALWAYS FREE MEMORY!!!