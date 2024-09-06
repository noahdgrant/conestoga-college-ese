#!/bin/bash

# Operating Systems Assignment 2
# Author: Noah Grant

# Print main menu
echo "
MENU SYSTEM

0. Change directory
1. List file details in current folder
2. Create backup of current files in user specified folder
3. Create a ZIP archive of current files in user specified archive
4. Output all text files one page at a time in current folder
5. Delete files in current folder
6. Output help information
7. Exit"

# Main loop
while [ "$cmd" != "7" ]
do
    echo
    pwd
    read cmd

    case $cmd in
    0)
        echo "New working directory (path to do directory):"
        read newDir
        cd $newDir
        ;;
    1)
        ls -l
        ;;
    2)
        echo "Destination folder (path to backup):"
        read dir

        # Check if folder already exists
        if [ -d $dir ]
        then
            echo "Folder ($dir) already exists"
        else
            mkdir $dir
            cp -r * $dir
        fi
        ;;
    3)
        echo "Zip filename (path to zip):"
        read filename

        zip -r $filename ./*
        ;;
    4)
        cat *.txt | more
        ;;
    5)
        rm -r *
        ;;
    6)
        echo "====== Help Information ======"
        echo "If you are having trouble changing directories, creating a backup, or ziping"
        echo "a file, try including a './' for 'current directory' or a '..' for 'parent directory'"
        echo
        echo "====== IT Top Tips ======"
        echo "Try restarting it"
        echo "Try unplugging it"
        echo "Try Googling the issue"
        echo "Try again tomorrow"
        echo
        echo "Contact Info:"
        echo "Phone: 555-123-4567"
        echo "Email: IT@conestogac.on.ca"
        ;;
    7)
        echo "Exiting..."
        ;;
    *) # Default
        echo "Invalid command"
        ;;
    esac
done

