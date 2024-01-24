#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get2Complement (char *binary) 
{
    // Calculate 1's complement
    for (int i = 0; i < strlen(binary); i++) 
    {
        binary[i] = ((binary[i] == '0') ? '1' : '0');
    }

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
    binary [strlen(binary)] = '\0'; //add a null at the end of the binary string
}

void Parse (char *binary) 
{
    int size = strlen(binary), decimal = 0;
    // Check if the binary string contains only 0s and 1s
    for (int i = 0; i < size; i++) 
    {
        if (binary[i] != '0' && binary[i] != '1') 
        {
            printf("Error: Invalid binary number\n");
            exit(0);
        }
    }

    // Check if the MSB is 1 (indicating a negative number)
    int isNegative = (binary[0] == '1');
    //If the binary is a negative number, Flip the bit -> Add 1 -> and change # = -#
    if (isNegative) 
    {
        get2Complement (binary);
    }

    // Loop through the binary array in reverse order to check if the decimal value of binary is within -128, 127
    for (int i = size - 1; i >= 0; i--) 
    {
        // Convert character '0' or '1' to integer 0 or 1
        int bit = binary[i] - '0';
        
        // Multiply the current bit by 2 to the power of its position (LSB to MSB)
        // and add it to the decimal sum
        decimal += bit * (1 << (size - 1 - i)); //(1 << (size - 1 - i)) this part shift 1 to the left of 0, 1, 2, 3,...7
    }

    // Adjust the decimal value if it's a negative number
    if (isNegative) 
    {
        decimal = -decimal;
        get2Complement (binary);
    }

    //If the number is larger than 127, return the program
    if (decimal > 127 || decimal < -128)
    {
        printf("Error: Binary number is larger than 127 or lower than -128. Enter range from -128 to 127\n");
        exit(0);
    }
    printf("The decimal number is: %d\n", decimal);
}

void Add (char *num1, char op, char *num2, char *result) 
{
    int decimal = 0, size = strlen(num1);
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

    // Check if the MSB is 1 (indicating a negative number)
    int isNegative = (result[0] == '1');
    //If the binary is a negative number, Flip the bit -> Add 1 -> and change # = -#
    if (isNegative) 
    {
        get2Complement (result);
    }

    // Loop through the binary array in reverse order to check if the decimal value of binary is within -128, 127
    for (int i = size - 1; i >= 0; i--) 
    {
        // Convert character '0' or '1' to integer 0 or 1
        int bit = result[i] - '0';
        
        // Multiply the current bit by 2 to the power of its position (LSB to MSB)
        // and add it to the decimal sum
        decimal += bit * (1 << (size - 1 - i)); //(1 << (size - 1 - i)) this part shift 1 to the left of 0, 1, 2, 3,...7
    }

    // Adjust the decimal value if it's a negative number
    if (isNegative) 
    {
        decimal = -decimal;
        get2Complement (result);
    }

    //If the number is larger than 127, return the program
    if (decimal > 127 || decimal < -128)
    {
        printf("Error: Result of Binary number is larger than 127 or lower than -128. Enter range from -128 to 127\n");
        exit(0);
    }

    // Print the result
    printf("%s %c %s = %s\n", num1, op, num2, result);
    printf("The result decimal number is: %d\n", decimal);
}

int main(int argc, char *argv[]) {
    if (argc != 4) 
    {
        printf("Error: Too many number of arguments. The format is < Binary1 > < +/- > < Binary2 >\n");
        return 1;
    }

    char *num1 = argv[1];
    char op = argv[2][0];
    char *num2 = argv[3];

    int resultSize = strlen(num1);
    char result[resultSize];
    result[resultSize] = '\0';

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

    // Check if the strings are correct binary number
    Parse (num1);
    Parse (num2);

    // Call the function with the provided arguments
    Add (num1, op, num2, result);
    return 0;
}