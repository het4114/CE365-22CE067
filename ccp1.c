#include <stdio.h>
#include <string.h>

int check(char* str) {
    int len = strlen(str);
    if (len < 2) return 0;

    int i = 0;
    while (i < len && str[i] == 'a') {
        i++;
    }
    if (i == len) return 0;

    if (str[i] != 'b') return 0;
    i++;
    if (i < len && str[i] == 'b') {
        i++;
    }

    return i == len;
}

int main() {
    char s[100];
    fgets(s, 100, stdin);
    s[strcspn(s, "\n")] = 0;

    if (check(s)) {
        printf("Valid string\n");
    } else {
        printf("Invalid string\n");
    }
    return 0;
}
