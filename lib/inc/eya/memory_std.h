/**
 * @file memory_std.h
 * @brief Standard memory operations with safety checks and overlap handling
 *
 * This header provides a set of memory manipulation functions similar to standard
 * C library functions (memcpy, memmove, memset, memcmp) but with enhanced safety
 * features including:
 * - Runtime pointer validation
 * - Explicit overlap handling
 * - Reverse operation variants
 * - Consistent return value semantics
 *
 * All functions:
 * - Validate input pointers using eya_runtime_check_ref
 * - Return useful pointers for operation chaining
 * - Are marked with EYA_ATTRIBUTE(SYMBOL) for proper linkage
 * - Work with eya_usize_t for consistent sizing
 */

#ifndef EYA_MEMORY_STD_H
#define EYA_MEMORY_STD_H

#include "attribute.h"
#include "size.h"

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @brief Copies bytes from source memory location to destination.
 *
 * This function copies @p n bytes from the memory area pointed to by @p src
 * to the memory area pointed to by @p dst. Both memory areas must be valid
 * and accessible. The memory areas should not overlap (for overlapping
 * regions, consider using eya_memory_std_move instead).
 *
 * @param[out] dst Pointer to the destination memory location.
 * @param[in] src Pointer to the source memory location to copy from.
 * @param[in] n Number of bytes to copy.
 *
 * @return Returns a pointer to the destination memory location (@p dst).
 *
 * @note Both @p dst and @p src pointers are checked for validity using
 *       eya_runtime_check_ref before performing the copy operation.
 *
 * @warning The behavior is undefined
 *          if the source and destination buffers overlap.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_copy(void *dst, const void *src, eya_usize_t n);

/**
 * @brief Copies bytes from source to destination in reversed order.
 *
 * This function copies @p n bytes from the memory area pointed to by @p src
 * to the memory area pointed to by @p dst, reversing the order of bytes.
 *
 * The first byte of @p src becomes the last byte of @p dst, the second byte
 * of @p src becomes the second-to-last byte of @p dst, and so on.
 * The memory areas must be valid and accessible, and should not overlap.
 *
 * @param[out] dst Pointer to the destination memory location.
 * @param[in]  src Pointer to the source memory location to copy from.
 * @param[in]  n   Number of bytes to copy.
 *
 * @return Returns a pointer to the end of the destination memory location
 *         (@p dst + @p n).
 *
 * @note Both @p dst and @p src pointers are checked for validity using
 *       eya_runtime_check_ref before performing the copy operation.
 *
 * @warning The behavior is undefined if the source and destination buffers overlap.
 *
 * @see eya_memory_std_copy   For non-overlapping forward copy.
 * @see eya_memory_std_rcopy  For backward copy without reversing content.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_copy_rev(void *dst, const void *src, eya_usize_t n);

/**
 * @brief Copies bytes from source to destination in reverse order (backward copy).
 *
 * This function copies @p n bytes from @p src to @p dst, starting from the end
 * of the buffers and moving backward. Unlike a forward copy, this safely handles
 * overlapping regions where @p dst > @p src (e.g., shifting memory right without corruption).
 *
 * @param[out] dst Pointer to the destination memory location.
 * @param[in]  src Pointer to the source memory location to copy from.
 * @param[in]  n   Number of bytes to copy.
 *
 * @return Returns the original @p dst pointer (points to the start of the copied block).
 *
 * @note Both @p dst and @p src are checked for validity via eya_runtime_check_ref.
 * @warning If @p dst < @p src and the regions overlap, behavior is undefined.
 *          Use eya_memory_std_move for forward-copying overlapping regions.
 *
 * @see eya_memory_std_copy   For non-overlapping forward copy.
 * @see eya_memory_std_move   For safe forward copy with overlap.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_rcopy(void *dst, const void *src, eya_usize_t n);

/**
 * @brief Safely copies memory between potentially overlapping regions.
 *
 * This function copies @p n bytes from @p src to @p dst, automatically choosing
 * between forward (`eya_memory_std_copy`) or reverse (`eya_memory_std_rcopy`)
 * copying to prevent corruption when regions overlap. Unlike naive `memcpy`,
 * it guarantees correct results for overlapping blocks.
 *
 * @param[out] dst Pointer to the destination memory location.
 * @param[in]  src Pointer to the source memory location to copy from.
 * @param[in]  n   Number of bytes to copy.
 *
 * @return Returns the original @p dst pointer (start of the copied block).
 *
 * @note Internally checks for overlap using `eya_ptr_ranges_no_overlap`.
 *       - If no overlap: delegates to `eya_memory_std_copy` (faster forward copy).
 *       - If overlap exists: uses `eya_memory_std_rcopy` (safe backward copy).
 *
 * @warning If @p dst == @p src, no copy occurs (returns immediately).
 * @see eya_memory_std_copy   For non-overlapping forward copies.
 * @see eya_memory_std_rcopy  For explicit backward copies.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_move(void *dst, const void *src, eya_usize_t n);

/**
 * @brief Fills a memory block with a specified byte value.
 *
 * This function sets the first @p n bytes of the memory block pointed to by @p dst
 * to the value @p val. It is analogous to the standard `memset` function but with
 * runtime safety checks.
 *
 * @param[out] dst Pointer to the destination memory block to fill.
 * @param[in]  val Value to set (interpreted as an unsigned byte).
 * @param[in]  n   Number of bytes to fill.
 *
 * @return Returns a pointer to the end of the filled memory block (i.e., @p dst + @p n).
 *         This simplifies consecutive operations on adjacent memory regions.
 *
 * @note The destination pointer @p dst is validated using `eya_runtime_check_ref`.
 * @warning If @p n is zero, the function returns @p dst unchanged (no operation is performed).
 * @see eya_memory_std_copy For copying data between memory regions.
 * @see eya_memory_std_move For overlap-safe memory copying.
 */
