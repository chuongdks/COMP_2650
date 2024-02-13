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

    //Change size depend on how many arguments, program will have error if does not scale the number of arguments
    int size = 0;
    if (argc <= 6)
    {
        size = argc/2;
    }
    else
    {
        size = argc*1000;
    }
    // Allocate memory for arrays
    char *term[size]; // +1 for NULL Terminator if ever use argv/2 for the array number, but it could cause limited number of arguments
    char op[size]; //Increase to argc*10 so that the program could take more than 9 arguments, 1 string argument is superior https://github.com/chuongdks/COMP_2650.git
    
    // Iterate over arguments
    int i = 1;
    int termCount = 0; // Use a counter instead of argv cuz argv might have more and it is more complicated
    int opCount = 0; // If use argv to count the term and operator, will need more duck tape solution
    while (argv[i] != NULL) 
    {
        if (i % 2 == 0) // If the argument position is even, it is an operator
        {
            op[opCount++] = argv[i][0]; // Increase the Operator Counter
        }
        else // Odd position, it is a term
        {
            term[termCount++] = argv[i]; // Increase the Term Counter
        }
        i++;
    }

    // Null-terminate the arrays to deal with weird symbols when print them out. Due to uninitialized memory or accessing beyond the allocated memory
    op[opCount] = '\0'; // Null-terminate op array
    term[termCount] = NULL;   // Null-terminate term array

    // Print terms
    int j = 0;
    printf ("Truth Table of: ");
    while (term[j] != NULL || op[j] != '\0') 
    {
        printf("%s %c ", term[j], op[j]);
        j++;
    }

    // Check if operators is '+'
    j = 0;
    while (op[j] != '\0') 
    {
        if (op[j] != '+') 
        {
            printf("Error: Invalid operator. The correct arguments is: %s \"ABC\" + \"AC'\" + \"B'\" + \"BC'\"...\n", argv[0]);
            return 1;
        }
        j++;
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
                for (int i = 0; i < termCount; i++)
                {
                    // Evaluate the function for each combination of A, B, C
                    output = output || evalTerm (A, B, C, term[i]); 
                    //printf("%s\n", term);
                }
                printf("%d %d %d |  %d\n", A, B, C, output);
                
            }
        }
    }
    return 0;
}
