/**
 * @file eya_memory_view_state.h
 * @brief Defines the state enumeration for memory view validity checking.
 *
 * This header provides an enumeration that describes various states of a memory view,
 * which is typically represented by a pair of pointers (begin and end).
 * The states indicate whether the memory view is valid, empty, uninitialized,
 * or in some invalid state.
 */

#ifndef EYA_MEMORY_VIEW_STATE_H
#define EYA_MEMORY_VIEW_STATE_H

/**
 * @enum eya_memory_view_state
 * @brief Enumeration describing possible states of a memory view.
 *
 * This enumeration is used to represent and check the validity state of a memory range
 * defined by two pointers (begin and end). It helps in validating memory views before
 * operations and provides detailed diagnostics about what might be wrong with a view.
 */
typedef enum eya_memory_view_state
{
    EYA_MEMORY_VIEW_EMPTY,              ///< Valid but empty view (begin == end, but not nullptr)
    EYA_MEMORY_VIEW_UNINITIALIZED,      ///< Uninitialized view (both pointers are nullptr)
    EYA_MEMORY_VIEW_HAS_DATA,           ///< Valid view with data (begin < end)
    EYA_MEMORY_VIEW_INVALID_NULL_BEGIN, ///< Invalid: begin is nullptr while end is not
    EYA_MEMORY_VIEW_INVALID_NULL_END,   ///< Invalid: end is nullptr while begin is not
    EYA_MEMORY_VIEW_INVALID_DANGLING    ///< Invalid: begin > end (logical error)
} eya_memory_view_state_t;

#endif // EYA_MEMORY_VIEW_STATE_H