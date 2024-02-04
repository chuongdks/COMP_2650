#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to evaluate a single term
int evalTerm(int A, int B, int C, char *term) {
    int result = 1; // Initialize result to 1 (true)
    int len = strlen(term);
    for (int i = 0; i < len; i++) 
    {
        if (term[i] == 'A') 
        {
            result = result && A;
        } 
        else if (term[i] == 'B') 
        {
            result = result && B;
        } 
        else if (term[i] == 'C') 
        {
            result = result && C;
        }
        else if (term[i] == '\'') 
        {
            // Negate the next variable
            if (term[i+1] == 'A') 
            {
                result = result && !A;
            } 
            else if (term[i+1] == 'B') 
            {
                result = result && !B;
            } 
            else if (term[i+1] == 'C') 
            {
                result = result && !C;
            }
            i++; // Skip the next character (negation symbol)
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) 
    {
        printf("Usage: %s \"Boolean function\"\n", argv[0]);
        return 1;
    }

    // Get the Boolean function from command-line argument
    char *function = argv[1];
    // Get the first token, Tokenize the function based on '+'
    char *term = strtok(function, " .,-:+");
    
    //
    while (term != NULL) 
    {
        // Print each term
        printf("Term:%s\n", term);
        for (int A = 0; A <= 1; A++) 
        {
            for (int B = 0; B <= 1; B++) 
            {
                for (int C = 0; C <= 1; C++) 
                {
                    // Evaluate the function for each combination of A, B, C
                    int output = 0;
                    output = output || evalTerm (A, B, C, term);
                    printf("%d %d %d\n", A,B,C);
                    //printf("%d\t%d\t%d\t%d\n", A, B, C, output);
                }
            }
        }
        // Move to the next term
        term = strtok (NULL, "+");
    }
    return 0;
}
