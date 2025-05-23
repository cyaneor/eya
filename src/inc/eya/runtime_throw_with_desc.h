/**
 * @file runtime_throw_with_desc.h
 * @brief Interface for exception generation with error descriptions
 *
 * Provides specialized macro @ref se_runtime_throw_with_desc for streamlined
 * exception generation with fixed error code and custom diagnostic messages.
 *
 * Key features:
 * - Automatically uses SE_RUNTIME_ERROR_INTERRUPT error code
 * - Supports custom error descriptions with string literals or pointers
 * - Maintains full compatibility with base exception mechanism
 * - Augments debug traces with call site information in DEBUG builds
 */

#ifndef SE_RUNTIME_THROW_DESC_H
#define SE_RUNTIME_THROW_DESC_H

#include "runtime_error_code.h"
#include "runtime_throw.h"

/**
 * @def se_runtime_throw_with_desc
 * @brief Macro for generating exceptions with fixed error code and custom description
 *
 * Provides unified interface for raising exceptions using predefined
 * SE_RUNTIME_ERROR_INTERRUPT code with user-defined diagnostic message.
 *
 * @param desc Error description (string literal or char pointer)
 * @note Always uses SE_RUNTIME_ERROR_INTERRUPT error code
 * @note DEBUG builds inject __FILE__ and __LINE__ information
 *
 * Usage example:
 * @code
 * // Abort operation with context
 * if (operation_aborted) {
 *     se_runtime_throw_with_desc("User-initiated operation termination");
 * }
 * @endcode
 *
 * @see se_runtime_throw()
 * @see se_runtime_throw_with_code()
 * @see SE_RUNTIME_ERROR_INTERRUPT
 */
#define se_runtime_throw_with_desc(desc) se_runtime_throw(SE_RUNTIME_ERROR_INTERRUPT, desc)

#endif // SE_RUNTIME_THROW_DESC_H