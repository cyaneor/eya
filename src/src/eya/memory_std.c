#include <eya/memory_std.h>
#include <eya/runtime_error_code.h>
#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

#if defined(EYA_COMPILE_OPTION_SSE2) || defined(EYA_COMPILE_OPTION_AVX2) ||                        \
    defined(EYA_COMPILE_OPTION_AVX512)
#    include <immintrin.h> // Для AVX, AVX2, AVX-512 и SSE
#endif

void *
eya_memory_std_copy(void *restrict dst, const void *restrict src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_char_t       *d = (eya_char_t *)dst;
    const eya_char_t *s = (const eya_char_t *)src;

#if defined(EYA_COMPILE_OPTION_AVX512) && defined(__AVX512F__)
    while (n >= 64)
    {
        __m512i chunk = _mm512_loadu_si512((const __m512i *)s);
        _mm512_storeu_si512((__m512i *)d, chunk);
        s += 64;
        d += 64;
        n -= 64;
    }
#elif defined(EYA_COMPILE_OPTION_AVX2) && defined(__AVX2__)
    while (n >= 32)
    {
        __m256i chunk = _mm256_loadu_si256((const __m256i *)s);
        _mm256_storeu_si256((__m256i *)d, chunk);
        s += 32;
        d += 32;
        n -= 32;
    }
#elif defined(EYA_COMPILE_OPTION_SSE2) && defined(__SSE2__)
    while (n >= 16)
    {
        __m128i chunk = _mm_loadu_si128((const __m128i *)s);
        _mm_storeu_si128((__m128i *)d, chunk);
        s += 16;
        d += 16;
        n -= 16;
    }
#endif

    while (n--)
    {
        *d++ = *s++;
    }

    return d;
}

void *
eya_memory_std_rcopy(void *restrict dst, const void *restrict src, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_runtime_check_ref(src);

    eya_char_t       *d = eya_ptr_add_offset_unsafe(eya_char_t, dst, n);
    const eya_char_t *s = eya_ptr_add_offset_unsafe(const eya_char_t, src, n);

#if defined(EYA_COMPILE_OPTION_AVX512) && defined(__AVX512F__)
    while (n >= 64)
    {
        d -= 64;
        s -= 64;
        __m512i chunk = _mm512_loadu_si512((const __m512i *)s);
        _mm512_storeu_si512((__m512i *)d, chunk);
        n -= 64;
    }
#elif defined(EYA_COMPILE_OPTION_AVX2) && defined(__AVX2__)
    while (n >= 32)
    {
        d -= 32;
        s -= 32;
        __m256i chunk = _mm256_loadu_si256((const __m256i *)s);
        _mm256_storeu_si256((__m256i *)d, chunk);
        n -= 32;
    }
#elif defined(EYA_COMPILE_OPTION_SSE2) && defined(__SSE2__)
    while (n >= 16)
    {
        d -= 16;
        s -= 16;
        __m128i chunk = _mm_loadu_si128((const __m128i *)s);
        _mm_storeu_si128((__m128i *)d, chunk);
        n -= 16;
    }
#endif

    while (n--)
    {
        *(--d) = *(--s);
    }

    return d;
}

void *
eya_memory_std_set(void *dst, eya_char_t val, eya_usize_t n)
{
    eya_runtime_check_ref(dst);
    eya_char_t *d = (eya_char_t *)dst;

#if defined(EYA_COMPILE_OPTION_AVX512) && defined(__AVX512F__)
    __m512i fill = _mm512_set1_epi8(val);
    while (n >= 64)
    {
        _mm512_storeu_si512((__m512i *)d, fill);
        d += 64;
        n -= 64;
    }
#elif defined(EYA_COMPILE_OPTION_AVX2) && defined(__AVX2__)
    __m256i fill = _mm256_set1_epi8(val);
    while (n >= 32)
    {
        _mm256_storeu_si256((__m256i *)d, fill);
        d += 32;
        n -= 32;
    }
#elif defined(EYA_COMPILE_OPTION_SSE2) && defined(__SSE2__)
    __m128i fill = _mm_set1_epi8(val);
    while (n >= 16)
    {
        _mm_storeu_si128((__m128i *)d, fill);
        d += 16;
        n -= 16;
    }
#endif

    while (n--)
    {
        *d++ = val;
    }
    return d;
}