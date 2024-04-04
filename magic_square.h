#include <stdio.h>
#include <stdbool.h>

#ifndef MAGIC_SQUARE_H
#define MAGIC_SQUARE_H

#endif // MAGIC_SQUARE_H

#define N 3

const int magicConstant = (N * (N * N + 1)) / 2;

bool isRepeated(int [][N], int, int, int);

bool checkRow(int [][N], int);

bool checkCol(int [][N], int);

bool checkDiag(int [][N]);

bool checkReverseDiag(int [][N]);

bool checkSolution(int [][N]);

void markSpace(int [][N], int, int, int);

void unmarkSpace(int [][N], int, int);

void moveForward(int *, int *, int *);

void moveBackward(int [][N], int *, int *, int *);

bool isFinished(int, int);

bool isUnsolvable(int, int, int);

bool solve(int [][N]);

void drawLine();

void show(int [][N]);

bool isRepeated(int board[][N], int row, int col, int counter) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == row && j == col) {
                return false;
            }
            if (board[i][j] == counter) {
                return true;
            }
        }
    }
    return false;
}

bool checkRow(int board[][N], int row) {
    int sum = 0;
    for (int col = 0; col < N; col++) {
        sum += board[row][col];
    }
    return sum == magicConstant;
}

bool checkCol(int board[][N], int col) {
    int sum = 0;
    for (int row = 0; row < N; row++) {
        sum += board[row][col];
    }
    return sum == magicConstant;
}

bool checkDiag(int board[][N]) {
    int row = 0, col = 0;
    int sum = 0;
    while (row < N && col < N) {
        sum += board[row][col];
        row++;
        col++;
    }
    return sum == magicConstant;
}

bool checkReverseDiag(int board[][N]) {
    int row = 0, col = N - 1;
    int sum = 0;
    while (row < N && col >= 0) {
        sum += board[row][col];
        row++;
        col--;
    }
    return sum == magicConstant;
}

bool checkSolution(int board[][N]) {
    for (int i = 0; i < N; i++) {
        if (!(checkRow(board, i) && checkCol(board, i))) {
            return false;
        }
    }
    return checkDiag(board) && checkReverseDiag(board);
}

void markSpace(int board[][N], int row, int col, int counter) {
    board[row][col] = counter;
}

void unmarkSpace(int board[][N], int row, int col) {
    board[row][col] = 0;
}

void moveForward(int *row, int *col, int *counter) {
    if (*col == N - 1) {
        *col = 0;
        *row += 1;
    } else {
        *col += 1;
    }
    *counter = 1;
}

void moveBackward(int board[][N], int *row, int *col, int *counter) {
    if (*col == 0) {
        *col = N - 1;
        *row -= 1;
    } else {
        *col -= 1;
    }
    *counter = board[*row][*col] + 1;
}

bool isFinished(int row, int col) {
    return row == N - 1 && col == N - 1;
}

bool isUnsolvable(int row, int col, int counter) {
    return row == 0 && col == 0 && counter >= N * N;
}

bool solve(int board[][N]) {
    int row = 0;
    int col = 0;
    int counter = 1;
    while (true) {
        if (counter <= N * N && !isRepeated(board, row, col, counter)) {
            markSpace(board, row, col, counter);
            if (isFinished(row, col)) {
                if (checkSolution(board)) {
                    return true;
                }
                unmarkSpace(board, row, col);
                moveBackward(board, &row, &col, &counter);
                continue;
            }
            moveForward(&row, &col, &counter);
        } else {
            counter += 1;
            if (isUnsolvable(row, col, counter)) {
                return false;
            }
            if (counter >= N * N) {
                unmarkSpace(board, row, col);
                moveBackward(board, &row, &col, &counter);
            }
        }
    }
}

void drawLine() {
    for (int i = 0; i < N; i++) {
        printf("+----");
    }
    printf("+\n");
}

void show(int board[][N]) {
    fflush(stdout);
    drawLine();
    for (int i = 0; i < N; i++) {
        fflush(stdout);
        for (int j = 0; j < N; j++) {
            printf("| %2d ", board[i][j]);
        }
        printf("|\n");
        drawLine();
    }
    printf("\n");
}