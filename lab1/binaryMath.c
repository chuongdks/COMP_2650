#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkBinary (char *binary) 
{
    // Check if the binary string contains only 0s and 1s
    for (int i = 0; i < strlen(binary); i++) 
    {
        if (binary[i] != '0' && binary[i] != '1') 
        {
            printf("Error: Invalid binary number\n");
            return;
        }
    }
}

void get2Complement (char *binary) 
{
    // Calculate 1's complement
    for (int i = 0; i < strlen(binary); i++) 
    {
        binary[i] = ((binary[i] == '0') ? '1' : '0');
    }
    //printf("\n1's complement binary number: %s", binary);

    // Add 1 to the 1's complement to make a 2's complement
    int carry = 1;
    for (int i = strlen(binary) - 1; i >= 0; i--) 
    {
        if (binary[i] == '1' && carry == 1)
        {
            binary[i] = '0';
        }
        else if (binary[i] == '0' && carry == 1)
        {
            binary[i] = '1';
            carry = 0;
        }
    }
    //printf("\n2's complement binary number: %s\n", binary);
    binary [strlen(binary)] = '\0'; //add a null at the end of the binary string
}

void addBinaryNumbers (char *num1, char op, char *num2, char *result) 
{
    // Check if the strings are correct binary number
    checkBinary(num1);
    checkBinary(num2);

    // If the operator is '-', get 2's complement of the second binary number
    if (op == '-') 
    {
        get2Complement(num2);
    }

    // Add the two binary numbers
    int carry = 0;
    for (int i = strlen(num1) - 1; i >= 0; i--) 
    {
        int sum = (num1[i] - 48) + (num2[i] - 48) + carry; //num[i] - '0' to convert the string '0' and '1' to an integer number (48 - 48 = 0; 49 - 48 = 1)
        result[i] = (sum % 2) + 48; //0 + 0 = 0; 0 + 1 = 1,; only 1 + 1 = 0 carry 1. If the sum = 2, its remainder is 0. At the end add 48 to turn it into a string value again
        carry = sum / 2; //If the sum is 2 then the carry will be equal to 1, else it is 0
    }

    // Print the result
    printf("%s %c %s = %s\n", num1, op, num2, result);
}

int main(void) {
    char num1[9] = {'\0'}, op = '\0', num2[9] = {'\0'};
    //char num1[9] = "01111011", op = '\0', num2[9] = "00111000"; //DEbugging fast
    char string[100];

    printf("Please enter the binary number below. (Format: num1 op num2)\n");
    fgets (string, sizeof(string), stdin);
    sscanf (string, "%s %c %s", num1, &op, num2);

    // scanf("%8s", num1);
    // scanf(" %c", &op);
    // scanf("%8s", num2);
    
    //printf("%s\n", num1);
    //printf("%8c\n", op);
    //printf("%s\n", num2);

    if (op != '+' && op != '-') 
    {
        printf("Error: Invalid operator\n");
        return 1;
    }

    if (strlen (num1) > 8 || strlen (num2) > 8)
    {
        printf("Error: Binary String too big. Use only 8 bits\n");
        return 1;
    }

    int resultSize = strlen(num1);
    char result[resultSize];
    result[resultSize] = '\0';

    // Call the function with the provided arguments
    addBinaryNumbers(num1, op, num2, result);

    return 0;
}