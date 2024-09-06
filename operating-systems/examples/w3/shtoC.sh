#!/bin/bash

# concatenate text and store into prog.c until the keyboard EOF is seen

cat > prog.c << EOF

// this will be stored into prog.c as the C source code

#include <stdio.h>
#define SIZE 10

int main(void) {

    for(int i = 0; i < SIZE; i++){
        printf("Hello %d!\n", i);
    }

}

return 0;

EOF
# end-of-file waypoint

gcc prog.c -o prog
./prog
