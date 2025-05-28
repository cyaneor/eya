#ifndef EYA_MEMORY_STD_H
#define EYA_MEMORY_STD_H

#include "attribute.h"
#include "size.h"
#include "char.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Copies a block of memory from source
 *        to destination using optimized SIMD instructions if available.
 *
 * This function copies `n` bytes from the memory block pointed to by `src` to the memory block
 * pointed to by `dst`. It utilizes SIMD instructions (AVX-512, AVX2, or SSE2) for optimal
 * performance when the respective compile-time options and CPU features are enabled.
 * Remaining bytes are copied using a standard byte-wise loop.
 *
 * @param[out] dst Pointer to the destination memory block where the content is copied.
 * @param[in]  src Pointer to the source memory block to copy from.
 * @param[in]  n   Number of bytes to copy.
 *
 * @return Pointer to the byte immediately following the last copied byte
 *         in the destination memory block (i.e., `dst + n`).
 *
 * @note The function performs runtime checks on both `dst` and `src` pointers
 *       using  `eya_runtime_check_ref()` for debugging or safety validation.
 * @note SIMD optimizations are prioritized in the following order
 *       (if enabled at compile time and supported by the CPU):
 *       - **AVX-512**: Processes 64-byte blocks.
 *       - **AVX2**: Processes 32-byte blocks.
 *       - **SSE2**: Processes 16-byte blocks.
 *       Remaining bytes are handled with a byte-wise loop.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_copy(void *__restrict dst, const void *__restrict src, eya_usize_t n);

