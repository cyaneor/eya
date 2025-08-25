/**
 * @file library_option.h
 * @brief Configuration options
 *
 * This header defines configuration macros for enabling/disabling features.
 * It provides default values for library-specific options while allowing customization.
 *
 * The file defines two main configuration states:
 * - EYA_LIBRARY_OPTION_ON:
 *   Enabled/active state (defaults to EYA_OPTION_ON)
 * - EYA_LIBRARY_OPTION_OFF:
 *   Disabled/inactive state (defaults to EYA_OPTION_OFF)
 *
 * @note These macros are designed to maintain consistency
 *       with the base EYA option system while providing
 *       library-specific customization points.
 */

#ifndef EYA_LIBRARY_OPTION_H
#define EYA_LIBRARY_OPTION_H

#include "option.h"

/**
 * @def EYA_LIBRARY_OPTION_ON
 * @brief Configuration macro representing enabled/on state
 *
 * This macro defines the value used to represent an enabled or on configuration state.
 * Defaults to `EYA_OPTION_ON` (1) if not explicitly defined.
 *
 * @see EYA_OPTION_ON for the base definition
 * @see EYA_LIBRARY_OPTION_OFF for the complementary option
 */
#ifndef EYA_LIBRARY_OPTION_ON
#    define EYA_LIBRARY_OPTION_ON EYA_OPTION_ON
#endif // EYA_LIBRARY_OPTION_ON

/**
 * @def EYA_LIBRARY_OPTION_OFF
 * @brief Configuration macro representing disabled/off state
 *
 * This macro defines the value used to represent a disabled or off configuration state.
 * Defaults to `EYA_OPTION_OFF` (0) if not explicitly defined.
 *
 * @see EYA_OPTION_OFF for the base definition
 * @see EYA_LIBRARY_OPTION_ON for the complementary option
 */
#ifndef EYA_LIBRARY_OPTION_OFF
#    define EYA_LIBRARY_OPTION_OFF EYA_OPTION_OFF
#endif // EYA_LIBRARY_OPTION_OFF

#endif // EYA_LIBRARY_OPTION_H