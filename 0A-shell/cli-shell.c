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

checkdir - check if a directory exists
    
    syntax:
    checkdir <directory>
    function:
    checkdir(var);

fperm - check a files permissions

    syntax:
    fperm <file>
    function:
    fperm(var);

sys - run a command in the systems shell

    syntax:
    sys <command>
    function:
    sys(var);

clear - clear the terminal

    syntax:
    clear
    function:
    clear();

cx - run a compiled executble

    syntax:
    cx <file>
    function:
    cx(file);

leave - exit the terminal

    syntax:
    leave
    function:
    leave();

ping - ping a server over the internet

    syntax:
    ping <ip>
    function:
    ping(ip);

// - comments

    syntax:
    // <comment>
    function:
    NONE
    
==========
Functions:
==========

remove_initial_prefix(var, "prefix"); - Remove prefix from a string, returns void
starts_with(var, "prefix"); - Checks if prefix starts the variable, returns bool
directory_exists(var); - Checks if a directory exists, returns bool
compare_strings("String1", "String2"); - Compare strings against eachother, returns int
get_permissions(mode, perms); - Get a files permissions, returns void

========
Imports:
========

stdio.h
unistd.h
string.h
stdbool.h
dirent.h
errno.h
sys/stat.h
stdlib.h

==========
Variables:
==========

char USRInput[256]; - The variable that is what the user inputs to the shell
char newpwd; - Used by the cd(var) function to change the pwd
char toPrint; - Used by echo("String") function to print
char lsdir; - Used by ls(dir) function to share the pwd
char checkdirdir; - used by checkdir(dir) function as the buffer for the directory
char syscmd; - used by the sys command
char cxtorun; - used by the cx command
char toPingIP; - used by the ping command to save the IP address
bool running; - Used to indicate that the program is running

*/

/*
=======
IMPORTS
=======
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>

/*
=========
VARIABLES
=========
*/

char USRInput[256];
char newpwd;
char toPrint;
char lsdir;
char checkdirdir;
char syscmd;
char cxtorun;
char toPingIP;
bool running;

// SET PWD
char pwd[256] = "none";

/*
=========
FUNCTIONS
=========
*/

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

// Alphabetical order comparison function
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Get File Permissions
void get_permissions(mode_t mode, char *perms) {

    // Determine file type

    if (S_ISDIR(mode)) perms[0] = 'd';
    else if (S_ISLNK(mode)) perms[0] = 'l';
    else perms[0] = '-';

    // User permissions

    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';

    // Group permissions

    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';

    // Other permissions

    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';

    // Null terminator
    
    perms[10] = '\0';
}

/*
========
COMMANDS
========
*/

// CD COMMAND

void cd(char *newpwd) {
    if (newpwd != NULL && directory_exists(newpwd)) {
        snprintf(pwd, sizeof(pwd), "%s", newpwd);
    } else {
        printf("Unknown or unrecognised directory\n");
    }
}


// ECHO COMMAND

void echo(char toPrint[sizeof(toPrint)]) {
    printf("%s\n", toPrint);
}

// LS COMMAND

void ls(char *lsdir) {
    if (directory_exists(lsdir)) {
        // Open directory
        DIR *dir = opendir(lsdir);

        // Array alloc to hold file names
        size_t capacity = 10;
        size_t count = 0;

        char **filenames = malloc(capacity * sizeof(char *));

        if (!filenames) {
            printf("Memory allocation failed");
            closedir(dir);
            return;
        }

        struct dirent *entry;
        
        // Gather all file names into dynamic array
        while ((entry = readdir(dir)) != NULL) {
            // Resize array if it runs out of space
            if (count >= capacity) {
                capacity *= 2;
                char **temp = realloc(filenames, capacity * sizeof(char *));
                if (!temp) {
                    printf("Memory reallocation failed");
                    break;
                }
                filenames = temp;
            }
            // Store filenames safely in memory via duplication
            filenames[count] = strdup(entry->d_name);
            count++;
        }

        // Close directory as it is unneeded now
        closedir(dir);

        // Sort the file names alphabetically
        qsort(filenames, count, sizeof(char *), compare_strings);

        /*
        =========
        LS OUTPUT
        =========
        */
       
        // Loop through sorted items, get metadata and print
        printf("%-12s %s\n", "PERMISSIONS", "FILENAME");
        printf("---------------------\n");

        for (size_t i = 0; i < count; i++) {
            struct stat file_stat;
            char perms[] = "----------";
            // Full-path buffer
            char full_path[1024];

            // Combine lsdir and filenames[i] into lsdir/filename
            snprintf(full_path, sizeof(full_path), "%s/%s", lsdir, filenames[i]);

            // Fetch file attributes via stat
            if (stat(full_path, &file_stat) == 0) {
                get_permissions(file_stat.st_mode, perms);
            }

            printf("%s %s\n", perms, filenames[i]);

            // Free up memory
            free(filenames[i]);
        }
        // Clean up top level array memory
        free(filenames);
    } else {
        printf("Unknown Directory.\n");
    }
}

// CHECKDIR COMMAND
void checkdir(char *checkdirdir) {
    //
    if (directory_exists(checkdirdir)) printf("Directory %s exists!\n", checkdirdir);
    else printf("Directory %s does not exist!\n", checkdirdir);
}

// SYS COMMAND
void sys(char *syscmd) {
    system(syscmd);
}

// CLEAR COMMAND

void clear() {
    printf("\e[1;1H\e[2J");
}

// CX COMMAND

void cx(char *cxtorun) {
    //
    printf("Starting executable...\n");

    cxtorun = ("./%s", cxtorun);

    int status = system(cxtorun);

    if (status ==  -1) {
        printf("Failed to run the executable.\n");
    } else {
        printf("Executable finished.\n");
    }
}

// PING COMMAND

void ping(char *toPingIP) {
    //
    system(toPingIP);
}

// LEAVE COMMAND

void leave() {
    exit(0);
}

/*
===============
INT MAIN

WHILE RUNNING:
ADDED COMMANDS:

CD
ECHO
LS
CHECKDIR
SYS
CLEAR
LEAVE
CX
PING
// - COMMENTS
===============
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
        } else if (starts_with(USRInput, "echo")) {
            //
            remove_initial_prefix(USRInput, "echo ");
            echo(USRInput);
        } else if (starts_with(USRInput, "ls")) {
            //
            remove_initial_prefix(USRInput, "ls ");
            ls(USRInput);
        } else if (starts_with(USRInput, "checkdir")) {
            //
            remove_initial_prefix(USRInput, "checkdir ");
            checkdir(USRInput);
        } else if (starts_with(USRInput, "sys")) {
            remove_initial_prefix(USRInput, "sys ");
            sys(USRInput);
        } else if (starts_with(USRInput, "clear")) {
            clear();
        } else if (starts_with(USRInput, "leave")) {
            leave();
        } else if (starts_with(USRInput, "cx")) {
            remove_initial_prefix(USRInput, "cx ");
            cx(USRInput);
        } else if (starts_with(USRInput, "ping")) {
            ping(USRInput);
        } else if (starts_with(USRInput, "//")) {
            //
        } else {
            printf("Unknown or unrecognised command: %s\n", USRInput);
        }
    }
}