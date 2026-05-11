#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 100000

struct node {
    int list[6];
    struct node* next;
};

bool check_rear(int* first, int* second, int position) {
    for (int i = 0; i < 6; i++) {
        if (first[i] != second[((position - i) % 6 + 6) % 6]) return false;
    }
    return true;
}

bool check_front(int* first, int* second, int position) {
    for (int i = 0; i < 6; i++) {
        if (first[i] != second[(position + i) % 6]) return false;
    }
    return true;
}

bool compare(int* first, int* second) {
    for (int i = 0; i < 6; i++) {
        if (first[0] == second[i]) {
            if (check_front(first, second, i) || check_rear(first, second, i)) return true;
        }
    }
    return false;
}

int sum(int* mas) {
    int summ = 0;
    for (int i = 0; i < 6; i++) {
        summ += mas[i];
    }
    return summ % SIZE;
}

int main() {
    int n, pos;
    scanf("%d", &n);
    static struct node* matrix[SIZE] = {NULL};
    for (int i = 0; i < n; i++) {
        struct node* snow = malloc(sizeof(struct node));
        for (int j = 0; j < 6; j++) {
            scanf("%d", &snow -> list[j]);
        }
        pos = sum(snow -> list);
        
        struct node* current = matrix[pos];
        while(current != NULL) {
            if (compare(snow -> list, current -> list)) {
                printf("Twin snowflakes found.\n");
                return 0;
            } else current = current -> next;
        }
        snow -> next = matrix[pos];
        matrix[pos] = snow;
    }
    
    printf("No two snowflakes are alike.\n");
    
    return 0;
}