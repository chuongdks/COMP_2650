#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseBinary(char *binary_str) {
    for (int i = 0; binary_str[i] != '\0'; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            printf("Error: Binary strings can only contain 0s and 1s.\n");
            exit(1);
        }
    }
}

void addZeros(char *binary_str, int length) {
    int original_length = strlen(binary_str);
    int i, j;

    for (i = length - 1, j = original_length - 1; j >= 0; i--, j--) {
        binary_str[i] = binary_str[j];
    }

    for (i = 0; i < length - original_length; i++) {
        binary_str[i] = '0';
    }
}

void complement(char *binary_str) {
    for (int i = 0; binary_str[i] != '\0'; i++) {
        binary_str[i] = (binary_str[i] == '0') ? '1' : '0';
    }
}

char FullAdder(char A, char B, char C, char *S) {
    int sum_bit = (A - '0') + (B - '0') + (C - '0');
    S[0] = (sum_bit % 2) + '0';
    return (sum_bit / 2) + '0';
}

char AddSub(char *N1, char *N2, char C, char *R) {
    int N1_len = strlen(N1);
    int N2_len = strlen(N2);
    int i;
    
    if (N1_len != N2_len) {
        printf("Error: Binary numbers must have the same length.\n");
        exit(1);
    }

    int result_len = N1_len + 1;
    char carry = C;

    addZeros(N1, result_len);
    addZeros(N2, result_len);

    if (C == '1') {
        complement(N2);
    }

    for (i = result_len - 1; i >= 0; i--) {
        carry = FullAdder(N1[i], N2[i], carry, &R[i]);
    }

    return carry;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <binary_number1> <+ or -> <binary_number2>\n", argv[0]);
        return 1;
    }

    char *binary_num1 = argv[1];
    char operator = argv[2][0];
    char *binary_num2 = argv[3];

    parseBinary(binary_num1);
    parseBinary(binary_num2);

    if (operator != '+' && operator != '-') {
        printf("Error: Operator must be '+' or '-'.\n");
        return 1;
    }

    int result_len = strlen(binary_num1) + 1;
    char result[result_len];

    char carry = AddSub(binary_num1, binary_num2, (operator == '-') ? '1' : '0', result);

    printf("%s\n", result);
    return 0;
}
