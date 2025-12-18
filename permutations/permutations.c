#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void backtrack(char *str, int len, int *used, char *perm, int depth) {
    if (depth == len) {
        perm[depth] = '\0';
        puts(perm);
        return;
    }
    for (int i = 0; i < len; i++) {
        if (used[i]) continue;  // 已经选过
        // 选择字符
        used[i] = 1;
        perm[depth] = str[i];
        backtrack(str, len, used, perm, depth + 1);
        used[i] = 0;  // 回溯
    }
}

int main(int argc, char **argv) {
    if (argc != 2) return 1;

    char *input = argv[1];
    int len = strlen(input);
    char *str = strdup(input);

    // 排序输入，保证字典序
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char tmp = str[i];
                str[i] = str[j];
                str[j] = tmp;
            }
        }
    }

    int *used = calloc(len, sizeof(int));
    char *perm = malloc(len + 1);

    backtrack(str, len, used, perm, 0);

    free(used);
    free(perm);
    free(str);
    return 0;
}