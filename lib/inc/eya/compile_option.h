/**
 * @file compile_option.h
 * @brief Header file defining compilation option macros
 *
 * This file provides macros for compilation options
 * that build upon the basic option macros defined in option.h.
 *
 * It allows for consistent representation
 * of compilation-related ON/OFF states throughout the codebase.
 */

#ifndef EYA_COMPILE_OPTION_H
#define EYA_COMPILE_OPTION_H

#include "option.h"

/**
 * @def EYA_COMPILE_OPTION_ON
 * @brief Macro representing the "ON" state for compilation options
 *
 * If not previously defined, defaults to EYA_OPTION_ON (1).
 * Provides a consistent way to represent enabled compilation options.
 */
#ifndef EYA_COMPILE_OPTION_ON
#    define EYA_COMPILE_OPTION_ON EYA_OPTION_ON
#endif // EYA_COMPILE_OPTION_ON

/**
 * @def EYA_COMPILE_OPTION_OFF
 * @brief Macro representing the "OFF" state for compilation options
 *
 * If not previously defined, defaults to EYA_OPTION_OFF (0).
 * Provides a consistent way to represent disabled compilation options.
 */
#ifndef EYA_COMPILE_OPTION_OFF
#    define EYA_COMPILE_OPTION_OFF EYA_OPTION_OFF
#endif // EYA_COMPILE_OPTION_OFF

#endif // EYA_COMPILE_OPTION_H