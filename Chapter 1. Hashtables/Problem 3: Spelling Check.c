#include <stdio.h>

int second_check(char* misspel, char* correct) {
    for (int i = 0; misspel[i] != '\0'; i++) {
        if (misspel[i] != correct[i] ) return 0;
    }
    return 1;
}

int check(char* misspel, char* correct) {
    for (int i = 0; misspel[i] != '\0'; i++) {
        if (misspel[i] != correct[i]) {
            if (second_check(misspel + i + 1, correct + i)) return i + 1;
            else break;
        }
    }
    return 0;
}

int main() {

    static char misspel[1000000 + 1];
    static char correct[1000000 + 1];
    scanf("%s%s", misspel, correct);
    int index = check(misspel, correct), count = 1;
    if (!index) {
        printf("0\n");
        return 0;
    }

    char misspeled = misspel[index - 1];
    for (int i = index - 1; i > 0; i--) {
        if (misspel[i - 1] == misspeled) count++;
        else break;
    }
    printf("%d\n", count);

    for (int i = index - count + 1, j = 0; j < count; i++, j++) {
    int n = i, k = 0; char b[12];
    while (n) { b[k++] = n % 10 + '0'; n /= 10; } //разбор числа на цифры через остаток от деления
    while (k) putchar(b[--k]); //putchar выводит быстрее чем printf в 10 раз 
    putchar(" \n"[j == count - 1]);
    }

    return 0;
}