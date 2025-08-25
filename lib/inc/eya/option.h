/**
 * @file option.h
 * @brief Header file defining option macros
 *
 * This file provides basic option macros that can be used
 * to represent ON/OFF or TRUE/FALSE states in a consistent
 * way throughout the codebase.
 */

#ifndef EYA_OPTION_H
#define EYA_OPTION_H

/**
 * @def EYA_OPTION_ON
 * @brief Macro representing the "ON" or "TRUE" state
 *
 * Defined as 1, this macro provides a consistent way
 * to represent enabled/active/true states in the code.
 */
#ifndef EYA_OPTION_ON
#    define EYA_OPTION_ON 1
#endif // EYA_OPTION_ON

/**
 * @def EYA_OPTION_OFF
 * @brief Macro representing the "OFF" or "FALSE" state
 *
 * Defined as 0, this macro provides a consistent way
 * to represent disabled/inactive/false states in the code.
 */
#ifndef EYA_OPTION_OFF
#    define EYA_OPTION_OFF 0
#endif // EYA_OPTION_OFF

#endif // EYA_OPTION_H