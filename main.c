#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

enum Space {
    Empty,
    Naught,
    Cross
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
                case Naught:
                    printf(" o ");
                    break;
                case Cross:
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
        scanf("%c %c", &a, &b);

        result = decodeCoordinates(a, b, row, col);
    }
}

int main() {
    int row;
    int col;
    drawBoard();
    askPosition(&row, &col);
    printf("Row: %d, Col: %d", row, col);
    return 0;
}
