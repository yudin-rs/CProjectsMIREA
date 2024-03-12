#include <stdlib.h>
#include "longnum_utils.h"

LongNumber multiply(LongNumber numOne, LongNumber numTwo) {
    LongNumber result = init();
    result.represent.digits = (int *) calloc(numOne.length + numTwo.length, sizeof(int));

    for (int i = 0; i < numOne.length; i++) {
        int carry = 0;

        for (int j = 0; j < numTwo.length || carry; j++) {
            int product = carry + result.represent.digits[i + j];

            if (j < numTwo.length) {
                product += numOne.represent.digits[i] * numTwo.represent.digits[j];
            }

            result.represent.digits[i + j] = product % 10;
            carry = product / 10;

            if (result.length <= i + j && result.represent.digits[i + j] != 0) {
                result.length = i + j + 1;
            }
        }
    }

    return result;
}
