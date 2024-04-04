#include "magic_square.h"

int main() {
    int board[N][N] = {0};
    show(board);
    solve(board);
    show(board);
    return 0;
}
