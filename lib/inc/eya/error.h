/**
 * @file error.h
 * @brief Header file containing structures for error handling.
 *
 * This file defines the `eya_error_t` structure used
 * to store error information during program execution.
 *
 * The structure contains an error code and textual description,
 * enabling effective error diagnostics and exception handling.
 */

#ifndef EYA_ERROR_H
#define EYA_ERROR_H

#include "attribute.h"
#include "bool.h"
#include "error_code.h"

/**
 * @struct eya_error_t
 * @brief Structure for storing error information.
 *
 * This structure represents errors occurring during execution.
 * Contains both error code and textual description for
 * diagnostics and exception handling.
 */
typedef struct eya_error
{
    eya_error_code_t code; /**< Error code identifying error type/cause */
    const char      *desc; /**< Pointer to error description string */
} eya_error_t;

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Extracts error code and description from eya_error_t object
 * @param[in] self Pointer to eya_error_t object
 * @param[out] code Pointer to store error code (may be nullptr)
 * @param[out] desc Pointer to store error description (may be nullptr)
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_error_unpack(const eya_error_t *self, eya_error_code_t *code, const char **desc);

/**
 * @brief Retrieves error code from eya_error_t object
 * @param[in] self Pointer to eya_error_t object
 * @return Error code or 0 if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
eya_error_code_t
eya_error_get_code(const eya_error_t *self);

/**
 * @brief Retrieves error code and clears eya_error_t object
 * @param[in,out] self Pointer to eya_error_t object
 * @return Error code present before clearing
 */
EYA_ATTRIBUTE(SYMBOL)
eya_error_code_t
eya_error_get_code_and_clear(eya_error_t *self);

/**
 * @brief Retrieves error description from eya_error_t object
 * @param[in] self Pointer to eya_error_t object
 * @return Error description string or nullptr if self is nullptr
 */
EYA_ATTRIBUTE(SYMBOL)
const char *
eya_error_get_desc(const eya_error_t *self);

/**
 * @brief Sets error code and description in eya_error_t object
 * @param[in,out] self Pointer to eya_error_t object
 * @param[in] code Error code to set
 * @param[in] desc Error description string
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_error_set(eya_error_t *self, eya_error_code_t code, const char *desc);

/**
 * @brief Sets only error code in eya_error_t object
 * @param[in,out] self Pointer to eya_error_t object
 * @param[in] code Error code to set
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_error_set_code(eya_error_t *self, eya_error_code_t code);

/**
 * @brief Copies contents between eya_error_t objects
 * @param[in,out] self Destination eya_error_t object
 * @param[in] other Source eya_error_t object
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_error_assign(eya_error_t *self, const eya_error_t *other);

/**
 * @brief Resets eya_error_t object to default state
 * @param[in,out] self Pointer to eya_error_t object
 */
EYA_ATTRIBUTE(SYMBOL)
void
eya_error_clear(eya_error_t *self);

/**
 * @brief Checks if object contains specified error code
 * @param[in] self Pointer to eya_error_t object
 * @param[in] code Error code to check
 * @return true if code matches, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_error_is_equal_code_to(const eya_error_t *self, eya_error_code_t code);

/**
 * @brief Compares error codes between two objects
 * @param[in] self First eya_error_t object
 * @param[in] other Second eya_error_t object
 * @return true if codes match, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_error_is_equal_code(const eya_error_t *self, const eya_error_t *other);

/**
 * @brief Checks if object contains specified error description
 * @param[in] self Pointer to eya_error_t object
 * @param[in] desc Description to check
 * @return true if description matches, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_error_is_equal_desc_to(const eya_error_t *self, const char *desc);

/**
 * @brief Compares descriptions between two error objects
 * @param[in] self First eya_error_t object
 * @param[in] other Second eya_error_t object
 * @return true if descriptions match, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_error_is_equal_desc(const eya_error_t *self, const eya_error_t *other);

/**
 * @brief Compares two error objects for equality
 * @param[in] self First eya_error_t object
 * @param[in] other Second eya_error_t object
 * @return true if objects are equal (code and description if enabled)
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_error_is_equal(const eya_error_t *self, const eya_error_t *other);

/**
 * @brief Checks if object represents no error
 * @param[in] self Pointer to eya_error_t object
 * @return true if code equals EYA_ERROR_CODE_NONE, false otherwise
 */
EYA_ATTRIBUTE(SYMBOL)
bool
eya_error_is_ok(const eya_error_t *self);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_ERROR_H