/**
 * @file version_fields.h
 * @brief Defines a macro for version fields used in versioning structures.
 *
 * This header file provides a macro `eya_version_fields` that defines three fields
 * (major, minor, patch) for versioning purposes. The macro allows flexibility
 * in specifying the data types for each version field.
 *
 * @note This macro is intended to be used within a struct
 *       or class definition to include version fields with customizable types.
 */

#ifndef EYA_VERSION_FIELDS_H
#define EYA_VERSION_FIELDS_H

#include "initializer.h"

/**
 * @def eya_version_fields(T, M, P)
 * @brief Macro to define version fields (major, minor, patch) with specified types.
 *
 * This macro generates three fields for versioning:
 * - `major`: The major version number, typically indicating significant changes.
 * - `minor`: The minor version number, typically indicating incremental updates.
 * - `patch`: The patch version number, typically indicating bug fixes or minor changes.
 *
 * @param T The data type for the `major` version field (e.g., int, uint32_t).
 * @param M The data type for the `minor` version field (e.g., int, uint32_t).
 * @param P The data type for the `patch` version field (e.g., int, uint32_t).
 *
 * Example usage:
 * ```c
 * struct Version {
 *     eya_version_fields(int, int, int);
 * };
 * ```
 */
#define eya_version_fields(T, M, P)                                                                \
    T major;                                                                                       \
    M minor;                                                                                       \
    P patch

#endif // EYA_VERSION_FIELDS_H