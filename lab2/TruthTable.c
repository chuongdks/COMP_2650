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
            if (i + 1 < len && term[i+1] == '\'')
                result = result && !A;
            else
                result = result && A;
        } 
        else if (term[i] == 'B') 
        {
            if (i + 1 < len && term[i+1] == '\'')
                result = result && !B;
            else
                result = result && B;
        } 
        else if (term[i] == 'C') 
        {
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
    // int A = 0, B = 0, C = 0;
    int outputTemp = 0, outputFinal = 0;
    if (argc != 2) 
    {
        printf("Usage: %s \"Boolean function\"\n", argv[0]);
        return 1;
    }

    // Get the Boolean function from command-line argument
    char *function = argv[1];
    // Get the first token, Tokenize the function based on '+'
    char *term = strtok(function, " .,-:+");
    
    // Initialize output outside the term loop
    int output = 0;

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
                    output = evalTerm (A, B, C, term); //output || 
                    //output1 = evalTerm (A, B, C, term1);
                    //output2 = evalTerm (A, B, C, term2);
                    //output =  output1 || output2;
                    //printf("%d\t%d\t%d\t%d\n", A, B, C, output);
                }
            }
        }
        // Move to the next term
        term = strtok (NULL, "+");
    }
    return 0;
}
