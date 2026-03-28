#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // Argc - counts the amount of words written in the prompt
    // Argv - an array with said words
    int num, size, i, j;

    // argv[0]     - Program name
    // argv[1]     - num
    // argv[2]..[n] - list of array items

    // And because there's a need for at least 2 items, argc must be at least 4.
    if (argc < 4){
        printf("Error! Array must have at least 2 numbers\n");
        exit(1);
    }
    
    // Converts user input into int
	num = atoi(argv[1]);

    // The size of the array is argv[2] + ... + argv[n] == the size of argc - "Program name" and "num"
    size = argc - 2;
    int array[size];
    
    // Puts numbers into an array
    for (i = 0; i < size; i++)
        array[i] = atoi(argv[i + 2]);
    
    // Checks if there are two numbers in "array" that add up to "num"
    for (i = 0; i < size; i++)
    {
        for (j = i + 1; j < size; j++)
            if ((array[i] + array[j]) == num){
                printf("2 numbers exist : %d + %d = %d\n", array[i], array[j], num);
                return 0;
            }
    }
    printf("2 numbers do no exist\n");
	return 0;
}