#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    // Argc - counts the amount of words written in the prompt
    // Argv - an array with said words
    int i;
    char *str, *token;
    // argv[0]     - Program name
    // argv[1]     - num
    // argv[2]..[n] - list of array items
    // If no argument was provided.
    if (argc < 2){
        printf("Error! You must provide an argument\n");
        exit (1);
    }

    // Stores user input into "str" variable
	str = argv[1];

    // Check if the string is empty
    if (str[0] == '\0') {
        printf("Error! The argument cannot be empty.\n");
        exit(1);
    }

    // Checks if there are spaces in the prompt
    for (i = 0; str[i] != '\0'; i++)
        if (isspace(str[i])){
            printf("Error! The argument mustn't have spaces in it.\n");
            exit (1);
        }
    
    // Gets the first word in the string
    token = strtok(str, "_");

    // Loops through the rest of the tokens
    while (token != NULL) {

        // We uppercase each letter in said token
        for (int j = 0; token[j] != '\0'; j++)
            token[j] = toupper(token[j]);

        printf("%s\n", token);

        // Gets the rest of the words
        token = strtok(NULL, "_");
    }
    
	return 0;
}