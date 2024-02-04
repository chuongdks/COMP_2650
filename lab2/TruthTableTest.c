#include <stdio.h>
#include <string.h>

// Function to evaluate a single term
int evalTerm(int A, int B, int C, char *term) 
{
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

int main() {
    // Input Boolean function
    char function[100];
    printf("Enter the Boolean function in sum-of-products form: ");
    scanf("%s", function);

    // Print the Boolean function
    printf("Boolean function: %s\n", function);

    // Print the truth table
    printf("Truth Table:\n");
    printf("A\tB\tC\tOutput\n");
    for (int A = 0; A <= 1; A++) 
    {
        for (int B = 0; B <= 1; B++) 
        {
            for (int C = 0; C <= 1; C++) 
            {
                // Evaluate the function for each combination of A, B, C
                int output = 0;
                int len = strlen(function);
                for (int i = 0; i < len; i++) 
                {
                    char term[10];
                    int j = 0;
                    while (function[i] != '+' && i < len) 
                    {
                        term[j++] = function[i++];
                    }
                    term[j] = '\0';
                    output = output || evalTerm(A, B, C, term);
                }
                printf("%d\t%d\t%d\t%d\n", A, B, C, output);
            }
        }
    }
    return 0;
}
