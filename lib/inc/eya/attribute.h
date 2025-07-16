/**
 * @file attribute.h
 * @brief Header file for centralized project-specific attribute definitions.
 *
 * This file serves as a centralized management point for attributes
 * that can be configured based on project requirements.
 *
 * Attribute configuration is handled through CMake, enabling flexible
 * adaptation of project behavior according to selected build options.
 */

#ifndef EYA_ATTRIBUTE_H
#define EYA_ATTRIBUTE_H

#include "attribute_force_inline.h"
#include "attribute_noreturn.h"
#include "attribute_symbol.h"
#include "attribute_target.h"
#include "attribute_thread_local.h"
#include "attribute_unused.h"

/**
 * @def EYA_ATTRIBUTE(N)
 * @brief Expands to the corresponding attribute macro.
 *
 * This macro takes a single argument `N` and concatenates it with
 * `EYA_ATTRIBUTE_` to form the complete attribute macro name.
 *
 * @param N Suffix specifying the target attribute macro.
 */
#define EYA_ATTRIBUTE(N) EYA_ATTRIBUTE_##N

#endif // EYA_ATTRIBUTE_H