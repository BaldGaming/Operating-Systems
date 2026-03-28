#!/bin/bash

echo "START"

echo "Enter folder name: $1"

echo "Creating new folder $1..."

mkdir "$1"

cd "$1"

echo "Creating new file '$USER'..."

touch "$USER.txt"

man ls | head -n 5 > "$USER.txt"

man ls | tail -n 5 >> "$USER.txt"

chmod -w "$USER.txt"

echo "Creating new file 'home.txt'..."

echo "$HOME" > "home.txt"

echo "END"