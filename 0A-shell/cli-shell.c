/*
Nelle Borg Costanzi (nellemat) https://github.com/fe3n1xx

0A-shell is a basic fake shell emulator C project

=========
Commands:
=========

echo - Print

    syntax:
    echo <string>
    function:
    echo("string");

cd - Change Directory

    syntax:
    cd <directory>
    function:
    cd(var);

ls - list files in a directory

    syntax:
    ls <directory>
    function:
    ls(var);

==========
Functions:
==========

remove_initial_prefix(var, "prefix"); - Remove prefix from a string, returns void
starts_with(var, "prefix"); - Checks if prefix starts the variable, returns bool
directory_exists(var); - Checks if a directory exists, returns bool

========
Imports:
========

stdio.h
unistd.h
string.h
stdbool.h
dirent.h
errno.h

==========
Variables:
==========

char USRInput[256]; - The variable that is what the user inputs to the shell
char newpwd; - Used by the cd(var) function to change the pwd
char toPrint; - Used by echo("String") function to print
bool running; - Used to indicate that the program is running
*/

// IMPORTS
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>

// VARIABLES
char USRInput[256];
char newpwd;
char toPrint;
bool running;

// SET PWD
char pwd[256] = "~/";

// Remove initial prefix from string
void remove_initial_prefix(char *str, const char *prefix) {
    size_t prefix_len = strlen(prefix);

    // Check if string actually starts with the prefix
    if (strncmp(str, prefix, prefix_len) == 0) {
        /* Shift everything left, including '\0'
        totl. bytes to move = totl. len - prefix len + 1 (for '\0')*/
        size_t total_len = strlen(str);
        memmove(str, str + prefix_len, total_len - prefix_len + 1);
    }
}

// Starts with checker
bool starts_with(const char *str, const char *prefix) {
    if (strlen(prefix) > strlen(str)) {
        return false;
    }
    return strncmp(str, prefix, strlen(prefix)) == 0;
}

// Check if directory exists
bool directory_exists(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return true; // Exists
    } else if (ENOENT == errno) {
        return false; // Doesnt exist
    } else {
        return false; // Exists but fails to open (e.g. permission denied)
    }
}


// CD COMMAND

void cd(char *newpwd) {
    if (newpwd != NULL && directory_exists(newpwd)) {
        snprintf(pwd, sizeof(pwd), "%s", newpwd);
    }
}


// ECHO COMMAND

void echo(char toPrint[sizeof(toPrint)]) {
    printf(toPrint);
}

/*
INT MAIN
*/
int main () {
    //
    bool running = true;

    while (running) {
        printf("[%s] - ", pwd);
        // READ USER INPUT
        fgets(USRInput, sizeof(USRInput), stdin);
        // Clean up \n
        USRInput[strcspn(USRInput, "\n")] = '\0';

        if (starts_with(USRInput, "cd")) {
            //
            remove_initial_prefix(USRInput, "cd ");
            cd(USRInput);
        }
    }
}