/**
 * @brief Copies a block of memory from source to destination
 *        in reverse order using optimized SIMD instructions if available.
 *
 * This function copies `n` bytes from the memory block pointed to by `src`
 * to the memory block pointed to by `dst`, starting from the end of the blocks
 * and moving backwards.
 *
 * It utilizes SIMD instructions (AVX-512, AVX2, or SSE2) for optimal performance
 * when the respective compile-time options and CPU features are enabled.
 * Remaining bytes are copied using a standard byte-wise loop in reverse.
 *
 * @param[out] dst Pointer to the destination memory block where the content is copied.
 * @param[in]  src Pointer to the source memory block to copy from.
 * @param[in]  n   Number of bytes to copy.
 *
 * @return Pointer to the start of the destination memory block (i.e., `dst`).
 *
 * @note The function performs runtime checks on both `dst` and `src`
 *       pointers using `eya_runtime_check_ref()` for debugging or safety validation.
 * @note SIMD optimizations are prioritized in the following order
 *       (if enabled at compile time and supported by the CPU):
 *       - **AVX-512**: Processes 64-byte blocks backwards.
 *       - **AVX2**: Processes 32-byte blocks backwards.
 *       - **SSE2**: Processes 16-byte blocks backwards.
 *       Remaining bytes are handled with a byte-wise loop in reverse.
 * @note This reverse copy is useful for overlapping memory regions
 *       where copying from the end prevents data corruption.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_rcopy(void *__restrict dst, const void *__restrict src, eya_usize_t n);

/**
 * @brief Safely moves a block of memory from source to destination,
 *        handling overlapping regions correctly.
 *
 * This function moves `n` bytes from the memory block pointed to by `src`
 * to the memory block pointed to by `dst`. It automatically determines
 * whether to perform a forward copy or reverse copy based on whether
 * the source and destination memory regions overlap.
 *
 * If the regions do not overlap, it performs a standard forward copy
 * using `eya_memory_std_copy()`. If they do overlap, it performs
 * a reverse copy using `eya_memory_std_rcopy()` to prevent data corruption.
 *
 * @param[out] dst Pointer to the destination memory block where the content is moved.
 * @param[in]  src Pointer to the source memory block to move from.
 * @param[in]  n   Number of bytes to move.
 *
 * @return Pointer to the byte immediately following the last moved byte
 *         in the destination memory block (i.e., `dst + n`).
 *
 * @note The function uses `eya_ptr_ranges_no_overlap()` to check
 *       for memory overlap between source and destination regions.
 * @note For non-overlapping regions, it delegates to `eya_memory_std_copy()`
 *       which may use optimized SIMD instructions.
 * @note For overlapping regions, it uses `eya_memory_std_rcopy()`
 *       which performs the copy in reverse order to ensure correct results.
 * @note The function is marked with `restrict` qualifiers for both pointers,
 *       meaning the compiler can assume they don't alias each other (except
 *       for the case of overlapping regions which is handled specially).
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_move(void *__restrict dst, const void *__restrict src, eya_usize_t n);

/**
 * @brief Fills a block of memory with the specified value
 *        using optimized SIMD instructions if available.
 *
 * This function sets the first `n` bytes
 * of the memory block pointed to by `dst` to the value `val`.
 *
 * It utilizes SIMD instructions (AVX-512, AVX2, or SSE2)
 * for optimal performance when the respective compile-time options
 * and CPU features are enabled. Remaining bytes are filled using a standard loop.
 *
 * @param[in,out] dst Pointer to the destination memory block to fill.
 * @param[in]     val Value to set for each byte in the memory block.
 * @param[in]     n   Number of bytes to set.
 *
 * @return Pointer to the end of the filled memory block (i.e., `dst + n`).
 *
 * @note The function performs a runtime check on `dst`
 *       using `eya_runtime_check_ref()` for debugging or safety validation.
 * @note SIMD optimizations are prioritized in the following order
 *       (if enabled at compile time and supported by the CPU):
 *       - **AVX-512**: Processes 64-byte blocks.
 *       - **AVX2**: Processes 32-byte blocks.
 *       - **SSE2**: Processes 16-byte blocks.
 *       Remaining bytes are handled with a byte-wise loop.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_set(void *dst, eya_uchar_t val, eya_usize_t n);

/**
 * @brief Compares two memory blocks and returns the address of the first mismatch.
 *
 * This function performs a byte-wise comparison
 * of two memory blocks `lhs` and `rhs` for up to `n` bytes.
 * It employs optimized strategies based on the size of the data:
 * - Small blocks are processed using scalar operations
 * - Larger blocks utilize SIMD instructions (AVX2 or SSE2 as fallback) for efficiency
 *
 * The implementation includes pointer alignment optimizations
 * for AVX2 when handling large data blocks to maximize performance.
 *
 * @param[in] lhs Pointer to the first memory block.
 * @param[in] rhs Pointer to the second memory block.
 * @param[in] n Number of bytes to compare
 * @return Address of the first differing byte between `lhs` and `rhs`,
 *         or `nullptr` if all bytes are equal
 *
 * @note The function performs runtime checks on `lhs` and `rhs`
 *       to ensure they are valid references
 * @note The thresholds for switching between scalar
 *       and SIMD processing are determined by `EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD`,
 *       `EYA_MEMORY_STD_STREAM_THRESHOLD`, and `EYA_MEMORY_STD_SIMD_BLOCK`
 * @note If AVX2 is available (indicated by `EYA_MEMORY_STD_SIMD_LEVEL >= 256`),
 *       32-byte SIMD operations are used.
 * @note Otherwise,
 *       SSE2 16-byte operations serve as a fallback
 *
 * @note Pointer alignment to 32-byte or 64-byte boundaries
 *       is performed to optimize SIMD accesses
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_std_compare(const void *__restrict lhs, const void *__restrict rhs, eya_usize_t n);

/**
 * @brief Reverse-compares two memory blocks
 *        to find the first differing byte from the end.
 *
 * This function compares two memory blocks byte-by-byte
 * in reverse order (from the highest address to the lowest)
 * and returns the address of the first mismatching byte
 * in the left-hand side (LHS) block.
 *
 * It is optimized for performance using a combination of scalar
 * and SIMD-based strategies depending on the block size
 * and available CPU features.
 *
 * The implementation uses the following approach:
 * 1. **Small blocks**:
 *    Scalar comparison
 *    for sizes below `EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD`.
 * 2. **Alignment**:
 *    Adjusts pointers to optimize memory access patterns
 *    (32-byte or 64-byte boundaries).
 * 3. **SIMD processing**: Uses AVX-512, AVX2, or SSE2 instructions
 *    (based on `EYA_MEMORY_STD_SIMD_LEVEL`) for large/medium blocks
 *    (≥`EYA_MEMORY_STD_STREAM_THRESHOLD`).
 * 4. **Residual data**: Handles remaining bytes
 *    with scalar comparisons after SIMD processing.
 *
 * @param[in] lhs Pointer to the left-hand side (LHS) memory block.
 * @param[in] rhs Pointer to the right-hand side (RHS) memory block.
 * @param[in] n Number of bytes to compare.
 *
 * @return Address of the first differing byte in `lhs`,
 *         or `nullptr` if the blocks are identical.
 *
 * @note The `restrict` qualifier ensures `lhs` and `rhs` do not overlap.
 *       Violation results in undefined behavior.
 * @note Runtime checks (`eya_runtime_check_ref`) validate `lhs` and `rhs`.
 *       Invalid pointers may trigger errors.
 * @note Thresholds (e.g., `EYA_MEMORY_STD_STREAM_THRESHOLD`)
 *       and SIMD level (`EYA_MEMORY_STD_SIMD_LEVEL`) control optimization strategies.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_std_rcompare(const void *__restrict lhs, const void *__restrict rhs, eya_usize_t n);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_STD_H