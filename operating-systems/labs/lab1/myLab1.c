// First 10 terms of Fibbonacci sequence

#include <stdio.h>

#define DIGITS 10

int main(void) {

    int num1 = 0;
    int num2 = 1;
    int nextNum = 1;

    for (int i = 0; i < DIGITS; i++) {
        printf("%d\n", num1);
        num1 = num2;
        num2 = nextNum;
        nextNum = num1 + num2;
    }

    return 0;
}

