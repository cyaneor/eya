/**
 * @file memory_range_state.h
 * @brief Memory range state enumeration and definitions.
 *
 * This header defines the `eya_memory_range_state_t` enumeration which represents
 * all possible states of a memory range or view, including both valid and invalid
 * configurations.
 *
 * The enumeration distinguishes between:
 * - Valid states (empty, initialized with data)
 * - Uninitialized state
 * - Various invalid configurations (null mismatches, dangling pointers)
 *
 * @note When using these states, always ensure proper initialization before checking
 *       the memory range state to avoid undefined behavior.
 *
 * Example usage:
 * @code
 * eya_memory_range_state_t state = check_memory_range_state(ptr_begin, ptr_end);
 * if (state == EYA_MEMORY_RANGE_HAS_DATA) {
 *     // Process valid memory range
 * }
 * @endcode
 *
 * @see eya_memory_range_state_t
 */

#ifndef EYA_MEMORY_RANGE_STATE_H
#define EYA_MEMORY_RANGE_STATE_H

/**
 * @typedef eya_memory_range_state_t
 * @brief Represents the state of a memory range/view.
 *
 * This enumeration describes all possible states of a memory range,
 * including valid states and various invalid configurations.
 */
typedef enum eya_memory_range_state
{
    /**
     * @brief Valid but empty view (begin == end, but not nullptr)
     *
     * The memory range is valid but contains no data as the begin and end pointers
     * are equal (though neither is null).
     */
    EYA_MEMORY_RANGE_EMPTY,

    /**
     * @brief Uninitialized view (both pointers are nullptr)
     *
     * The memory range is uninitialized, with both begin and end pointers being null.
     */
    EYA_MEMORY_RANGE_UNINITIALIZED,

    /**
     * @brief Valid view with data (begin < end)
     *
     * The memory range is valid and contains data, with begin pointing to the start
     * and end pointing just past the last element (begin < end).
     */
    EYA_MEMORY_RANGE_HAS_DATA,

    /**
     * @brief Invalid: begin is nullptr while end is not
     *
     * The memory range is in an invalid state where the begin pointer is null
     * while the end pointer is not null.
     */
    EYA_MEMORY_RANGE_INVALID_NULL_BEGIN,

    /**
     * @brief Invalid: end is nullptr while begin is not
     *
     * The memory range is in an invalid state where the end pointer is null
     * while the begin pointer is not null.
     */
    EYA_MEMORY_RANGE_INVALID_NULL_END,

    /**
     * @brief Invalid: begin > end (logical error)
     *
     * The memory range is in an invalid state where the begin pointer is
     * after the end pointer, indicating a logical error in the range.
     */
    EYA_MEMORY_RANGE_INVALID_DANGLING
} eya_memory_range_state_t;

#endif // EYA_MEMORY_RANGE_STATE_H