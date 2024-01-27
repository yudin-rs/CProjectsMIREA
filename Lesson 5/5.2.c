#include <stdio.h>
#include <string.h>
#define MAX_DIGITS 1000

typedef union {
    int digits[MAX_DIGITS];
    char str[MAX_DIGITS + 1];
} NumberRepresentation;

typedef struct {
    NumberRepresentation representation;
    int length;
} LongNumber;

LongNumber initLongNumber() {
    LongNumber num;
    num.length = 0;
    memset(num.representation.digits, 0, sizeof(num.representation.digits));
    return num;
}

LongNumber add(LongNumber num1, LongNumber num2) {
    LongNumber result = initLongNumber();
    int carry = 0;

    for (int i = 0; i < MAX_DIGITS; i++) {
        int sum = carry;
        if (i < num1.length) sum += num1.representation.digits[i];
        if (i < num2.length) sum += num2.representation.digits[i];

        result.representation.digits[i] = sum % 10;
        carry = sum / 10;

        if (result.length <= i && result.representation.digits[i] != 0) {
            result.length = i + 1;
        }
    }

    return result;
}

LongNumber multiply(LongNumber num1, LongNumber num2) {
    LongNumber result = initLongNumber();

    for (int i = 0; i < num1.length; i++) {
        int carry = 0;

        for (int j = 0; j < num2.length || carry; j++) {
            int product = carry + result.representation.digits[i + j];

            if (j < num2.length) {
                product += num1.representation.digits[i] * num2.representation.digits[j];
            }

            result.representation.digits[i + j] = product % 10;
            carry = product / 10;

            if (result.length <= i + j && result.representation.digits[i + j] != 0) {
                result.length = i + j + 1;
            }
        }
    }

    return result;
}

void printNumber(LongNumber num) {
    for (int i = num.length - 1; i >= 0; i--) {
        printf("%d", num.representation.digits[i]);
    }
    printf("\n");
}

int main() {
    char num1Str[MAX_DIGITS], num2Str[MAX_DIGITS];
    printf("Enter the first number: ");
    scanf("%s", num1Str);
    printf("Enter the second number: ");
    scanf("%s", num2Str);

    LongNumber num1 = initLongNumber();
    LongNumber num2 = initLongNumber();

    // Initialize LongNumber from input
    for (int i = strlen(num1Str) - 1; i >= 0; i--) {
        num1.representation.digits[num1.length++] = num1Str[i] - '0';
    }

    for (int i = strlen(num2Str) - 1; i >= 0; i--) {
        num2.representation.digits[num2.length++] = num2Str[i] - '0';
    }

    LongNumber result = multiply(num1, num2);

    printf("Multiplication result: ");
    printNumber(result);

    return 0;
}
