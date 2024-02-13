#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to evaluate a single term
int evalTerm(int A, int B, int C, char *term) 
{
    int result = 1; // Initialize result to 1 (true)
    int len = strlen(term);
    //Loop to evaluate a single term compare to the current set of the Truth Table. Ex: ABC' AND 001, 010, 100,...
    for (int i = 0; i < len; i++) 
    {
        if (term[i] == 'A') 
        {
            //If the next character does not reach max size and is the character " ' ", result is then & !A, else it is & A
            if (i + 1 < len && term[i+1] == '\'')
                result = result && !A;
            else
                result = result && A;
        } 
        else if (term[i] == 'B') 
        {
            //If the next character does not reach max size and is the character " ' ", result is then & !A, else it is & A
            if (i + 1 < len && term[i+1] == '\'')
                result = result && !B;
            else
                result = result && B;
        } 
        else if (term[i] == 'C') 
        {
            //If the next character does not reach max size and is the character " ' ", result is then & !A, else it is & A
            if (i + 1 < len && term[i+1] == '\'')
                result = result && !C;
            else
                result = result && C;
        }
    }
    //printf("Result %d\n", result);
    return result;
}

int main(int argc, char *argv[]) {
    // Check if there are enough arguments
    if (argc < 2) 
    {
        printf("Invalid number of arguments. Example: %s \"ABC\" + \"AC'\" + \"B'\" + \"BC'\"...\n", argv[0]);
        return 1;
    }

    // Print terms
    printf ("Truth Table of: ");
    for (int i = 1; i < argc; i++)
    {
        printf("%s ", argv[i]);
    }

    printf("\n");
    printf("A B C |  F\n");
    printf("------|---\n");
    // Print each term
    for (int A = 0; A <= 1; A++) 
    {
        for (int B = 0; B <= 1; B++) 
        {
            for (int C = 0; C <= 1; C++) 
            {
                // Initialize 'output' outside the tokenized while loop so that 'output' will reset and check for a new term (Ex: 000 -> 001 'output' will reset to 0)
                int output = 0;

                // Walk through other tokens 
                for (int i = 1; i < argc; i++)
                {
                    if (i % 2 != 0)
                    {
                        output = output || evalTerm (A, B, C, argv[i]); 
                    }
                }
                printf("%d %d %d |  %d\n", A, B, C, output);
            }
        }
    }
    return 0;
}