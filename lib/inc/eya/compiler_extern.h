/**
 * @file compiler_extern.h
 * @brief Macro definition for external storage specifier.
 *
 * This header provides the EYA_COMPILER_EXTERN macro for declaring
 * variables and functions with external linkage.
 *
 * The macro serves to unify and abstract extern keyword usage throughout
 * the project, enabling centralized control of storage specifiers and
 * simplifying code maintenance across different platforms and requirements.
 */

#ifndef EYA_COMPILER_EXTERN_H
#define EYA_COMPILER_EXTERN_H

/**
 * @def EYA_COMPILER_EXTERN
 * @brief Macro indicating external linkage declaration
 *
 * This macro replaces the `extern` keyword which specifies that
 * a variable or function is declared here but defined in another
 * compilation unit.
 *
 * Using this macro provides:
 * - Centralized storage specifier management
 * - Platform/compiler abstraction layer
 * - Easier codebase maintenance
 *
 * Usage example:
 * @code
 * EYA_COMPILER_EXTERN int global_variable;
 * EYA_COMPILER_EXTERN void some_function(void);
 * @endcode
 *
 * @note Entities declared with this macro must be defined in exactly
 *       one implementation file to prevent linker errors.
 */
#define EYA_COMPILER_EXTERN extern

#endif // EYA_COMPILER_EXTERN_H