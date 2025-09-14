#ifndef EYA_H
#define EYA_H

#include "version.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Retrieves the EYA library version.
 *
 * This function returns a pointer to the global eya_version_t structure,
 * which contains the major, minor, and patch version numbers of the EYA library.
 *
 * @return A pointer to the eya_version_t structure containing version information.
 */
EYA_ATTRIBUTE(SYMBOL)
eya_version_t *
eya_version(void);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_H
