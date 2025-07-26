/**
 * @file memory.h
 * @brief Enhanced Memory Operations Library with Bounds Checking
 *
 * Provides a suite of memory manipulation functions with built-in size validation
 * and safety checks. Designed as safer alternatives to standard C memory functions
 * with these key features:
 * - Automatic buffer size checking
 * - Pointer validation
 * - Overlap detection and handling
 * - Consistent error handling
 * - Support for both forward and reverse operations
 *
 * All functions:
 * - Validate input pointers using eya_runtime_check_ref
 * - Respect buffer sizes to prevent overflows
 * - Provide meaningful return values for operation chaining
 * - Are thread-safe when used with distinct memory regions
 */

#ifndef EYA_MEMORY_H
#define EYA_MEMORY_H

#include "attribute.h"
#include "size.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Safely copies memory between buffers with size checking.
 *
 * This function copies the smaller of @p dst_size or @p src_size bytes from @p src
 * to @p dst, ensuring no buffer overflow can occur. It serves as a safer alternative
 * to standard memory copy functions by explicitly requiring buffer sizes.
 *
 * @param[out] dst       Pointer to the destination buffer.
 * @param[in]  dst_size  Total size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source buffer to copy from.
 * @param[in]  src_size  Total size of the source buffer in bytes.
 *
 * @return Returns a pointer to the destination buffer (@p dst).
 *
 * @note Internally uses `eya_memory_std_copy` after calculating the safe copy size.
 * @note Both buffers are validated via `eya_runtime_check_ref`.
 * @warning The function only copies up to the smaller buffer size - no partial copies
 *          are performed if sizes differ.
 * @warning Behavior is undefined if buffers overlap (use `eya_memory_move` instead).
 *
 * @see eya_memory_std_copy For basic copying without size checks.
 * @see eya_memory_move     For overlap-safe copying with size checks.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_copy(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Copies bytes from source to destination
 *        in reversed order with size checking.
 *
 * This function copies bytes from the memory area pointed to by @p src
 * to the memory area pointed to by @p dst, reversing the order of bytes.
 * The number of bytes copied is the minimum of @p dst_size and @p src_size.
 *
 * The first byte of @p src becomes the last byte of @p dst,
 * the second byte of @p src becomes the second-to-last byte of @p dst, and so on.
 * The memory areas must be valid and accessible, and should not overlap.
 *
 * @param[out] dst       Pointer to the destination memory location.
 * @param[in]  dst_size  Size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source memory location to copy from.
 * @param[in]  src_size  Size of the source buffer in bytes.
 *
 * @return Returns a pointer to the destination memory location (@p dst).
 *
 * @note The actual number of bytes copied is the minimum of @p dst_size and @p src_size.
 *       This provides basic protection against buffer overflows.
 *
 * @warning The behavior is undefined if the source and destination buffers overlap.
 * @warning If either @p dst_size or @p src_size is zero, no bytes are copied.
 *
 * @see eya_memory_std_copy_rev  For the underlying implementation without size checking.
 * @see eya_memory_std_copy      For non-overlapping forward copy.
 * @see eya_memory_std_rcopy     For backward copy without reversing content.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_copy_rev(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Safely copies memory between buffers in reverse order with size checking.
 *
 * This function copies the smaller of @p dst_size or @p src_size bytes from @p src
 * to @p dst in reverse order (from end to beginning), ensuring no buffer overflow
 * can occur. The reverse copy provides safe handling for certain overlap scenarios.
 *
 * @param[out] dst       Pointer to the destination buffer.
 * @param[in]  dst_size  Total size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source buffer to copy from.
 * @param[in]  src_size  Total size of the source buffer in bytes.
 *
 * @return Returns a pointer to the destination buffer (@p dst).
 *
 * @note Internally uses `eya_memory_std_rcopy` after calculating the safe copy size.
 * @note Both buffers are validated via `eya_runtime_check_ref`.
 * @warning Only safe when @p dst >= @p src + n. For other overlaps, use `eya_memory_move`.
 * @warning Copies exactly min(dst_size, src_size) bytes - no partial copies if sizes differ.
 *
 * @see eya_memory_std_rcopy For reverse copying without size checks.
 * @see eya_memory_copy      For forward copying with size checks.
 * @see eya_memory_move      For full overlap-safe copying.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_rcopy(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Safely moves memory between potentially overlapping buffers with size checking.
 *
 * This function copies the smaller of @p dst_size or @p src_size bytes from @p src
 * to @p dst, automatically handling overlap cases by choosing between forward and
 * reverse copying strategies. Provides complete memory safety for all copy scenarios.
 *
 * @param[out] dst       Pointer to the destination buffer.
 * @param[in]  dst_size  Total size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source buffer to move from.
 * @param[in]  src_size  Total size of the source buffer in bytes.
 *
 * @return Returns a pointer to the destination buffer (@p dst).
 *
 * @note Internally uses `eya_memory_std_move` after calculating the safe copy size.
 * @note Performs automatic overlap detection to choose optimal copy direction.
 * @warning If @p dst == @p src, returns immediately without copying.
 * @warning Only copies min(dst_size, src_size) bytes - no partial copies.
 *
 * @see eya_memory_std_move For move operation without size checks.
 * @see eya_memory_copy     For non-overlapping copies with size checks.
 * @see eya_memory_rcopy    For explicit reverse copying.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_move(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Safely fills a memory buffer with a specified byte value.
 *
 * This function sets all bytes in the destination buffer to the specified value,
 * with explicit size checking to prevent buffer overflows. It provides a safer
 * alternative to memset() by including runtime buffer validation.
 *
 * @param[out] dst   Pointer to the destination buffer to fill.
 * @param[in]  size  Total size of the destination buffer in bytes.
 * @param[in]  val   Value to set (interpreted as unsigned byte).
 *
 * @return Returns a pointer to the end of the filled memory block (dst + size).
 *         This enables convenient operation chaining.
 *
 * @note Internally uses eya_memory_std_set after validation.
 * @note The destination pointer is validated via eya_runtime_check_ref.
 * @warning If size is zero, returns dst without modification.
 *
 * @see eya_memory_std_set For the underlying implementation without size checks.
 * @see eya_memory_copy    For copying between buffers.
 * @see eya_memory_move    For overlap-safe memory transfers.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_set(void *dst, eya_usize_t size, eya_uchar_t val);

/**
 * @brief Fills a memory buffer with a repeating pattern from a source buffer.
 *
 * This function safely copies the source pattern repeatedly into the destination buffer,
 * handling cases where the pattern doesn't evenly divide the destination size. It performs
 * full runtime validation of input parameters and ensures no buffer overflows occur.
 *
 * @param[out] dst      Pointer to the destination buffer to fill.
 * @param[in]  dst_size Total size of the destination buffer in bytes.
 * @param[in]  src      Pointer to the source pattern to replicate.
 * @param[in]  src_size Size of the source pattern in bytes.
 *
 * @return Returns the original destination pointer (dst) on success.
 *         Returns NULL if either dst_size or src_size is zero.
 *
 * @note Both dst and src pointers are validated via eya_runtime_check_ref.
 * @note The function handles partial pattern copies at the end of the buffer.
 * @warning Returns NULL if either buffer size is zero (no operation performed).
 * @warning If src_size exceeds dst_size, only the first dst_size bytes of src are used.
 *
 * @see eya_memory_set       For filling with a single byte value.
 * @see eya_memory_copy      For direct buffer-to-buffer copying.
 * @see eya_memory_move      For overlap-safe memory transfers.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_set_pattern(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Safely compares two memory buffers with size checking.
 *
 * This function compares the smaller of @p lhs_size or @p rhs_size bytes between
 * the two buffers, returning the position of the first difference or NULL if equal.
 * Provides complete memory safety by honoring both buffer sizes.
 *
 * @param[in] lhs       Pointer to the first memory buffer.
 * @param[in] lhs_size  Size of the first buffer in bytes.
 * @param[in] rhs       Pointer to the second memory buffer.
 * @param[in] rhs_size  Size of the second buffer in bytes.
 *
 * @return - Pointer to first differing byte in @p lhs
 *         - NULL if buffers are equal for min(lhs_size, rhs_size) bytes
 *
 * @note Internally uses eya_memory_std_compare after size validation.
 * @note Both pointers are validated via eya_runtime_check_ref.
 * @warning Returns NULL if either size is zero (treats as equal).
 * @warning Only compares up to the smaller buffer's size.
 *
 * @see eya_memory_std_compare For comparison without size checks.
 * @see eya_memory_rcompare    For reverse-order comparison.
 * @see eya_memory_diff       For finding all differences.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_compare(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

/**
 * @brief Safely compares two memory buffers in reverse order with size checking.
 *
 * This function compares the last N bytes of both buffers (where N is the smaller of
 * @p lhs_size and @p rhs_size), moving backward from the end. It returns the position
 * of the last difference when viewed from the start, or NULL if the compared regions
 * are equal.
 *
 * @param[in] lhs       Pointer to the first memory buffer.
 * @param[in] lhs_size  Size of the first buffer in bytes.
 * @param[in] rhs       Pointer to the second memory buffer.
 * @param[in] rhs_size  Size of the second buffer in bytes.
 *
 * @return - Pointer to the last differing byte in @p lhs (from start address)
 *         - NULL if the compared regions are equal
 *         - NULL if either size is zero
 *
 * @note Compares only the overlapping suffix regions of both buffers.
 * @note Both pointers are validated via eya_runtime_check_ref.
 * @warning The returned pointer references the original lhs buffer, not the adjusted
 *          comparison start position.
 * @warning For zero-sized buffers, returns NULL (considered equal).
 *
 * @see eya_memory_compare      For forward comparison with size checks.
 * @see eya_memory_std_rcompare For reverse comparison without size checks.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_rcompare(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

/**
 * @brief Finds the first occurrence of a memory pattern within a larger buffer.
 *
 * This function searches for the first occurrence of the @p rhs pattern within
 * the @p lhs buffer, comparing byte-by-byte. Returns the position where the
 * complete pattern matches or NULL if not found.
 *
 * @param[in] lhs       Pointer to the haystack buffer to search.
 * @param[in] lhs_size  Size of the haystack buffer in bytes.
 * @param[in] rhs       Pointer to the needle pattern to find.
 * @param[in] rhs_size  Size of the needle pattern in bytes.
 *
 * @return - Pointer to first occurrence of @p rhs within @p lhs
 *         - NULL if pattern not found
 *         - NULL if either buffer is empty
 *
 * @note Performs thorough bounds checking and pointer validation.
 * @warning Returns NULL immediately if:
 *          - Either size is zero
 *          - Needle is larger than haystack
 *          - Any pointer is invalid
 * @see eya_memory_rfind For reverse search (last occurrence).
 * @see eya_memory_compare For direct buffer comparison.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_find(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

/**
 * @brief Finds the last occurrence of a memory pattern within a larger buffer.
 *
 * This function searches backward for the last complete match of the @p rhs pattern
 * within the @p lhs buffer. Returns the starting position of the match or NULL if
 * not found.
 *
 * @param[in] lhs       Pointer to the haystack buffer to search.
 * @param[in] lhs_size  Size of the haystack buffer in bytes.
 * @param[in] rhs       Pointer to the needle pattern to find.
 * @param[in] rhs_size  Size of the needle pattern in bytes.
 *
 * @return - Pointer to last occurrence of @p rhs within @p lhs
 *         - NULL if pattern not found
 *         - NULL if either buffer is empty or pattern is larger than haystack
 *
 * @note Uses reverse comparison (eya_memory_rcompare) for efficient backward search.
 * @warning Returns NULL immediately if:
 *          - Either size is zero
 *          - Needle is larger than haystack
 *          - Any pointer is invalid
 * @see eya_memory_find    For forward search (first occurrence).
 * @see eya_memory_rcompare For reverse memory comparison.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_rfind(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_H