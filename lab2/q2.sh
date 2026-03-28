#!/bin/bash

echo "Compiling 'chekNum.c'..."

cc chekNum.c -o chekNum

echo "Running test 1:..."

./chekNum 100 5 6 7 50 50

echo "Running test 2:..."

./chekNum 100 1 2 3