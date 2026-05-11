#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 10000000

struct password_node {
    char data[11];
    int copies;
    struct password_node* next;
};

int hash(char* string) {
    int hashcode = 0;
    for (int i = 0; i < strlen(string); i++) {
        hashcode += string[i] * (i + 1);
    }
    return hashcode % MAX;
}

struct password_node* check(struct password_node** hashtable, char* string) {
    int hashcode = hash(string);
    struct password_node* password = hashtable[hashcode];
    while(password) {
        if (strcmp(password -> data, string) == 0) {
            return password;
        }
        password = password -> next;
    }
    return NULL;
}

void append(struct password_node** hashtable, char* string) {
    struct password_node* password = check(hashtable, string);
    if (password) {
        password -> copies++;
        return;
    }

    int hashcode = hash(string);
    password = malloc(sizeof(struct password_node));
    strcpy(password -> data, string);
    password -> copies = 1;
    password -> next = hashtable[hashcode];
    hashtable[hashcode] = password;
}

int main() {
    int n, type;
    scanf("%d", &n);
    static struct password_node* hashtable[MAX] = {NULL};
    char password[11], substring[11];
    for (int count = 0; count < n; count++) {
        scanf("%d%s", &type, password);
        if (type == 1) {
            char local_seen[60][11];
            int local_cnt = 0;
            for (int i = 0; i < strlen(password); i++) {
                for (int j = i; j < strlen(password); j++) {
                    int len = j - i + 1;
                    strncpy(substring, password + i, len);
                    substring[len] = '\0';
                    int is_dup = 0;
                    for (int k = 0; k < local_cnt; k++) {
                        if (strcmp(local_seen[k], substring) == 0) {
                            is_dup = 1;
                            break;
                        }
                    }
                    if (!is_dup) {
                        strcpy(local_seen[local_cnt++], substring);
                        append(hashtable, substring);
                    }
                }
            }
        } else {
            if (check(hashtable, password)) printf("%d\n", check(hashtable, password) -> copies);
            else printf("%d\n", 0);
        }
    }
    return 0;
}