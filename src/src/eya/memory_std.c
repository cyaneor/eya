#include <eya/memory_std.h>
#include <eya/runtime_error_code.h>
#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

#if defined(EYA_COMPILE_OPTION_SSE2) || defined(EYA_COMPILE_OPTION_AVX2) ||                        \
    defined(EYA_COMPILE_OPTION_AVX512)
#    include <immintrin.h>
#endif

#ifndef EYA_MEMORY_STD_SIMD_LEVEL
#    if defined(EYA_COMPILE_OPTION_AVX512)
#        define EYA_MEMORY_STD_SIMD_LEVEL 512
#        define EYA_MEMORY_STD_SIMD_ALIGN 64
#        define EYA_MEMORY_STD_SIMD_BLOCK 64
#    elif defined(EYA_COMPILE_OPTION_AVX2)
#        define EYA_MEMORY_STD_SIMD_LEVEL 256
#        define EYA_MEMORY_STD_SIMD_ALIGN 32
#        define EYA_MEMORY_STD_SIMD_BLOCK 32
#    elif defined(EYA_COMPILE_OPTION_SSE2)
#        define EYA_MEMORY_STD_SIMD_LEVEL 128
#        define EYA_MEMORY_STD_SIMD_ALIGN 16
#        define EYA_MEMORY_STD_SIMD_BLOCK 16
#    else
#        define EYA_MEMORY_STD_SIMD_LEVEL 0
#        define EYA_MEMORY_STD_SIMD_ALIGN 8
#        define EYA_MEMORY_STD_SIMD_BLOCK 8
#    endif
#endif

#define EYA_MEMORY_STD_PTR_ALIGNMENT EYA_MEMORY_STD_SIMD_ALIGN

void *
eya_memory_std_copy(void *restrict dst, const void *restrict src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_uchar_t       *d = eya_ptr_cast(eya_uchar_t, dst);
    const eya_uchar_t *s = eya_ptr_cast(const eya_uchar_t, src);

    // 1. Processing of small blocks
    if (n <= EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD)
    {
        while (n >= 8)
        {
            *(eya_u64_t *)d = *(const eya_u64_t *)s;
            d += 8;
            s += 8;
            n -= 8;
        }
        if (n >= 4)
        {
            *(eya_u32_t *)d = *(const eya_u32_t *)s;
            d += 4;
            s += 4;
            n -= 4;
        }
        if (n >= 2)
        {
            *(eya_u16_t *)d = *(const eya_u16_t *)s;
            d += 2;
            s += 2;
            n -= 2;
        }
        if (n > 0)
        {
            *d++ = *s;
        }
        return d;
    }

    // 2. Alignment of the target buffer
    eya_usize_t align = eya_ptr_align_mask(d, EYA_MEMORY_STD_PTR_ALIGNMENT);
    if (align != EYA_MEMORY_STD_PTR_ALIGNMENT)
    {
        eya_usize_t head = align;
        n -= head;
        while (head--)
        {
            *d++ = *s++;
        }
    }

    // 3. Processing of large blocks with stream instructions
    if (n >= EYA_MEMORY_STD_STREAM_THRESHOLD)
    {
        // Source alignment
        eya_usize_t src_align = eya_ptr_align_mask(s, EYA_MEMORY_STD_STREAM_ALIGNMENT);
        if (src_align != EYA_MEMORY_STD_STREAM_ALIGNMENT)
        {
            eya_usize_t head = src_align;
            n -= head;
            while (head--)
            {
                *d++ = *s++;
            }
        }

        // Stream copying
        eya_usize_t stream_blocks = n / EYA_MEMORY_STD_STREAM_ALIGNMENT;
        while (stream_blocks--)
        {
#if EYA_MEMORY_STD_SIMD_LEVEL >= 512
            __m512i val = _mm512_loadu_si512((__m512i *)s);
            _mm512_stream_si512((__m512i *)d, val);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 256
            __m256i v0 = _mm256_loadu_si256((__m256i *)(s + 0));
            __m256i v1 = _mm256_loadu_si256((__m256i *)(s + 32));
            _mm256_stream_si256((__m256i *)(d + 0), v0);
            _mm256_stream_si256((__m256i *)(d + 32), v1);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 128
            __m128i v0 = _mm_loadu_si128((__m128i *)(s + 0));
            __m128i v1 = _mm_loadu_si128((__m128i *)(s + 16));
            __m128i v2 = _mm_loadu_si128((__m128i *)(s + 32));
            __m128i v3 = _mm_loadu_si128((__m128i *)(s + 48));
            _mm_stream_si128((__m128i *)(d + 0), v0);
            _mm_stream_si128((__m128i *)(d + 16), v1);
            _mm_stream_si128((__m128i *)(d + 32), v2);
            _mm_stream_si128((__m128i *)(d + 48), v3);
#else
            // Fallback for non-SIMD: copy in 64-bit chunks
            for (eya_usize_t i = 0; i < EYA_MEMORY_STD_STREAM_ALIGNMENT; i += 8)
            {
                *(eya_u64_t *)(d + i) = *(const eya_u64_t *)(s + i);
            }
#endif
            d += EYA_MEMORY_STD_STREAM_ALIGNMENT;
            s += EYA_MEMORY_STD_STREAM_ALIGNMENT;
            n -= EYA_MEMORY_STD_STREAM_ALIGNMENT;
        }
#if EYA_MEMORY_STD_SIMD_LEVEL > 0
        _mm_sfence();
#endif
    }

    // 4. SIMD optimization for medium blocks
    if (n >= EYA_MEMORY_STD_SIMD_BLOCK)
    {
        eya_usize_t simd_blocks = n / EYA_MEMORY_STD_SIMD_BLOCK;
        while (simd_blocks--)
        {
#if EYA_MEMORY_STD_SIMD_LEVEL >= 512
            __m512i val = _mm512_loadu_si512(s);
            _mm512_storeu_si512(d, val);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 256
            __m256i val = _mm256_loadu_si256((__m256i *)s);
            _mm256_storeu_si256((__m256i *)d, val);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 128
            __m128i val = _mm_loadu_si128((__m128i *)s);
            _mm_storeu_si128((__m128i *)d, val);
#else
            // Fallback for non-SIMD: copy in 64-bit chunks
            for (eya_usize_t i = 0; i < EYA_MEMORY_STD_SIMD_BLOCK; i += 8)
            {
                *(eya_u64_t *)(d + i) = *(const eya_u64_t *)(s + i);
            }
#endif
            d += EYA_MEMORY_STD_SIMD_BLOCK;
            s += EYA_MEMORY_STD_SIMD_BLOCK;
            n -= EYA_MEMORY_STD_SIMD_BLOCK;
        }
    }

    // 5. Residual data processing
    while (n >= 8)
    {
        *(eya_u64_t *)d = *(const eya_u64_t *)s;
        d += 8;
        s += 8;
        n -= 8;
    }
    if (n >= 4)
    {
        *(eya_u32_t *)d = *(const eya_u32_t *)s;
        d += 4;
        s += 4;
        n -= 4;
    }
    if (n >= 2)
    {
        *(eya_u16_t *)d = *(const eya_u16_t *)s;
        d += 2;
        s += 2;
        n -= 2;
    }
    if (n > 0)
    {
        *d++ = *s;
    }

    return d;
}

