/**
 * @file version.h
 * @brief Defines the version structure for the EYA library.
 *
 * This file contains the definition of the eya_version_t structure,
 * which is used to store version information for the EYA library,
 * including major, minor, and patch version numbers.
 */

#ifndef EYA_VERSION_H
#define EYA_VERSION_H

#include "attribute.h"
#include "version_fields.h"
#include "numeric_fixed_types.h"

/**
 * @struct eya_version
 * @brief Structure to hold EYA library version information.
 *
 * This structure encapsulates the version information of the EYA library,
 * with fields for major, minor, and patch version numbers.
 */
typedef struct eya_version
{
    eya_version_fields(eya_u16_t, eya_u8_t, eya_u8_t);
} eya_version_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Retrieves the major version number.
 *
 * This function returns the major version number from the provided eya_version_t
 * structure. It performs a runtime check to ensure the provided pointer is valid.
 *
 * @param self Pointer to the eya_version_t structure.
 * @return The major version number as a 16-bit unsigned integer.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_u16_t
eya_version_major(const eya_version_t *self);

/**
 * @brief Retrieves the minor version number.
 *
 * This function returns the minor version number
 * from the provided eya_version_t structure.
 *
 * @param self Pointer to the eya_version_t structure.
 * @return The minor version number as an 8-bit unsigned integer.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_u8_t
eya_version_minor(const eya_version_t *self);

/**
 * @brief Retrieves the patch version number.
 *
 * This function returns the patch version number
 * from the provided eya_version_t structure.
 *
 * @param self Pointer to the eya_version_t structure.
 * @return The patch version number as an 8-bit unsigned integer.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_u8_t
eya_version_patch(const eya_version_t *self);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_VERSION_H