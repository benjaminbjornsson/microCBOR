#include "exp2_uint.h"

uint64_t exp2_uint(uint64_t exponent) {
    return 0b01 << exponent;
}