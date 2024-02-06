#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to evaluate a single term
int evalTerm(int A, int B, int C, char *term) 
{
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
    //Check for correct argument number
    if (argc != 2) 
    {
        printf("The format is: ./*name* \"ABC + AC'\"");
        return 1;
    }
    // Get the Boolean function from command-line argument
    char *function = argv[1];
    
    printf("Truth table of %s:\n", function);
    printf("A B C |  F\n");
    printf("------|--\n");
    // Print each term
    for (int A = 0; A <= 1; A++) 
    {
        for (int B = 0; B <= 1; B++) 
        {
            for (int C = 0; C <= 1; C++) 
            {
                // Since strtok() function modified the string, use a temporary function and initilized a new string each loop
                char *tempFunction = (char*) malloc (sizeof (function)*sizeof(char)) ;
                strcpy (tempFunction,function);
                // Get the first token of the tempFunction string, Tokenize the function based on '+'
                char *term = strtok (tempFunction, " .,-:+");
                // Initialize 'output' outside the tokenized while loop so that 'output' will reset and check for a new term (Ex: 000 -> 001 'output' will reset to 0)
                int output = 0;

                // Walk through other tokens 
                while (term  != NULL)
                {
                    // Evaluate the function for each combination of A, B, C
                    output = output || evalTerm (A, B, C, term); 
                    //printf("%s\n", term);
                    term = strtok (NULL, " .,-:+");
                }
                printf("%d %d %d | %d\n", A, B, C, output);
                //Free the tempFunction string
                free(tempFunction);
            }
        }
    }
    return 0;
}

//Assign argument to each outputs, last resort if cant tokenize strings
//output1 = evalTerm (A, B, C, term1);
//output2 = evalTerm (A, B, C, term2);
//output3 = evalTerm (A, B, C, term3);
//output =  output1 || output2 || output3;
//printf("%d\t%d\t%d\t%d\n", A, B, C, output);