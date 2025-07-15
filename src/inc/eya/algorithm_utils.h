#ifndef EYA_ALGORITHM_UTILS_H
#define EYA_ALGORITHM_UTILS_H

/**
 * @def eya_algorithm_swap(T, a, b)
 * @brief Swaps values of two variables of the same type
 * @param T Data type of variables
 * @param a First variable
 * @param b Second variable
 * @warning Avoid expressions with side effects (e.g., i++)
 *
 * Example:
 * @code
 * int x=1, y=2;
 * eya_algorithm_swap(x, y, int);
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
 * @brief Swaps values without temporary variable (XOR swap)
 * @param a First integer variable
 * @param b Second integer variable
 * @note Only for integers. Slightly faster but less readable.
 */
#define eya_algorithm_swap_no_temp(a, b)                                                           \
    do                                                                                             \
    {                                                                                              \
        (a) ^= (b);                                                                                \
        (b) ^= (a);                                                                                \
        (a) ^= (b);                                                                                \
    } while (0)

#endif // EYA_ALGORITHM_UTILS_H