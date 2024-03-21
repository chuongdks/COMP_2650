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
    // Exit if over 100 bits
    if (strlen(binary) > 100)
    {
        printf("100 bits is the limit\n");
        exit(1);
    }

    // Check if the binary string contains only 0s and 1s
    for (int i = 0; i < strlen(binary); i++) 
    {
        if (binary[i] != '0' && binary[i] != '1') 
        {
            printf("Non binary number, try again\n");
            exit(1);
        }
    }
}

void addZerosOrOnes (char **binary, int new_length) 
{
    // Old binary String
    char *temp = *binary;
    int original_size = strlen(temp);

    // Allocate memory for the new binary string
    *binary = malloc((new_length + 1) * sizeof(char));

    // Shift the OG content to the right String and padded with '0' or '1' on the left String
    for (int i = 1; i <= original_size; i++) 
    {
        int new_loop = new_length - i;
        int old_loop = original_size - i;
        (*binary)[new_loop] = temp[old_loop];
        // printf("new_loop: %d, old_loop: %d\n", new_loop, old_loop);
    }

    // Padded the rest of the binary String on the left with '0'
    for (int i = 0; i < new_length - original_size; i++) 
    {
        if ((*binary)[new_length - original_size] == 0)
        {
            (*binary)[i] = '0';
        }
        else
        {
            (*binary)[i] = '1';
        }
    }

    // Terminate the string with null character
    (*binary)[new_length] = '\0';

    // printf("Shifted number: %s\n", *binary);
}

char FullAdder (char A, char B, char C, char *S) 
{
    // Logic like the first lab1.c
    int sum = (A - 48) + (B - 48) + (C - 48);
    S[0] = (sum % 2) + 48; // For Full-Adder, Sum = (# of Inputs % 2)
    return (sum / 2) + 48; // For Full-Adder, Carry = (# of Inputs / 2)
}

char AddSub(char *N1, char *N2, char C, char *R) 
{
    int N1_size = strlen(N1);
    int N2_size = strlen(N2);
    int biggerNumber;
    char C1, C0;

    // Choose which Binary string is larger
    if (N1_size > N2_size) 
    {
        biggerNumber = N1_size;
        addZerosOrOnes(&N2, N1_size);
    }
    else   
    {
        biggerNumber = N2_size;
        addZerosOrOnes(&N1, N2_size);
    }

    printf("Same length: N1 = %s\t N2 = %s\n", N1, N2);

    // Allocate memory for the Result binary string
    R = malloc((biggerNumber+1) * sizeof(char));

    // 1's Compliment the second binary number if the first Carry bit = 1
    if (C == '1') 
    {
        complement(N2);
    }

    // Assign the Resulting bit one by one Starting from the LSB to MSB
    for (int i = biggerNumber - 1; i >= 0; i--) 
    {
        C = FullAdder(N1[i], N2[i], C, &R[i]);

        // Assign the carry bit of the MSB and the one next to the MSB
        if (i == 1)
        {
            C1 = C;
        }
        else if (i == 0)
        {
            C0 = C;
        }
    }

    // Terminate the string with null character
    R[biggerNumber] = '\0';

    // If the carry into the sign bit position and the carry out of the sign bit position are different --> Overflow signed number
    // Could increase the size of result by 1 and added the overflow bit, OR just put the carry bit next to it, cheesing.
    if (C1 != C0)
    {
        printf("%s + %s = %c%s\n", N1, N2, C, R);
    }
    else
    {
        printf("%s + %s = %s\n", N1, N2, R);
    }
  
    return C;
}

int main(int argc, char *argv[]) {
    if (argc != 4) 
    {
        printf("Full Adder/subtractor of up to 100 bits numbers\n");
        printf("Usage: enter a bit string +/- bit string\n");
        printf("E.g.: ./LinuxAddSub 1000111111111111101011 + 1111110000111101111\n");
        return 1;
    }

    // Assign binary number and operator from cmd line arguments
    char *binary_num1 = argv[1];
    char operator = argv[2][0];
    char *binary_num2 = argv[3];

    // Check correct operator
    if (operator != '+' && operator != '-') 
    {
        printf("Full Adder/subtractor of up to 100 bits numbers\n");
        printf("Usage: enter a bit string +/- bit string\n");
        printf("E.g.: ./LinuxAddSub 1000111111111111101011 + 1111110000111101111\n");
    }

    printf("You entered %s and %s\n", binary_num1, binary_num2);
    parseBinary(binary_num1);
    parseBinary(binary_num2);

    char *result;

    char carry = AddSub(binary_num1, binary_num2, (operator == '-') ? '1' : '0', result);

    return 0;
}


/*
* Ask chatgpt why u need extra asterisk in function addZerosOrOnes()
* The reason why the changes you made to binary inside the addZeros function are not reflected in main is because you're passing binary_num1 and binary_num2 as pointers to characters (char*). 
* When you pass these pointers to the addZeros function, you're essentially passing the address of the strings stored in argv, not the actual arrays themselves. 
* Therefore, modifying binary inside addZeros only modifies the local variable binary within the function, not the original strings binary_num1 and binary_num2 in main.

* To make the changes reflect in main, you need to pass the address of the pointers (char**) so that you can modify the pointers themselves. Here's how you can do it:
*/