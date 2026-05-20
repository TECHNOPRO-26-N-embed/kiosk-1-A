#include "ai_utils.h"
#include <stdio.h>

int ai_input_int(const char* prompt) {
    int val;
    printf("%s", prompt);
    while (scanf("%d", &val) != 1) {
        printf("無効な入力です。再度入力してください: ");
        ai_clear_stdin();
    }
    ai_clear_stdin();
    return val;
}

void ai_clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
