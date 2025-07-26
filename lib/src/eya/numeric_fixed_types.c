#include <eya/numeric_fixed_types.h>
#include <eya/static_assert.h>
#include <eya/type_util.h>

eya_static_assert(eya_type_size(eya_u8_t) == 1, "Size mismatch");
eya_static_assert(eya_type_size(eya_u16_t) == 2, "Size mismatch");
eya_static_assert(eya_type_size(eya_u32_t) == 4, "Size mismatch");
eya_static_assert(eya_type_size(eya_u64_t) == 8, "Size mismatch");

eya_static_assert(eya_type_size(eya_s8_t) == 1, "Size mismatch");
eya_static_assert(eya_type_size(eya_s16_t) == 2, "Size mismatch");
eya_static_assert(eya_type_size(eya_s32_t) == 4, "Size mismatch");
eya_static_assert(eya_type_size(eya_s64_t) == 8, "Size mismatch");