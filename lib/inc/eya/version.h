/**
 * @file version.h
 * @brief Header for library version handling.
 *
 * Provides functions to retrieve library version information
 * including:
 *
 * - Full semantic version string (major.minor.patch)
 * - Individual version components (major, minor, patch)
 *
 * Used for version control and compatibility management.
 */

#ifndef EYA_VERSION_H
#define EYA_VERSION_H

#include "attribute.h"
#include "char.h"
#include "return.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Retrieves full semantic version string "major.minor.patch"
 *
 * Constructs the version string using eya_str_from_args macro,
 * combining major, minor and patch version components.
 *
 * @return Const pointer to version string (e.g. "1.2.3")
 *
 * @note The string is statically allocated and must not be freed
 *
 * Usage example:
 * @code
 * const char *version = eya_version();
 * printf("Current version: %s\n", version); // Output: "1.2.3" (example)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const eya_char_t *
eya_version(void);

/**
 * @brief Retrieves major version component
 *
 * Provides access to the major version number
 * defined via `EYA_VERSION_MAJOR`.
 *
 * @return Major version as `eya_return_t`
 *
 * Usage example:
 * @code
 * eya_return_t major = eya_version_major();
 * printf("Major version: %d\n", major); // Output: 1 (example)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
eya_return_t
eya_version_major(void);

/**
 * @brief Retrieves minor version component
 *
 * Provides access to the minor version number
 * defined via `EYA_VERSION_MINOR`.
 *
 * @return Minor version as `eya_return_t`
 *
 * Usage example:
 * @code
 * eya_return_t minor = eya_version_minor();
 * printf("Minor version: %d\n", minor); // Output: 2 (example)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
eya_return_t
eya_version_minor(void);

/**
 * @brief Retrieves patch version component
 *
 * Provides access to the patch version number
 * defined via `EYA_VERSION_PATCH`.
 *
 * @return Patch version as eya_return_t
 *
 * Usage example:
 * @code
 * eya_return_t patch = eya_version_patch();
 * printf("Patch version: %d\n", patch); // Output: 3 (example)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
eya_return_t
eya_version_patch(void);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_VERSION_H