/**
 * @file numeric.h
 * @brief Main header for numeric types and limits.
 *
 * @details This is the primary include file for the numeric types system.
 *          It provides a unified interface to access all numeric type
 *          definitions and their associated limits and properties.
 *
 * The header includes:
 * - @ref numeric_types.h: Type definitions for signed and unsigned integers
 * - @ref numeric_limits.h: Size and limit macros for numeric types
 *
 * @note This is a convenience header that aggregates the complete numeric
 *       types functionality. For fine-grained control, include the specific
 *       headers directly.
 */

#ifndef EYA_NUMERIC_H
#    define EYA_NUMERIC_H

#    include "numeric_types.h"  ///< Type definitions for signed/unsigned integers
#    include "numeric_limits.h" ///< Size and limit macros for numeric types

#endif // EYA_NUMERIC_H

/** @} */ // end of numeric group