/**
 * @file algorithm_util.h
 * @brief Utility macros for common algorithmic operations
 *
 * This header provides a set of efficient macro implementations for common
 * algorithmic operations such as swapping, copying, filling and comparing
 * memory regions.
 *
 * The macros are type-safe and designed for optimal performance.
 * Key features:
 * - Type-generic operations through macros
 * - Both standard and optimized versions of operations
 * - Support for forward and reverse operations
 * - Memory-safe pointer operations
 *
 * @warning Some macros have specific type requirements and usage constraints.
 *          Always check the documentation before use.
 */

#ifndef EYA_ALGORITHM_UTIL_H
#define EYA_ALGORITHM_UTIL_H

#include "ptr_util.h"

/**
 * @def eya_algorithm_swap(T, a, b)
 * @brief Swaps values of two variables of the same type
 * @param T Data type of variables
 * @param a First variable
 * @param b Second variable
 * @warning Avoid expressions with side effects (e.g., i++) in parameters
 *
 * @details This macro performs a standard swap operation using a temporary variable.
 *          It works for any data type that supports assignment.
 *
 * Example:
 * @code
 * int x = 1, y = 2;
 * eya_algorithm_swap(int, x, y);
 * @endcode
 */
#define eya_algorithm_swap(T, a, b)                                                                \
    do                                                                                             \
    {                                                                                              \
        T temp = (a);                                                                              \
        (a)    = (b);                                                                              \
        (b)    = temp;                                                                             \
    } while (0)

/**
 * @def eya_algorithm_swap_no_temp(a, b)
 * @brief Swaps integer values without temporary variable using XOR operation
 * @param a First integer variable
 * @param b Second integer variable
 * @note Only works for integer types.
 *       Slightly faster but less readable than standard swap.
 * @warning Avoid using with floating-point numbers or pointers
 *
 * @details Implements XOR swap algorithm which avoids using a temporary variable.
 *          This can be useful in very constrained memory environments.
 */
#define eya_algorithm_swap_no_temp(a, b)                                                           \
    do                                                                                             \
    {                                                                                              \
        (a) ^= (b);                                                                                \
        (b) ^= (a);                                                                                \
        (a) ^= (b);                                                                                \
    } while (0)

/**
 * @def eya_algorithm_copy(T, dst, src, n)
 * @brief Copies elements from source to destination
 * @param T Data type of elements
 * @param dst Destination pointer
 * @param src Source pointer
 * @param n Number of elements to copy
 * @note Both pointers must be valid and have enough space for n elements
 *
 * @details Performs a standard forward copy operation from source to destination.
 *          The copy is done element by element in increasing memory order.
 */
#define eya_algorithm_copy(T, dst, src, n)                                                         \
    do                                                                                             \
    {                                                                                              \
        T       *d = eya_ptr_cast(T, dst);                                                         \
        const T *s = eya_ptr_ccast(T, src);                                                        \
                                                                                                   \
        while (n--)                                                                                \
        {                                                                                          \
            *d++ = *s++;                                                                           \
        }                                                                                          \
    } while (0)

/**
 * @def eya_algorithm_rcopy(T, dst, src, n)
 * @brief Copies elements from source to destination in reverse order
 * @param T Data type of elements
 * @param dst Destination pointer
 * @param src Source pointer
 * @param n Number of elements to copy
 * @note Useful when source and destination memory regions overlap
 *
 * @details Performs a reverse copy operation, starting from the end of the arrays.
 *          This is particularly useful when dealing with overlapping memory regions.
 */
#define eya_algorithm_rcopy(T, dst, src, n)                                                        \
    do                                                                                             \
    {                                                                                              \
        T       *d = eya_ptr_add_by_offset_unsafe(dst, n);                                         \
        const T *s = eya_ptr_add_by_offset_unsafe(src, n);                                         \
                                                                                                   \
        while (n--)                                                                                \
        {                                                                                          \
            *(--d) = *(--s);                                                                       \
        }                                                                                          \
    } while (0)

