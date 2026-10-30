#include <stdio.h>
void printGame(char *destination, size_t max_size, char gameArray[3][3])
{
    // variables
    char lineone[100];
    char linetwo[100];
    char linethree[100];
    // Create lines
    snprintf(lineone, sizeof(lineone), "%c | %c | %c", gameArray[2][0], gameArray[2][1], gameArray[2][2]);
    snprintf(linetwo, sizeof(linetwo), "%c | %c | %c", gameArray[1][0], gameArray[1][1], gameArray[1][2]);
    snprintf(linethree, sizeof(linethree), "%c | %c | %c", gameArray[0][0], gameArray[0][1], gameArray[0][2]);
    // Output
    snprintf(destination, max_size, "%s\n%s\n%s", lineone, linetwo, linethree);
};

int main()
{
    printf("NOUGHTS AND CROSSES\n");
    // gameArray[x][y]
    /*
    [2][0] | [2][1] | [2][2]
    ------------------------
    [1][0] | [1][1] | [1][2]
    ------------------------
    [0][0] | [0][1] | [0][2]
    */
    char gameArray[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}
    };
    bool game = true;
    // hold buffer
    char finalBoard[256];
    //
    // GAME LOOP
    //
    while (game) {
        // WOI
    }

    return 0;
};
/*
    // call funct to get printGame()
    printGame(finalBoard, sizeof(finalBoard), gameArray);
    // Print the board
    printf("%s\n", finalBoard);
*/