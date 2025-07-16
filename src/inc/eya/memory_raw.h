/**
 * @file memory_raw.h
 * @brief Low-level Memory Operations with Pointer Ranges
 *
 * Provides raw memory manipulation functions using pointer ranges [start, end)
 * instead of explicit size parameters. Designed for:
 * - Maximum performance in memory-bound operations
 * - Direct integration with pointer-based algorithms
 * - Working with half-open ranges common in C++ STL and system programming
 *
 * Key characteristics:
 * - Uses pointer arithmetic for all size calculations
 * - Supports both forward and reverse operations
 * - Provides raw versions of all standard memory operations
 * - Designed for use in performance-critical sections
 *
 * All functions:
 * - Operate on [start, end) pointer ranges
 * - Calculate sizes via pointer difference
 * - Preserve the same safety guarantees as sized versions
 * - Are marked with EYA_ATTRIBUTE(SYMBOL) for proper linkage
 *
 * @warning These are low-level operations - prefer sized versions (eya_memory_*)
 *          when safety is more important than performance.
 */

#ifndef EYA_MEMORY_RAW_H
#define EYA_MEMORY_RAW_H

#include "attribute.h"
#include "numeric_types.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Copies memory between buffers using end pointers instead of sizes.
 *
 * Copies data from source buffer to destination buffer using pointer ranges.
 * The number of bytes copied is the minimum of available space in both buffers:
 * - Destination space: `dst_end - dst`
 * - Source space: `src_end - src`
 *
 * @param[out] dst     Pointer to the start of destination memory block.
 * @param[in]  dst_end Pointer to the end of destination buffer (exclusive).
 * @param[in]  src     Pointer to the start of source memory block.
 * @param[in]  src_end Pointer to the end of source buffer (exclusive).
 *
 * @return Pointer to the byte immediately following the last copied byte
 *         in the destination buffer (dst + min(dst_end-dst, src_end-src)).
 *
 * @note Uses pointer arithmetic to calculate available space:
 *       - dst_size = reinterpret_cast<uintptr_t>(dst_end) - reinterpret_cast<uintptr_t>(dst)
 *       - src_size = reinterpret_cast<uintptr_t>(src_end) - reinterpret_cast<uintptr_t>(src)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `dst_end < dst` or `src_end < src`
 *          - Buffer ranges overlap incorrectly
 * @note Ideal for working with half-open ranges [start, end) commonly used in:
 *       - String processing
 *       - Container implementations
 *       - Iterators
 *
 * @see eya_memory_copy()
 *
 * Example:
 * @code
 * char dest[10];
 * const char src[] = "Hello";
 * void *result = eya_memory_raw_copy(
 *     dest, dest + sizeof(dest),
 *     src,  src + sizeof(src));
 * // Copies min(10, 6) = 6 bytes
 * // Returns dest + 6
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_raw_copy(void *dst, const void *dst_end, const void *src, const void *src_end);

