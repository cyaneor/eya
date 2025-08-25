/**
 * @file jump_buffer.h
 * @brief Definition of a data type
 *        for using a jump buffer with setjmp/longjmp.
 *
 * This file contains the definition of the `eya_jump_buffer_t` type,
 * which is an alias for the standard `jmp_buf` type used to save
 * the program's execution state when working with setjmp and longjmp functions.
 */

#ifndef EYA_JUMP_BUFFER_H
#define EYA_JUMP_BUFFER_H

#include <setjmp.h>

/**
 * @typedef eya_jump_buffer_t
 * @brief Type used to store the program's execution state.
 *
 * The `eya_jump_buffer_t` type is an alias for `jmp_buf`,
 * which is used to save and restore the program's execution state
 * when working with setjmp() and longjmp() functions.
 */
typedef jmp_buf eya_jump_buffer_t;

#endif // EYA_JUMP_BUFFER_H