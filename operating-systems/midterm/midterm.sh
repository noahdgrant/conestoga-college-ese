#!/bin/bash

# Operating systems midterm
# Noah Grant

# Create c file
cat > multiply.c << EOF

#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]){
    FILE *fp;
    int x;
    int multiplier;
    char *fname;
   
    if (argc != 3) {
        // need a multiplier a file name to invoke this program properly!
        return 1;
    }
   
    multiplier = atoi (argv[1]);
    fname = argv[2];
    
    fp = fopen (fname, "w");
    if (fp == NULL){
        //Invalid file name!!
        return 2;
    }

    for (x = 1; x <= 10; x++) {
        fprintf (fp, "%4d x %2d = %d\n", multiplier, x, multiplier * x);
    }
    
    fclose(fp);
    return 0;
}

EOF
# end-of-file waypoint

# Compile program
gcc multiply.c -o multiply

# Menu
echo "OS Midterm Q2"
echo "1. Run multiply.c"
echo "2. Help"
echo "3. Quit"

# Main program loop
while [ true ]
do
    echo -n "> "
    read cmd
    case $cmd in
    1)
        read -r -p "MULTIPLIER FILENAME: " -a info

        echo ${info[0]}
        echo ${info[1]}
        
        ./multiply ${info[0]} ${info[1]}

        # Check multiply.c return value
        case $? in
        0)
            echo "multiply.c successful..."
            echo "contents are..."
            cat ${info[1]}
            rm ${info[1]}
            ;;
        1)
            echo "need a multiplier and filename to invoke this program properly!"
            ;;
        2)
            echo "Invalid file name"
            ;;
        esac
        ;;
    2)
        echo "Usage: ./multiply MULTIPLIER FILENAME"
        echo "Otherwise Google it or ask Scott"
        ;;
    3)
        # Quit command
        break
        ;;
    *)
        echo "Invalid command"
        ;;
    esac
done
