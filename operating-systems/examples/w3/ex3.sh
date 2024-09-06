#!/bin/bash

echo "username: $USER"
echo "username: $USERNAME"

if [ "$USER" = "noah" ]
then
    echo "$USER is the expected user"
else
    echo "$USER is not the expected user"
fi
