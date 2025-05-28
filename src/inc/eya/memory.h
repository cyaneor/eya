#ifndef EYA_MEMORY_H
#define EYA_MEMORY_H

#include "attribute.h"
#include "size.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Safely copies memory between two buffers with size checking.
 *
 * Copies the minimum of `dst_size` and `src_size` bytes from the source buffer
 * to the destination buffer. The copy operation is performed using the optimized
 * `eya_memory_std_copy()` function with SIMD instructions (AVX-512/AVX2/SSE2)
 * when available.
 *
 * @param[out] dst       Pointer to the destination memory block.
 * @param[in]  dst_size  Size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source memory block.
 * @param[in]  src_size  Size of the source data available in bytes.
 *
 * @return Pointer to the byte immediately following the last copied byte
 *         in the destination buffer (dst + min(dst_size, src_size)).
 *
 * @note Inherits all optimization characteristics and runtime checks
 *       from `eya_memory_std_copy()`:
 *       - Uses SIMD optimizations (when enabled and available)
 *       - Performs runtime pointer validation
 *       - Processes remaining bytes with byte-wise loop
 * @warning Does not perform null-termination of the destination buffer.
 * @warning For overlapping memory regions, behavior is undefined.
 *
 * @see eya_memory_std_copy()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_copy(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Safely copies memory between two buffers in reverse order
 *        with size checking.
 *
 * Copies the minimum of `dst_size` and `src_size` bytes from the source buffer
 * to the destination buffer, starting from the end of the blocks and moving backwards.
 * This is particularly useful for overlapping memory regions where the source
 * starts before the destination. The operation is performed using the optimized
 * `eya_memory_std_rcopy()` function which may utilize SIMD instructions.
 *
 * @param[out] dst       Pointer to the destination memory block.
 * @param[in]  dst_size  Size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source memory block.
 * @param[in]  src_size  Size of the source data available in bytes.
 *
 * @return Pointer to the beginning of the destination buffer (dst).
 *         Unlike forward copy, reverse copy typically returns the start address.
 *
 * @note Inherits optimization characteristics from `eya_memory_std_rcopy()`:
 *       - Uses reverse-order SIMD optimizations when available
 *       - Performs runtime pointer validation
 *       - Processes bytes from high to low addresses
 * @warning For non-overlapping regions, forward copy (`eya_memory_copy`)
 *          may provide better performance.
 * @note Critical for handling overlapping regions where src < dst
 *       (source starts before destination in memory).
 *
 * @see eya_memory_std_rcopy()
 * @see eya_memory_copy()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_rcopy(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Safely moves memory between potentially overlapping buffers
 *        with size checking.
 *
 * Moves the minimum of `dst_size` and `src_size` bytes from the source buffer
 * to the destination buffer. Unlike standard copy functions, this operation
 * is safe for overlapping memory regions. The function automatically selects
 * the optimal copy direction (forward or reverse) to prevent data corruption
 * when source and destination buffers overlap.
 *
 * @param[out] dst       Pointer to the destination memory block.
 * @param[in]  dst_size  Size of the destination buffer in bytes.
 * @param[in]  src       Pointer to the source memory block.
 * @param[in]  src_size  Size of the source data available in bytes.
 *
 * @return Pointer to the byte immediately following the last moved byte
 *         in the destination buffer (dst + min(dst_size, src_size)).
 *
 * @note Inherits optimization characteristics from `eya_memory_std_move()`:
 *       - Uses SIMD optimizations when possible (non-overlapping regions)
 *       - Automatically selects copy direction for overlapping regions
 *       - Performs runtime pointer validation
 * @warning Always safe for overlapping regions, but may have performance
 *          overhead compared to `eya_memory_copy()` in non-overlapping cases.
 * @note Critical for moving data between overlapping memory blocks where
 *       source and destination addresses might be in any relative order.
 *
 * @see eya_memory_std_move()
 * @see eya_memory_copy()
 * @see eya_memory_rcopy()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_move(void *dst, eya_usize_t dst_size, const void *src, eya_usize_t src_size);

/**
 * @brief Fills a memory block with a specified byte value.
 *
 * Sets each byte in the destination memory block to the specified value.
 * This function utilizes optimized SIMD instructions (AVX-512, AVX2, or SSE2)
 * when available for maximum performance, with a fallback to byte-wise operations.
 *
 * @param[out] dst   Pointer to the destination memory block to fill.
 * @param[in]  size  Size of the memory block in bytes.
 * @param[in]  val   Value to set (interpreted as unsigned char).
 *
 * @return Pointer to the byte immediately following the filled memory block
 *         (dst + size).
 *
 * @note Inherits optimization characteristics from `eya_memory_std_set()`:
 *       - Uses SIMD instructions for large blocks when available
 *       - Processes remaining bytes with efficient byte-wise operations
 *       - Performs runtime pointer validation
 * @warning Behavior is undefined if `dst` is NULL (unless validation enabled)
 * @note More efficient than manual loops for memory initialization
 *       due to compiler intrinsics and SIMD optimizations.
 *
 * @see eya_memory_std_set()
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_set(void *dst, eya_usize_t size, eya_uchar_t val);

/**
 * @brief Safely compares two memory blocks with size checking.
 *
 * Compares the first `n` bytes of two memory blocks, where `n` is the minimum
 * of `lhs_size` and `rhs_size`. The comparison is byte-wise and stops at the
 * first differing byte found.
 *
 * @param[in] lhs       Pointer to the first memory block (left-hand side).
 * @param[in] lhs_size  Size of the first memory block in bytes.
 * @param[in] rhs       Pointer to the second memory block (right-hand side).
 * @param[in] rhs_size  Size of the second memory block in bytes.
 *
 * @return
 *   - `NULL` if both memory blocks are identical in the first `n` bytes
 *   - Pointer to the first differing byte in `lhs` if a difference is found
 *
 * @note Inherits optimization characteristics from `eya_memory_std_compare()`:
 *       - Uses SIMD instructions (SSE4.2, AVX2) for vectorized comparison
 *       - Optimized for large memory blocks with aligned access
 *       - Performs runtime pointer validation
 * @warning If buffer sizes are different, comparison is limited to the minimum size.
 * @note Return value semantics differ from standard memcmp():
 *       - Provides direct pointer to difference instead of integer result
 *       - NULL return indicates full equality in compared range
 *
 * @code
 * const char buf1[] = "Hello";
 * const char buf2[] = "Hellx";
 * const void *diff = eya_memory_compare(buf1, 5, buf2, 5);
 * // diff will point to 'o' in buf1 (position 4)
 * @endcode
 *
 * @see eya_memory_std_compare()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_compare(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

/**
 * @brief Safely compares two memory blocks in reverse order
 *        with size checking.
 *
 * Compares the last `n` bytes of two memory blocks (where `n` is the minimum
 * of `lhs_size` and `rhs_size`), starting from the ends of the buffers and
 * moving backward. This is useful for comparing data structures where meaningful
 * differences are likely to occur at the end (e.g., strings with different suffixes).
 *
 * @param[in] lhs       Pointer to the first memory block (left-hand side).
 * @param[in] lhs_size  Size of the first memory block in bytes.
 * @param[in] rhs       Pointer to the second memory block (right-hand side).
 * @param[in] rhs_size  Size of the second memory block in bytes.
 *
 * @return
 *   - `NULL` if the compared regions are identical
 *   - Pointer to the first differing byte (from the end) in `lhs`
 *     within the original memory block
 *
 * @note Inherits optimization characteristics from `eya_memory_std_rcompare()`:
 *       - Uses optimized reverse-order comparison with SIMD instructions
 *       - Processes bytes from high to low addresses
 *       - Performs runtime pointer validation
 * @warning Returns immediately with NULL if either buffer size is zero
 * @note Comparison is performed only on the overlapping suffix:
 *       - For buffers [A,B,C,D] (size=4) and [X,Y,Z] (size=3)
 *       - Compares C-D vs Y-Z (last 3 bytes)
 *
 * @code
 * const char buf1[] = "data_end";
 * const char buf2[] = "info_end";
 * // Compare last 7 bytes: "ta_end" vs "fo_end"
 * const void *diff = eya_memory_rcompare(buf1, 8, buf2, 8);
 * // diff points to 't' in "ta_end" (first difference from end)
 * @endcode
 *
 * @see eya_memory_std_rcompare()
 * @see eya_memory_compare()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_rcompare(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

/**
 * @brief Finds the first occurrence of a sub-buffer within a larger buffer.
 *
 * Searches for the first occurrence of the sub-buffer `rhs` (size `rhs_size`)
 * within the main buffer `lhs` (size `lhs_size`). The search starts from the
 * beginning of the main buffer and progresses byte-by-byte.
 *
 * @param[in] lhs       Pointer to the start of main memory block to search in.
 * @param[in] lhs_size  Size of the main buffer in bytes.
 * @param[in] rhs       Pointer to the start of sub-buffer to find.
 * @param[in] rhs_size  Size of the sub-buffer to find in bytes.
 *
 * @return
 *   - Pointer to the first occurrence of the sub-buffer within the main buffer
 *   - `nullptr` if the sub-buffer is not found
 *   - `nullptr` if either buffer size is zero
 *
 * @note Performs runtime pointer validation using `eya_runtime_check_ref()`
 * @note Comparison at each position uses `eya_memory_compare()`, which:
 *       - Compares only the minimum of remaining bytes and `rhs_size`
 *       - Utilizes SIMD optimizations for efficient comparison
 * @warning For complete match verification, ensure the remaining bytes after
 *          the found position are sufficient for the full sub-buffer size
 *
 * @see eya_memory_compare()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_find(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

/**
 * @brief Finds the last occurrence of a sub-buffer within a larger buffer
 *        by searching backward from the end.
 *
 * Searches for the last occurrence of the sub-buffer `rhs` (size `rhs_size`)
 * within the main buffer `lhs` (size `lhs_size`). The search starts from the
 * end of the main buffer and progresses backward byte-by-byte.
 *
 * @param[in] lhs       Pointer to the start of main memory block to search in.
 * @param[in] lhs_size  Size of the main buffer in bytes.
 * @param[in] rhs       Pointer to the start of sub-buffer to find.
 * @param[in] rhs_size  Size of the sub-buffer to find in bytes.
 *
 * @return
 *   - Pointer to the start of the last occurrence of the sub-buffer
 *   - `nullptr` if the sub-buffer is not found
 *   - `nullptr` if either buffer size is zero
 *
 * @note Performs runtime pointer validation using `eya_runtime_check_ref()`
 * @note Comparison at each position uses `eya_memory_rcompare()`, which:
 *       - Compares suffixes of the buffers
 *       - Utilizes reverse-order SIMD optimizations
 * @warning The found position may not have sufficient bytes after it for
 *          the full sub-buffer size - caller must verify buffer boundaries
 * @see eya_memory_rcompare()
 *
 * Example:
 * @code
 * const char data[] = "apple orange apple";
 * const char sub[] = "apple";
 * const void *pos = eya_memory_rfind(
 *     data, sizeof(data)-1,
 *     sub,  sizeof(sub)-1);
 * // pos points to the second "apple" in the string
 * @endcode
 *
 * @see eya_memory_rcompare()
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_rfind(const void *lhs, eya_usize_t lhs_size, const void *rhs, eya_usize_t rhs_size);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_H