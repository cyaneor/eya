#ifndef EYA_MEMORY_STD_H
#define EYA_MEMORY_STD_H

#include "attribute.h"
#include "size.h"
#include "char.h"

EYA_COMPILER(EXTERN_C_BEGIN)

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
eya_memory_std_set(void *dst, eya_char_t val, eya_usize_t n);

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_MEMORY_STD_H