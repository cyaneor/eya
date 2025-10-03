/**
 * @file version_initializer.h
 * @brief Header file providing version initializer macros for the EYA library.
 *
 * This file includes the initializer header and defines a convenience macro
 * for initializing eya_version_t structures using the major, minor,
 * and patch version numbers.
 */

#ifndef EYA_VERSION_INITIALIZER_H
#define EYA_VERSION_INITIALIZER_H

#include "initializer.h"

/**
 * @def eya_version_initializer(major, minor, patch)
 * @brief Initializes an eya_version_t structure with the specified version numbers.
 * @details This macro leverages the eya_struct_initializer to create an initialized
 *          eya_version_t instance.
 *
 *          It takes the major version (eya_ushort_t),
 *          minor version (eya_uchar_t), and patch version (eya_uchar_t) as arguments,
 *          which must match the field order in the eya_version_t structure.
 *
 * @param major The major version number (eya_ushort_t).
 * @param minor The minor version number (eya_uchar_t).
 * @param patch The patch version number (eya_uchar_t).
 * @return An initialized eya_version_t structure with the provided version numbers.
 * @note This macro is typically used to initialize global or static version variables.
 * @warning Ensure the arguments match the expected types to avoid compilation errors.
 *
 * Example usage:
 * @code
 * eya_version_t version = eya_version_initializer(1, 2, 3);
 * @endcode
 */
#define eya_version_initializer(major, minor, patch) eya_initializer(major, minor, patch)

#endif // EYA_VERSION_INITIALIZER_H