/**
 * @def eya_algorithm_set(T, dst, val, n)
 * @brief Sets n elements to the specified value
 * @param T Data type of elements
 * @param dst Destination pointer
 * @param val Value to set
 * @param n Number of elements to set
 *
 * @details Initializes or sets a block of memory to a specific value.
 *          Works for any data type that supports assignment.
 */
#define eya_algorithm_set(T, dst, val, n)                                                          \
    do                                                                                             \
    {                                                                                              \
        T *d = eya_ptr_cast(eya_uchar_t, dst);                                                     \
                                                                                                   \
        while (n--)                                                                                \
        {                                                                                          \
            *d++ = val;                                                                            \
        }                                                                                          \
    } while (0)

/**
 * @def eya_algorithm_compare(T, lhs, rhs, n)
 * @brief Compares two memory regions element by element
 * @param T Data type of elements
 * @param lhs Left-hand side pointer
 * @param rhs Right-hand side pointer
 * @param n Number of elements to compare
 * @return Pointer to the first differing element, or NULL if equal
 *
 * @details Performs a forward comparison of two memory regions.
 *          Returns at the first found difference.
 */
#define eya_algorithm_compare(T, lhs, rhs, n)                                                      \
    do                                                                                             \
    {                                                                                              \
        const T *l = eya_ptr_ccast(T, lhs);                                                        \
        const T *r = eya_ptr_ccast(T, rhs);                                                        \
                                                                                                   \
        while (n--)                                                                                \
        {                                                                                          \
            if (*l != *r)                                                                          \
            {                                                                                      \
                return l;                                                                          \
            }                                                                                      \
            l++;                                                                                   \
            r++;                                                                                   \
        }                                                                                          \
    } while (0)

/**
 * @def eya_algorithm_rcompare(T, lhs, rhs, n)
 * @brief Compares two memory regions in reverse order
 * @param T Data type of elements
 * @param lhs Left-hand side pointer
 * @param rhs Right-hand side pointer
 * @param n Number of elements to compare
 * @return Pointer to the first differing element (from end), or NULL if equal
 *
 * @details Performs a reverse comparison of two memory regions.
 *          Useful when differences are more likely to be at the end of arrays.
 */
#define eya_algorithm_rcompare(T, lhs, rhs, n)                                                     \
    do                                                                                             \
    {                                                                                              \
        const T *l = eya_ptr_add_unsafe(lhs, eya_math_sub_one(n));                                 \
        const T *r = eya_ptr_add_unsafe(rhs, eya_math_sub_one(n));                                 \
                                                                                                   \
        while (n--)                                                                                \
        {                                                                                          \
            if (*l != *r)                                                                          \
            {                                                                                      \
                return l;                                                                          \
            }                                                                                      \
            l--;                                                                                   \
            r--;                                                                                   \
        }                                                                                          \
    } while (0)

/**
 * @def eya_algorithm_copy_rev(T, dst, src, n)
 * @brief Copies elements from source to destination in reversed order
 * @param T Data type of elements
 * @param dst Destination pointer
 * @param src Source pointer
 * @param n Number of elements to copy
 * @note Both pointers must be valid and have enough space for n elements
 * @details Copies elements from source to destination such that the first element
 *          of src becomes the last element of dst, the second element of src
 *          becomes the second-to-last element of dst, and so on.
 */
#define eya_algorithm_copy_rev(T, dst, src, n)                                                     \
    do                                                                                             \
    {                                                                                              \
        T       *d = eya_ptr_add_by_offset_unsafe(dst, n);                                         \
        const T *s = eya_ptr_ccast(T, src);                                                        \
                                                                                                   \
        while (n--)                                                                                \
        {                                                                                          \
            *--d = *s++;                                                                           \
        }                                                                                          \
    } while (0)

#endif // EYA_ALGORITHM_UTIL_H