#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Argc - counts the amount of words written in the prompt
    // Argv - an array with said words
    int i = 0, j, k, len;
    char *str;

    // If no argument was provided
    if(argc < 2) {
        printf("\nERROR\n");
        exit(1);
    }

    // Stores user input into "str" variable
    str = argv[1];
    // Gets the length of "srt"
    len = strlen(str);
    // Creates a buffer for the current word
    char res[len + 1];

    // Loops through the entire string
    while(i < len) {
        j = i; // Current position in the source string
        k = 0; // Current position in our result buffer

        // Processes characters until an underscore or the end of the string is hit
        while(str[j] != '_' && str[j] != '\0') {
            
            // Checks for spaces
            if (str[j] == ' ')
            {
                printf("\nNo spaces allowed!");
                exit(1);
            }
            
            // Lower to uppercase conversion
            if(str[j] >= 'a' && str[j] <= 'z')
                res[k] = str[j] - 32;
            else
                res[k] = str[j];

            j++; // Moves to the next character in the source
            k++; // Moves to the next position in the result buffer
        }

        // Last character must be a '\0'
        res[k] = '\0';
        printf("%s\n", res);

        // Moves the main index 'i' to the character immediately after the underscore
        i = j + 1;
    }
    return 0;
}