EYA_ATTRIBUTE(SYMBOL)
void *
eya_memory_std_set(void *dst, eya_uchar_t val, eya_usize_t n);

/**
 * @brief Compares two memory blocks byte-by-byte.
 *
 * This function compares the first @p n bytes of the memory blocks pointed to by
 * @p lhs and @p rhs. It returns the position of the first differing byte, or
 * `nullptr` if the blocks are equal.
 *
 * @param[in] lhs Pointer to the first memory block to compare.
 * @param[in] rhs Pointer to the second memory block to compare.
 * @param[in] n   Number of bytes to compare.
 *
 * @return - A pointer to the first differing byte in @p lhs, if any.
 *         - `nullptr` if the blocks are equal for all @p n bytes.
 *
 * @note Both @p lhs and @p rhs are validated using eya_runtime_check_ref.
 * @warning If @p n is zero, the function returns `nullptr` (blocks are considered equal).
 * @see eya_memory_std_copy For copying memory blocks.
 * @see eya_memory_std_set For filling memory with a constant value.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_std_compare(const void *lhs, const void *rhs, eya_usize_t n);

/**
 * @brief Compares two memory blocks byte-by-byte in reverse order (from end to start).
 *
 * This function compares the last @p n bytes of the memory blocks pointed to by
 * @p lhs and @p rhs, moving backward. It returns the position of the last differing
 * byte (from the end), or `nullptr` if the blocks are equal.
 *
 * @param[in] lhs Pointer to the first memory block to compare.
 * @param[in] rhs Pointer to the second memory block to compare.
 * @param[in] n   Number of bytes to compare.
 *
 * @return - A pointer to the last differing byte in @p lhs (when viewed from the start), if any.
 *         - `nullptr` if the blocks are equal for all @p n bytes.
 *
 * @note Both @p lhs and @p rhs are validated using eya_runtime_check_ref.
 * @warning If @p n is zero, the function returns `nullptr` (blocks are considered equal).
 * @warning The function compares the last @p n bytes - ensure the pointers point to
 *          valid memory regions of at least size @p n.
 *
 * @see eya_memory_std_compare For forward comparison.
 * @see eya_memory_std_rcopy For reverse memory copying.
 */
EYA_ATTRIBUTE(SYMBOL)
const void *
eya_memory_std_rcompare(const void *lhs, const void *rhs, eya_usize_t n);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_STD_H