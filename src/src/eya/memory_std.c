#include <eya/memory_std.h>
#include <eya/runtime_error_code.h>
#include <eya/runtime_check_ref.h>
#include <eya/ptr_util.h>

#if defined(EYA_COMPILE_OPTION_SSE2) || defined(EYA_COMPILE_OPTION_AVX2) ||                        \
    defined(EYA_COMPILE_OPTION_AVX512)
#    include <immintrin.h> // Для AVX, AVX2, AVX-512 и SSE
#endif

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