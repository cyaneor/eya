/**
 * @file exception_catch.h
 * @brief Header file defining exception catching structure
 *
 * Contains definition of `eya_exception_catch_t` structure
 * used to implement exception handling mechanism
 * through setjmp/longjmp. Combines exception information
 * and execution context at catch point.
 */

#ifndef EYA_EXCEPTION_CATCH_H
#define EYA_EXCEPTION_CATCH_H

#include "exception.h"
#include "jump_buffer.h"

/**
 * @struct eya_exception_catch
 * @brief Exception catching structure
 *
 * Enables saving exception state and execution context
 * when using setjmp/longjmp exception handling.
 * Contains both the exception and environment for context restoration.
 *
 * @see eya_exception_t For exception structure details
 * @see eya_jump_buffer_t For execution context storage
 */
typedef struct eya_exception_catch
{
    eya_exception_t   exception; /**< Caught exception containing error details */
    eya_jump_buffer_t env;       /**< Buffer storing execution context at catch point */
} eya_exception_catch_t;

#endif // EYA_EXCEPTION_CATCH_H