/**
 * @brief Copies bytes from source to destination in reversed order using pointer ranges.
 *
 * This function copies bytes from the source range [@p src, @p src_end) to the destination
 * range [@p dst, @p dst_end) in reversed order. The number of bytes copied is the minimum
 * of the destination and source range sizes.
 *
 * The copy operation reverses the byte order - the first byte of the source range becomes
 * the last byte of the destination range, and so on. The ranges must be valid and should
 * not overlap.
 *
 * @param[out] dst     Pointer to the start of the destination memory range.
 * @param[in]  dst_end Pointer to the end of the destination memory range (exclusive).
 * @param[in]  src     Pointer to the start of the source memory range.
 * @param[in]  src_end Pointer to the end of the source memory range (exclusive).
 *
 * @return Returns a pointer to the destination memory location (@p dst).
 *
 * @note The function calculates the sizes using @p eya_ptr_udiff and delegates to
 *       @p eya_memory_copy_rev which performs the actual copy with size checking.
 * @note The ranges are half-open intervals: [start, end).
 *
 * @warning The behavior is undefined if:
 *          - The ranges overlap
 *          - @p dst_end comes before @p dst
 *          - @p src_end comes before @p src
 *          - Any pointer is NULL
 *
 * @see eya_memory_copy_rev      For the size-checked version of reverse copy.
 * @see eya_memory_std_copy_rev  For the low-level reverse copy implementation.
 * @see eya_ptr_udiff            For the pointer difference calculation.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_raw_copy_rev(void *dst, const void *dst_end, const void *src, const void *src_end);

/**
 * @brief Performs reverse memory copy using end pointers instead of sizes.
 *
 * Copies data from source to destination buffers in reverse order (from end to start)
 * using pointer ranges. The number of bytes copied is the minimum of:
 * - Destination space: `dst_end - dst`
 * - Source space: `src_end - src`
 *
 * @param[out] dst     Pointer to the start of destination memory block.
 * @param[in]  dst_end Pointer to the end of destination buffer (exclusive).
 * @param[in]  src     Pointer to the start of source memory block.
 * @param[in]  src_end Pointer to the end of source buffer (exclusive).
 *
 * @return Pointer to the beginning of the destination buffer (dst).
 *         Unlike forward copy, reverse copy returns the start address.
 *
 * @note Calculation of buffer sizes:
 *       - dst_size = reinterpret_cast<uintptr_t>(dst_end) - reinterpret_cast<uintptr_t>(dst)
 *       - src_size = reinterpret_cast<uintptr_t>(src_end) - reinterpret_cast<uintptr_t>(src)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `dst_end < dst` or `src_end < src`
 *          - Source and destination buffers overlap in undefined ways
 * @note Critical for overlapping regions where src < dst
 *       (source starts before destination in memory).
 *
 * @see eya_memory_rcopy()
 *
 * Example:
 * @code
 * char dest[5] = {0};
 * const char src[] = "HelloWorld";
 * void *result = eya_memory_raw_rcopy(
 *     dest, dest + 5,
 *     src,  src + sizeof(src));
 * // Copies last 5 bytes of src ("World") to dest
 * // Returns dest (pointer to start of buffer)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_raw_rcopy(void *dst, const void *dst_end, const void *src, const void *src_end);

/**
 * @brief Safely moves memory between potentially overlapping buffers
 *        using end pointers instead of sizes.
 *
 * Moves data from source to destination buffer, automatically handling
 * overlapping regions by selecting optimal copy direction (forward or reverse).
 * The number of bytes moved is the minimum of:
 * - Destination space: `dst_end - dst`
 * - Source space: `src_end - src`
 *
 * @param[out] dst     Pointer to the start of destination memory block.
 * @param[in]  dst_end Pointer to the end of destination buffer (exclusive).
 * @param[in]  src     Pointer to the start of source memory block.
 * @param[in]  src_end Pointer to the end of source buffer (exclusive).
 *
 * @return Pointer to the byte immediately following the last moved byte
 *         in the destination buffer (dst + min(dst_end-dst, src_end-src)).
 *
 * @note Uses pointer arithmetic to calculate available space:
 *       - dst_size = reinterpret_cast<uintptr_t>(dst_end) - reinterpret_cast<uintptr_t>(dst)
 *       - src_size = reinterpret_cast<uintptr_t>(src_end) - reinterpret_cast<uintptr_t>(src)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `dst_end < dst` or `src_end < src`
 * @note Automatically handles overlapping regions:
 *       - Uses forward copy if dst < src
 *       - Uses reverse copy if src < dst
 *       - Direct assignment if buffers are identical
 *
 * @see eya_memory_move()
 *
 * Example:
 * @code
 * char buffer[10] = "ABCDEFGHI";
 * // Move "DEFG" to overlap with "CDEF" (src: [3-7], dst: [2-6])
 * void *result = eya_memory_raw_move(
 *     buffer + 2, buffer + 6,
 *     buffer + 3, buffer + 7);
 * // Result: "ABDEFG" (safe move with overlap handling)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_raw_move(void *dst, const void *dst_end, const void *src, const void *src_end);

/**
 * @brief Fills a memory block with a specified value using end pointers.
 *
 * Sets each byte in the destination memory block defined by [dst, dst_end)
 * to the specified value. The size of the operation is automatically calculated
 * as the difference between the end and start pointers.
 *
 * @param[out] dst     Pointer to the start of destination memory block.
 * @param[in]  dst_end Pointer to the end of destination buffer (exclusive).
 * @param[in]  val     Value to set (interpreted as unsigned char).
 *
 * @return Pointer to the byte immediately following the filled memory block
 *         (dst_end).
 *
 * @note Size calculation:
 *       - n = reinterpret_cast<uintptr_t>(dst_end) - reinterpret_cast<uintptr_t>(dst)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `dst_end < dst`
 *          - `dst` is NULL (unless validation enabled)
 * @note More efficient than manual loops due to:
 *       - SIMD optimizations (AVX-512/AVX2/SSE2)
 *       - Compiler intrinsics for memory operations
 * @see eya_memory_set()
 *
 * Example:
 * @code
 * char buffer[100];
 * // Fill entire buffer with 'A'
 * void *result = eya_memory_raw_set(
 *     buffer, buffer + sizeof(buffer),
 *     'A');
 * // result == buffer + sizeof(buffer)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_raw_set(void *dst, const void *dst_end, eya_uchar_t val);

/**
 * @brief Fills a memory range [dst, dst_end)
 *        with a repeating pattern from [src, src_end).
 *
 * This function safely copies the source pattern repeatedly into the destination range,
 * using pointer arithmetic to determine buffer sizes. It provides a more intuitive interface
 * for working with pointer-based ranges while maintaining full safety through runtime checks.
 *
 * @param[out] dst     Pointer to the start of the destination range (inclusive).
 * @param[in]  dst_end Pointer to the end of the destination range (exclusive).
 * @param[in]  src     Pointer to the start of the source pattern (inclusive).
 * @param[in]  src_end Pointer to the end of the source pattern (exclusive).
 *
 * @return Returns the original destination pointer (dst) on success.
 *         Returns NULL if the destination or source range is empty
 *         (dst == dst_end or src == src_end).
 *
 * @note Both dst_end and src_end pointers are validated via eya_runtime_check_ref.
 * @note Internally converts pointer ranges to sizes and calls eya_memory_set_pattern.
 * @warning Returns NULL if either range is empty (zero-size operation).
 * @warning The function assumes valid pointer ranges (dst_end >= dst and src_end >= src).
 *
 * @see eya_memory_set_pattern For the size-based version of this operation.
 * @see eya_memory_raw_set     For filling a range with a single byte value.
 * @see eya_ptr_udiff          For details on pointer difference calculation.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_raw_set_pattern(void *dst, const void *dst_end, const void *src, const void *src_end);

/**
 * @brief Compares two memory blocks using end pointers instead of sizes.
 *
 * Compares the contents of two memory blocks defined by pointer ranges [lhs, lhs_end)
 * and [rhs, rhs_end). The comparison is performed on the first `n` bytes where `n`
 * is the minimum of the sizes of both buffers.
 *
 * @param[in] lhs     Pointer to the start of first memory block (left-hand side).
 * @param[in] lhs_end Pointer to the end of first buffer (exclusive).
 * @param[in] rhs     Pointer to the start of second memory block (right-hand side).
 * @param[in] rhs_end Pointer to the end of second buffer (exclusive).
 *
 * @return
 *   - `NULL` if both memory blocks are identical in the first `n` bytes
 *   - Pointer to the first differing byte in `lhs` if a difference is found
 *
 * @note Size calculation:
 *       - lhs_size = reinterpret_cast<uintptr_t>(lhs_end) - reinterpret_cast<uintptr_t>(lhs)
 *       - rhs_size = reinterpret_cast<uintptr_t>(rhs_end) - reinterpret_cast<uintptr_t>(rhs)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `lhs_end < lhs` or `rhs_end < rhs`
 * @note Ideal for comparing data structures with pointer-based ranges:
 *       - String slices
 *       - Array segments
 *       - Memory-mapped regions
 *
 * @see eya_memory_compare()
 *
 * Example:
 * @code
 * const char data1[] = "HelloWorld";
 * const char data2[] = "HelloUniverse";
 * const void *diff = eya_memory_raw_compare(
 *     data1, data1 + 10,
 *     data2, data2 + 10);
 * // Compares first 10 bytes, diff points to 'W' in data1 (position 5)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_raw_compare(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end);

/**
 * @brief Compares two memory blocks in reverse order using end pointers.
 *
 * Compares the suffix regions of two memory blocks defined by pointer ranges
 * [lhs, lhs_end) and [rhs, rhs_end). The comparison starts from the ends of
 * the buffers and moves backward, comparing the last `n` bytes where `n` is
 * the minimum of the buffer sizes.
 *
 * @param[in] lhs     Pointer to the start of first memory block (left-hand side).
 * @param[in] lhs_end Pointer to the end of first buffer (exclusive).
 * @param[in] rhs     Pointer to the start of second memory block (right-hand side).
 * @param[in] rhs_end Pointer to the end of second buffer (exclusive).
 *
 * @return
 *   - `NULL` if the suffix regions are identical
 *   - Pointer to the first differing byte (from the end) in the original `lhs` block
 *
 * @note Size calculation:
 *       - lhs_size = reinterpret_cast<uintptr_t>(lhs_end) - reinterpret_cast<uintptr_t>(lhs)
 *       - rhs_size = reinterpret_cast<uintptr_t>(rhs_end) - reinterpret_cast<uintptr_t>(rhs)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `lhs_end < lhs` or `rhs_end < rhs`
 * @note Critical for detecting suffix differences in:
 *       - Checksum verification
 *       - File format trailers
 *       - Network packet footers
 * @see eya_memory_rcompare()
 *
 * Example:
 * @code
 * const char log1[] = "[2023] Process completed";
 * const char log2[] = "[2024] Process completed";
 * const void *diff = eya_memory_raw_rcompare(
 *     log1, log1 + sizeof(log1)-1,
 *     log2, log2 + sizeof(log2)-1);
 * // Compares suffixes, diff points to '3' in "2023" (first difference from end)
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_raw_rcompare(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end);

/**
 * @brief Finds the first occurrence of a sub-buffer within a larger buffer
 *        using end pointers instead of sizes.
 *
 * Searches for the first occurrence of the sub-buffer `[rhs, rhs_end)` within
 * the main buffer `[lhs, lhs_end)`. The search is performed byte-by-byte from
 * the start of the main buffer.
 *
 * @param[in] lhs     Pointer to the start of main memory block to search in.
 * @param[in] lhs_end Pointer to the end of main buffer (exclusive).
 * @param[in] rhs     Pointer to the start of sub-buffer to find.
 * @param[in] rhs_end Pointer to the end of sub-buffer to find (exclusive).
 *
 * @return
 *   - Pointer to the first occurrence of the sub-buffer within the main buffer
 *   - `lhs_end` if the sub-buffer is not found
 *   - `lhs` if the sub-buffer is empty (size 0)
 *
 * @note Size calculation:
 *       - lhs_size = reinterpret_cast<uintptr_t>(lhs_end) - reinterpret_cast<uintptr_t>(lhs)
 *       - rhs_size = reinterpret_cast<uintptr_t>(rhs_end) - reinterpret_cast<uintptr_t>(rhs)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `lhs_end < lhs` or `rhs_end < rhs`
 * @note Search characteristics:
 *       - Returns immediately if sub-buffer is larger than main buffer
 *       - Handles empty sub-buffers as special case (returns start of main buffer)
 *       - Uses optimized byte-scanning algorithms
 * @see eya_memory_find()
 *
 * Example:
 * @code
 * const char data[] = "Hello amazing world";
 * const char sub[] = "amazing";
 * const void *pos = eya_memory_raw_find(
 *     data, data + sizeof(data)-1,
 *     sub,  sub + sizeof(sub)-1);
 * // pos points to "amazing world" within data
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_raw_find(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end);

/**
 * @brief Finds the last occurrence of a sub-buffer within a larger buffer
 *        using end pointers instead of sizes.
 *
 * Searches for the last occurrence of the sub-buffer `[rhs, rhs_end)` within
 * the main buffer `[lhs, lhs_end)`. The search is performed from the end of
 * the main buffer backward toward the start.
 *
 * @param[in] lhs     Pointer to the start of main memory block to search in.
 * @param[in] lhs_end Pointer to the end of main buffer (exclusive).
 * @param[in] rhs     Pointer to the start of sub-buffer to find.
 * @param[in] rhs_end Pointer to the end of sub-buffer to find (exclusive).
 *
 * @return
 *   - Pointer to the start of the last occurrence of the sub-buffer
 *   - `lhs_end` if the sub-buffer is not found
 *   - `lhs` if the sub-buffer is empty (size 0)
 *
 * @note Size calculation:
 *       - lhs_size = reinterpret_cast<uintptr_t>(lhs_end) - reinterpret_cast<uintptr_t>(lhs)
 *       - rhs_size = reinterpret_cast<uintptr_t>(rhs_end) - reinterpret_cast<uintptr_t>(rhs)
 * @warning Behavior is undefined if:
 *          - Pointers are not in the same memory segment
 *          - `lhs_end < lhs` or `rhs_end < rhs`
 * @note Search characteristics:
 *       - Returns immediately if sub-buffer is larger than main buffer
 *       - More efficient than forward search for finding last occurrences
 *       - Uses reverse scanning optimization
 * @see eya_memory_rfind()
 *
 * Example:
 * @code
 * const char data[] = "apple orange apple";
 * const char sub[] = "apple";
 * const void *pos = eya_memory_raw_rfind(
 *     data, data + sizeof(data)-1,
 *     sub,  sub + sizeof(sub)-1);
 * // pos points to the second "apple" in the string
 * @endcode
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_raw_rfind(const void *lhs, const void *lhs_end, const void *rhs, const void *rhs_end);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_RAW_H