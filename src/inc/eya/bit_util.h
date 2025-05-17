#ifndef SE_BIT_UTIL_H
#define SE_BIT_UTIL_H

#include "static_cast.h"
#include "type_util.h"

/**
 * @def eya_bit_sign_type_pos(T)
 * @brief Determines the sign bit position for type T
 * @param T Signed integer type (e.g., int)
 * @return Position of the sign bit (0-based index)
 *
 * @note Implemented as macro. Requires eya_type_bits(T) definition
 *
 * Example:
 * @code
 * int pos = eya_bit_sign_type_pos(int); // 31 for 32-bit int
 * @endcode
 */
#define eya_bit_sign_type_pos(T) (eya_type_bits(T) - 1)

/**
 * @def eya_bit_sign_type(T)
 * @brief Generates a value with the sign bit set for type T
 * @param T Signed integer type (e.g., int)
 * @return Value of type T with the most significant bit set
 *
 * @note Implemented as a macro. Requires:
 *       - eya_static_cast(T, val) for literal casting
 *       - eya_bit_sign_type_pos(T) to get sign bit position
 *
 * Example:
 * @code
 * int val = eya_bit_sign_type(int); // 0x80000000 (interpreted as -2147483648)
 * @endcode
 */
#define eya_bit_sign_type(T) (eya_static_cast(T, 1) << eya_bit_sign_type_pos(T))

#endif // SE_BIT_UTIL_H