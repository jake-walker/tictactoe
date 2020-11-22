#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

enum Space {
    Empty,
    Human,
    Computer
};

enum Space board[3][3] = {{Empty, Empty, Empty}, {Empty, Empty, Empty}, {Empty, Empty, Empty}};

void drawBoard() {
    printf("   1   2   3\n");
    for (int row = 0; row < 3; ++row) {
        printf("%c ", row + 'a');
        for (int col = 0; col < 3; ++col) {
            switch (board[row][col]) {
                case Empty:
                    printf("   ");
                    break;
                case Human:
                    printf(" o ");
                    break;
                case Computer:
                    printf(" x ");
                    break;
            }
            if (col < 2) {
                printf("│");
            }
        }
        if (row < 2) {
            printf("\n  ───┼───┼───\n");
        }
    }
    printf("\n\n");
}

bool decodeCoordinates(char a, char b, int *row, int *col) {
    int rowOut;
    int colOut;

    if (isalpha(a) && isdigit(b)) {
        // a is the row, b is the column
        rowOut = tolower(a) - 'a';
        colOut = (b - '0') - 1;
    } else if (isalpha(b) && isdigit(a)) {
        // b is the row, a is the column
        rowOut = tolower(b) - 'a';
        colOut = (a - '0') - 1;
    } else {
        rowOut = -1;
        colOut = -1;
        printf("Unknown format!\n");
    }

    if (rowOut < 0 || rowOut > 2 || colOut < 0 || colOut > 2) {
        return false;
    }

    printf("Decoded %c%c to %d %d\n", a, b, rowOut, colOut);

    *row = rowOut;
    *col = colOut;
    return true;
}

void askPosition(int *row, int *col) {
    bool result = false;

    while (!result) {
        char a;
        char b;
        printf("Where would you like to go? ");
        fflush(stdout);
        fflush(stdin);
        scanf("%c %c", &a, &b);

        result = decodeCoordinates(a, b, row, col);
    }
}

bool isWinner(int piece) {
    // horizontal lines
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == piece && board[i][1] == piece && board[i][2] == piece) {
            return true;
        }
    }

    // vertical lines
    for (int i = 0; i < 3; ++i) {
        if (board[0][i] == piece && board[1][i] == piece && board[2][i] == piece) {
            return true;
        }
    }

    // diagonal lines
    if ((board[0][0] == piece && board[1][1] == piece && board[2][2] == piece) || (board[0][2] == piece && board[1][1] == piece && board[2][0] == piece)) {
        return true;
    }

    return false;
}

bool isBoardFilled() {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row][col] == Empty) {
                return false;
            }
        }
    }

    return true;
}

bool isGameOver() {
    return isWinner(Human) || isWinner(Computer) || isBoardFilled();
}

void doComputerTurn() {
    srand(time(0));

    while (true) {
        int row = rand() % 3;
        int col = rand() % 3;

        printf("Computer trying for %d, %d\n", row, col);

        if (board[row][col] == Empty) {
            board[row][col] = Computer;
            return;
        }
    }
}

void doHumanTurn() {
    while (true) {
        int playerRow;
        int playerCol;
        askPosition(&playerRow, &playerCol);

        if (board[playerRow][playerCol] == Empty) {
            board[playerRow][playerCol] = Human;
            return;
        } else {
            printf("That space is taken!\n");
        }
    }
}

int main() {
    while (true) {
        drawBoard();
        doHumanTurn();
        if (isGameOver()) break;
        doComputerTurn();
        if (isGameOver()) break;
    }

    drawBoard();

    if (isWinner(Human)) {
        printf("Well done human!");
    } else if (isWinner(Computer)){
        printf("Better luck next time!");
    } else {
        printf("Tie");
    }

    return 0;
}
