#include <stdio.h>
#include <stdlib.h>

int n;       // 棋盘大小
int *board;  // board[col] = row 放置皇后在第 col 列的行

// 检查当前位置 (row, col) 是否安全
int is_safe(int row, int col) {
    for (int c = 0; c < col; c++) {
        int r = board[c];
        if (r == row || abs(r - row) == abs(c - col)) {
            return 0; // 同行或同斜线冲突
        }
    }
    return 1;
}

// 回溯函数，尝试在 col 列放皇后
void solve(int col) {
    if (col == n) {
        for (int i = 0; i < n; i++) {
            if (i > 0) fprintf(stdout, " ");
            fprintf(stdout, "%d", board[i]);
        }
        fprintf(stdout, "\n");
        return;
    }
    for (int row = 0; row < n; row++) {
        if (is_safe(row, col)) {
            board[col] = row;
            solve(col + 1);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    n = atoi(argv[1]);
    if (n <= 0) return 0;

    board = calloc(n, sizeof(int));
    if (!board) return 1;

    solve(0);

    free(board);
    return 0;
}