void *
eya_memory_std_rcopy(void *restrict dst, const void *restrict src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_uchar_t       *d = eya_ptr_add_offset_unsafe(eya_uchar_t, dst, n);
    const eya_uchar_t *s = eya_ptr_add_offset_unsafe(const eya_uchar_t, src, n);

    // 1. Processing of small blocks
    if (n <= EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD)
    {
        while (n >= 8)
        {
            d -= 8;
            s -= 8;
            *(eya_u64_t *)d = *(const eya_u64_t *)s;
            n -= 8;
        }
        if (n >= 4)
        {
            d -= 4;
            s -= 4;
            *(eya_u32_t *)d = *(const eya_u32_t *)s;
            n -= 4;
        }
        if (n >= 2)
        {
            d -= 2;
            s -= 2;
            *(eya_u16_t *)d = *(const eya_u16_t *)s;
            n -= 2;
        }
        if (n > 0)
        {
            *(--d) = *(--s);
        }
        return d;
    }

    // 2. Alignment of the target buffer for streaming
    eya_usize_t align = eya_ptr_align_mask(d - n, EYA_MEMORY_STD_STREAM_ALIGNMENT);
    if (align != EYA_MEMORY_STD_STREAM_ALIGNMENT)
    {
        eya_usize_t head = align;
        n -= head;
        while (head--)
        {
            *(--d) = *(--s);
        }
    }

    // 3. Processing of large blocks with stream instructions
    if (n >= EYA_MEMORY_STD_STREAM_THRESHOLD)
    {
        // Source alignment
        eya_usize_t src_align = eya_ptr_align_mask(s - n, EYA_MEMORY_STD_STREAM_ALIGNMENT);
        if (src_align != EYA_MEMORY_STD_STREAM_ALIGNMENT)
        {
            eya_usize_t head = src_align;
            n -= head;
            while (head--)
            {
                *(--d) = *(--s);
            }
        }

        // Stream copying in reverse
        eya_usize_t stream_blocks = n / EYA_MEMORY_STD_STREAM_ALIGNMENT;
        while (stream_blocks--)
        {
            d -= EYA_MEMORY_STD_STREAM_ALIGNMENT;
            s -= EYA_MEMORY_STD_STREAM_ALIGNMENT;
#if EYA_MEMORY_STD_SIMD_LEVEL >= 512
            __m512i val = _mm512_loadu_si512(s);
            _mm512_stream_si512(d, val);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 256
            __m256i v0 = _mm256_loadu_si256((const __m256i *)(s + 0));
            __m256i v1 = _mm256_loadu_si256((const __m256i *)(s + 32));
            _mm256_stream_si256((__m256i *)(d + 0), v0);
            _mm256_stream_si256((__m256i *)(d + 32), v1);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 128
            __m128i v0 = _mm_loadu_si128((const __m128i *)(s + 0));
            __m128i v1 = _mm_loadu_si128((const __m128i *)(s + 16));
            __m128i v2 = _mm_loadu_si128((const __m128i *)(s + 32));
            __m128i v3 = _mm_loadu_si128((const __m128i *)(s + 48));
            _mm_stream_si128((__m128i *)(d + 0), v0);
            _mm_stream_si128((__m128i *)(d + 16), v1);
            _mm_stream_si128((__m128i *)(d + 32), v2);
            _mm_stream_si128((__m128i *)(d + 48), v3);
#else
            // Fallback for non-SIMD: copy in 64-bit chunks
            for (eya_usize_t i = 0; i < EYA_MEMORY_STD_STREAM_ALIGNMENT; i += 8)
            {
                *(eya_u64_t *)(d + i) = *(const eya_u64_t *)(s + i);
            }
#endif
            n -= EYA_MEMORY_STD_STREAM_ALIGNMENT;
        }
#if EYA_MEMORY_STD_SIMD_LEVEL > 0
        _mm_sfence();
#endif
    }

    // 4. SIMD optimization for medium blocks
    if (n >= EYA_MEMORY_STD_SIMD_BLOCK)
    {
        eya_usize_t simd_blocks = n / EYA_MEMORY_STD_SIMD_BLOCK;
        while (simd_blocks--)
        {
            d -= EYA_MEMORY_STD_SIMD_BLOCK;
            s -= EYA_MEMORY_STD_SIMD_BLOCK;
#if EYA_MEMORY_STD_SIMD_LEVEL >= 512
            __m512i val = _mm512_loadu_si512(s);
            _mm512_storeu_si512(d, val);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 256
            __m256i val = _mm256_loadu_si256((const __m256i *)s);
            _mm256_storeu_si256((__m256i *)d, val);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 128
            __m128i val = _mm_loadu_si128((const __m128i *)s);
            _mm_storeu_si128((__m128i *)d, val);
#else
            // Fallback for non-SIMD: copy in 64-bit chunks
            for (eya_usize_t i = 0; i < EYA_MEMORY_STD_SIMD_BLOCK; i += 8)
            {
                *(eya_u64_t *)(d + i) = *(const eya_u64_t *)(s + i);
            }
#endif
            n -= EYA_MEMORY_STD_SIMD_BLOCK;
        }
    }

    // 5. Residual data processing
    while (n >= 8)
    {
        d -= 8;
        s -= 8;
        *(eya_u64_t *)d = *(const eya_u64_t *)s;
        n -= 8;
    }
    if (n >= 4)
    {
        d -= 4;
        s -= 4;
        *(eya_u32_t *)d = *(const eya_u32_t *)s;
        n -= 4;
    }
    if (n >= 2)
    {
        d -= 2;
        s -= 2;
        *(eya_u16_t *)d = *(const eya_u16_t *)s;
        n -= 2;
    }
    if (n > 0)
    {
        *(--d) = *(--s);
    }

    return d;
}

