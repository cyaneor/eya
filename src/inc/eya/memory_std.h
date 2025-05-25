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
 * @brief Fills a block of memory with the specified value
 *        using optimized SIMD instructions if available.
 *
 * This function sets the first `n` bytes of the memory block pointed to by `dst` to the value
 * `val`. It utilizes SIMD instructions (AVX-512, AVX2, or SSE2) for optimal performance when the
 * respective compile-time options and CPU features are enabled. Remaining bytes are filled using
 * a standard loop.
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

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_STD_H