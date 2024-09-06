#include <stdio.h>
#include <stdlib.h>

int main() {

        int a = 0;

        printf("[CHILD] I'm the child process\n");
        
        for (int i = 0; i < 20; i++, a += 2) {
            printf("[CHILD] i=%d, a=%d\n", i, a);
        }

        exit(EXIT_SUCCESS);
}
