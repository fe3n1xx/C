#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    [2][0] | [2][1] | [2][2]      NW | N | NE
    ------------------------      ----------- 
    [1][0] | [1][1] | [1][2]       W | C | E
    ------------------------      -----------
    [0][0] | [0][1] | [0][2]      SW | S | SE
    */
    char gameArray[3][3] = {
        {'-', '-', '-'},  // NW | N | NE
        {'-', '-', '-'},  //  W | C | E
        {'-', '-', '-'}   // SW | S | SE
    };
    // Who's go it is
    int go = 0; // EVEN/0: NOUGHT(O), ODD: CROSS(X)
    // Line to play
    char lineToPlay[4] = "NONE";
    // game is on
    bool game = true;
    // hold buffer
    char finalBoard[256];
    //
    // GAME LOOP
    //
    while (game) {
        // WOI
        // Prints the grid
        printGame(finalBoard, sizeof(finalBoard), gameArray);
        printf("%s\n", finalBoard);
        // Ask for input
        printf("Please play a line\n");
        scanf("%s",&lineToPlay);
        // work out who to give that array x,y to
        if (go % 2 == 0) {
            // EVEN - NOUGHTNW
            if (strcmp(lineToPlay, "NW") == 0) {
                //
                gameArray[2][0] = 'O';
            } else if (strcmp(lineToPlay, "N") == 0) {
                //
                gameArray[2][1] = 'O';
            } else if (strcmp(lineToPlay, "NE") == 0) {
                //
                gameArray[2][2] = 'O';
            } else if (strcmp(lineToPlay, "W") == 0) {
                //
                gameArray[1][0] = 'O';
            } else if (strcmp(lineToPlay, "C") == 0) {
                //
                gameArray[1][1] = 'O';
            } else if (strcmp(lineToPlay, "E") == 0) {
                //
                gameArray[1][2] = 'O';
            } else if (strcmp(lineToPlay, "SW") == 0) {
                //
                gameArray[0][0] = 'O';
            } else if (strcmp(lineToPlay, "S") == 0) {
                //
                gameArray[0][1] = 'O';
            } else if (strcmp(lineToPlay, "SE") == 0) {
                //
                gameArray[0][2] = 'O';
            };
        } else {
            // ODD - CROSS
            printf("Odd\n");
            if (lineToPlay == "NW") {
                //
                gameArray[2][0] = 'X';
            } else if (strcmp(lineToPlay, "N") == 0) {
                //
                gameArray[2][1] = 'X';
            } else if (strcmp(lineToPlay, "NE") == 0) {
                //
                gameArray[2][2] = 'X';
            } else if (strcmp(lineToPlay, "W") == 0) {
                //
                gameArray[1][0] = 'X';
            } else if (strcmp(lineToPlay, "C") == 0) {
                //
                gameArray[1][1] = 'X';
            } else if (strcmp(lineToPlay, "E") == 0) {
                //
                gameArray[1][2] = 'X';
            } else if (strcmp(lineToPlay, "SW") == 0) {
                //
                gameArray[0][0] = 'X';
            } else if (strcmp(lineToPlay, "S") == 0) {
                //
                gameArray[0][1] = 'X';
            } else if (strcmp(lineToPlay, "SE") == 0) {
                //
                gameArray[0][2] = 'X';
            };
        };
        go = go + 1;
    };

    return 0;
};
/*
    // call funct to get printGame()
    printGame(finalBoard, sizeof(finalBoard), gameArray);
    // Print the board
    printf("%s\n", finalBoard);
*/