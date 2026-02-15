#!/bin/bash

if [ "$1" == "1" ]; then
    g++ c_array.cpp -Wall -Wextra -o exec && ./exec
    exit 0
fi

if [ "$1" == "2" ]; then
    g++ vector.cpp -Wall -Wextra -o exec && ./exec
    exit 0
fi

echo "Invalid argument: wanted '1' or '2', got '$1' (blank == not supplied)"
exit 67

