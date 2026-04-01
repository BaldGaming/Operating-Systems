#!/bin/bash

echo "Compiling 'catByAt.c'..."

cc catByAt.c -o catByAt

echo -e "\nRunning test for: '$1'...\n"

./catByAt "$1"