#include <eya/numeric_fixed_limits.h>
#include <eya/static_assert.h>

// Unsigned types size validation
eya_static_assert(EYA_U8_T_SIZE == 1, "Size mismatch");
eya_static_assert(EYA_U16_T_SIZE == 2, "Size mismatch");
eya_static_assert(EYA_U32_T_SIZE == 4, "Size mismatch");
eya_static_assert(EYA_U64_T_SIZE == 8, "Size mismatch");

// Signed types size validation
eya_static_assert(EYA_S8_T_SIZE == 1, "Size mismatch");
eya_static_assert(EYA_S16_T_SIZE == 2, "Size mismatch");
eya_static_assert(EYA_S32_T_SIZE == 4, "Size mismatch");
eya_static_assert(EYA_S64_T_SIZE == 8, "Size mismatch");

// Unsigned ranges validation
eya_static_assert(EYA_U8_T_MIN == 0, "Value mismatch");
eya_static_assert(EYA_U8_T_MAX == 255, "Value mismatch");
eya_static_assert(EYA_U16_T_MIN == 0, "Value mismatch");
eya_static_assert(EYA_U16_T_MAX == 65535, "Value mismatch");
eya_static_assert(EYA_U32_T_MIN == 0, "Value mismatch");
eya_static_assert(EYA_U32_T_MAX == 4294967295U, "Value mismatch");
eya_static_assert(EYA_U64_T_MIN == 0, "Value mismatch");
eya_static_assert(EYA_U64_T_MAX == 18446744073709551615ULL, "Value mismatch");

// Signed ranges validation
eya_static_assert(EYA_S8_T_MIN == -128, "Value mismatch");
eya_static_assert(EYA_S8_T_MAX == 127, "Value mismatch");
eya_static_assert(EYA_S16_T_MIN == -32768, "Value mismatch");
eya_static_assert(EYA_S16_T_MAX == 32767, "Value mismatch");
eya_static_assert(EYA_S32_T_MIN == -2147483648LL, "Value mismatch");
eya_static_assert(EYA_S32_T_MAX == 2147483647, "Value mismatch");
eya_static_assert(EYA_S64_T_MIN == (-9223372036854775807LL - 1), "Value mismatch");
eya_static_assert(EYA_S64_T_MAX == 9223372036854775807LL, "Value mismatch");