void *
eya_memory_std_move(void *restrict dst, const void *restrict src, eya_usize_t n)
{
    const void *src_end = eya_ptr_add(const void *, src, n);
    if (eya_ptr_ranges_no_overlap(dst, src, src_end))
    {
        return eya_memory_std_copy(dst, src, n);
    }
    void *d = eya_memory_std_rcopy(dst, src, n);
    return eya_ptr_add(void *, d, n);
}

void *
eya_memory_std_set(void *dst, eya_uchar_t val, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_uchar_t *d = eya_ptr_cast(eya_uchar_t, dst);

    // 1. Processing of small blocks
    if (n <= EYA_MEMORY_STD_SMALL_BLOCK_THRESHOLD)
    {
        const eya_u64_t fill64 = eya_type_cast(eya_u64_t, val * 0x0101010101010101ULL);
        while (n >= 8)
        {
            *(eya_u64_t *)d = fill64;
            d += 8;
            n -= 8;
        }
        if (n >= 4)
        {
            *(eya_u32_t *)d = eya_type_cast(eya_u32_t, fill64);
            d += 4;
            n -= 4;
        }
        if (n >= 2)
        {
            *(eya_u16_t *)d = eya_type_cast(eya_u16_t, fill64);
            d += 2;
            n -= 2;
        }
        if (n > 0)
        {
            *d++ = val;
        }
        return d;
    }

    // 2. Alignment of the target buffer
    eya_usize_t align = eya_ptr_align_mask(d, EYA_MEMORY_STD_PTR_ALIGNMENT);
    if (align != EYA_MEMORY_STD_PTR_ALIGNMENT)
    {
        eya_usize_t head = EYA_MEMORY_STD_PTR_ALIGNMENT - align;
        if (head > n)
        {
            head = n;
        }
        n -= head;
        while (head--)
        {
            *d++ = val;
        }
    }

    // 3. Streaming instructions for large blocks
    if (n >= EYA_MEMORY_STD_STREAM_THRESHOLD)
    {
        eya_usize_t     stream_blocks = n / EYA_MEMORY_STD_STREAM_ALIGNMENT;
        const eya_u64_t fill64        = eya_type_cast(eya_u64_t, val * 0x0101010101010101ULL);
        while (stream_blocks--)
        {
#if EYA_MEMORY_STD_SIMD_LEVEL >= 512
            __m512i fill = _mm512_set1_epi8(eya_type_cast(eya_uchar_t, val));
            _mm512_stream_si512((__m512i *)d, fill);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 256
            __m256i fill = _mm256_set1_epi8(eya_type_cast(eya_uchar_t, val));
            _mm256_stream_si256((__m256i *)(d + 0), fill);
            _mm256_stream_si256((__m256i *)(d + 32), fill);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 128
            __m128i fill = _mm_set1_epi8(eya_type_cast(eya_uchar_t, val));
            _mm_stream_si128((__m128i *)(d + 0), fill);
            _mm_stream_si128((__m128i *)(d + 16), fill);
            _mm_stream_si128((__m128i *)(d + 32), fill);
            _mm_stream_si128((__m128i *)(d + 48), fill);
#else
            // Fallback for non-SIMD: set in 64-bit chunks
            for (eya_usize_t i = 0; i < EYA_MEMORY_STD_STREAM_ALIGNMENT; i += 8)
            {
                *(eya_u64_t *)(d + i) = fill64;
            }
#endif
            d += EYA_MEMORY_STD_STREAM_ALIGNMENT;
            n -= EYA_MEMORY_STD_STREAM_ALIGNMENT;
        }
#if EYA_MEMORY_STD_SIMD_LEVEL > 0
        _mm_sfence();
#endif
    }

    // 4. SIMD optimization for medium blocks
    if (n >= EYA_MEMORY_STD_SIMD_BLOCK)
    {
        eya_usize_t     simd_blocks = n / EYA_MEMORY_STD_SIMD_BLOCK;
        const eya_u64_t fill64      = eya_type_cast(eya_u64_t, val * 0x0101010101010101ULL);
        while (simd_blocks--)
        {
#if EYA_MEMORY_STD_SIMD_LEVEL >= 512
            __m512i fill = _mm512_set1_epi8(eya_type_cast(eya_uchar_t, val));
            _mm512_storeu_si512((__m512i *)d, fill);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 256
            __m256i fill = _mm256_set1_epi8(eya_type_cast(eya_uchar_t, val));
            _mm256_storeu_si256((__m256i *)d, fill);
#elif EYA_MEMORY_STD_SIMD_LEVEL >= 128
            __m128i fill = _mm_set1_epi8(eya_type_cast(eya_uchar_t, val));
            _mm_storeu_si128((__m128i *)d, fill);
#else
            // Fallback for non-SIMD: set in 64-bit chunks
            for (eya_usize_t i = 0; i < EYA_MEMORY_STD_SIMD_BLOCK; i += 8)
            {
                *(eya_u64_t *)(d + i) = fill64;
            }
#endif
            d += EYA_MEMORY_STD_SIMD_BLOCK;
            n -= EYA_MEMORY_STD_SIMD_BLOCK;
        }
    }

    // 5. Residual processing
    const eya_u64_t fill64 = eya_type_cast(eya_u64_t, val * 0x0101010101010101ULL);
    while (n >= 8)
    {
        *(eya_u64_t *)d = fill64;
        d += 8;
        n -= 8;
    }
    if (n >= 4)
    {
        *(eya_u32_t *)d = eya_type_cast(eya_u32_t, fill64);
        d += 4;
        n -= 4;
    }
    if (n >= 2)
    {
        *(eya_u16_t *)d = eya_type_cast(eya_u16_t, fill64);
        d += 2;
        n -= 2;
    }
    if (n > 0)
    {
        *d++ = val;
    }

    return d;
}