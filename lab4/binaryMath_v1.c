#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void complement (char *binary) 
{
    // Calculate 1's complement
    for (int i = 0; i < strlen(binary); i++) 
    {
        binary[i] = ((binary[i] == '0') ? '1' : '0');
    }
}

void parseBinary (char *binary) 
{
    // Check if the binary string contains only 0s and 1s
    for (int i = 0; i < strlen(binary); i++) 
    {
        if (binary[i] != '0' && binary[i] != '1') 
        {
            printf("Error: Invalid binary number\n");
            exit(1);
        }
    }
}

void addZeros (char **binary, int new_length) 
{
    char *temp = *binary;
    int original_size = strlen(temp);

    // Allocate memory for the new binary string
    *binary = malloc((new_length + 1) * sizeof(char));

    // Shift the OG content to the right String and padded with '0' on the left String
    for (int i = 0; i < original_size; i++) 
    {
        int new_loop = new_length - original_size + i;
        int old_loop = i;
        (*binary)[new_loop] = temp[old_loop];
        printf("new_loop: %d, old_loop: %d\n", new_loop, old_loop);
    }

    // Padded the rest of the binary String on the left with '0'
    for (int i = 0; i < new_length - original_size; i++) 
    {
        (*binary)[i] = '0';
    }

    // Terminate the string with null character
    (*binary)[new_length] = '\0';

    // printf("Shifted number: %s\n", *binary);
}

char FullAdder (char A, char B, char C, char *S) 
{

    int sum_bit = (A - '0') + (B - '0') + (C - '0');
    S[0] = (sum_bit % 2) + '0'; // For Full-Adder, Sum = (# of Inputs % 2)
    return (sum_bit / 2) + '0'; // For Full-Adder, Carry = (# of Inputs / 2)
}

char AddSub(char *N1, char *N2, char C, char *R) 
{
    int size = sizeof(R) + 1;
    printf("Carry Original: %c\n", C);

    if (C == '1') 
    {
        complement(N2);
    }

    for (int i = size - 1; i >= 0; i--) 
    {
        C = FullAdder(N1[i], N2[i], C, &R[i]);
        printf("Loop number %d:\n", i);
        printf("Sum: %c\n", R[i]);
        printf("Carry: %c\n", C);
    }

    return C;
}

int main(int argc, char *argv[]) {
    if (argc != 4) 
    {
        printf("Usage: %s <binary_number1> <+ or -> <binary_number2>\n", argv[0]);
        return 1;
    }

    char *binary_num1 = argv[1];
    char operator = argv[2][0];
    char *binary_num2 = argv[3];

    int N1_size = strlen(binary_num1);
    int N2_size = strlen(binary_num2);
    int biggerNumber;

    if (N1_size > N2_size) 
    {
        biggerNumber = N1_size;
        addZeros(&binary_num2, N1_size);
    }
    else   
    {
        biggerNumber = N2_size;
        addZeros(&binary_num1, N2_size);
    }

    printf("%s\n", binary_num1);
    printf("%s\n", binary_num2);

    parseBinary(binary_num1);
    parseBinary(binary_num2);

    if (operator != '+' && operator != '-') 
    {
        printf("Error: Operator must be '+' or '-'.\n");
        return 1;
    }

    char result[biggerNumber];
    
    char carry = AddSub(binary_num1, binary_num2, (operator == '-') ? '1' : '0', result);

    printf("%s\n", result);
    return 0;
}


/*
* The reason why the changes you made to binary inside the addZeros function are not reflected in main is because you're passing binary_num1 and binary_num2 as pointers to characters (char*). 
* When you pass these pointers to the addZeros function, you're essentially passing the address of the strings stored in argv, not the actual arrays themselves. 
* Therefore, modifying binary inside addZeros only modifies the local variable binary within the function, not the original strings binary_num1 and binary_num2 in main.

* To make the changes reflect in main, you need to pass the address of the pointers (char**) so that you can modify the pointers themselves. Here's how you can do it:
*/