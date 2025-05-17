#ifndef EYA_TYPE_UTIL_H
#define EYA_TYPE_UTIL_H

/**
 * @def eya_type_size(T)
 * @brief Calculates type size in bytes (C implementation)
 * @param T Data type to determine size of
 * @return Size of type T in bytes via sizeof operator
 *
 * Example of use:
 * @code
 * size_t s = eya_type_size(double); // sizeof(double)
 * @endcode
 */
#define eya_type_size(T) sizeof(T)

/**
 * @def eya_type_bits(T)
 * @brief Calculates bit size of type T
 *
 * @param T Data type to determine bit size of
 * @return Number of bits in type T (sizeof(T) * 8)
 *
 * Usage example:
 * @code
 * int bits = eya_type_bits(int); // Returns 32 for 32-bit int
 * @endcode
 */
#define eya_type_bits(T) (eya_type_size(T) * 8)

#endif // EYA_TYPE_UTIL_H