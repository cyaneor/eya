#include <eya/allocated_array.h>

#include <eya/runtime_error_code.h>
#include <eya/runtime_check.h>
#include <eya/memory_typed.h>
#include <eya/ptr_util.h>

eya_usize_t
eya_allocated_array_get_size(const eya_allocated_array_t *self)
{
    return eya_memory_range_is_uninit(eya_ptr_ccast(eya_memory_range_t, self))
               ? 0
               : eya_memory_typed_get_size(eya_ptr_cast(eya_memory_typed_t, self));
}

void
eya_allocated_array_exchange(eya_allocated_array_t *self, eya_allocated_array_t *other)
{
    eya_runtime_check(
        eya_memory_typed_is_equal_element_size(eya_ptr_cast(eya_memory_typed_t, self),
                                               eya_ptr_cast(eya_memory_typed_t, other)),
        EYA_RUNTIME_ERROR_DIFFERENT_ELEMENT_SIZE);

    eya_allocated_range_exchange(eya_ptr_cast(eya_allocated_range_t, self),
                                 eya_ptr_cast(eya_allocated_range_t, other));
}

eya_usize_t
eya_allocated_array_get_max_size(const eya_allocated_array_t *self)
{
    const eya_usize_t element_size =
        eya_memory_typed_get_element_size(eya_ptr_ccast(eya_memory_typed_t, self));

    eya_runtime_check(element_size, EYA_RUNTIME_ERROR_ZERO_ELEMENT_SIZE);
    return EYA_USIZE_T_MAX / element_size;
}

bool
eya_allocated_array_is_max_size_exceeds(const eya_allocated_array_t *self, eya_usize_t size)
{
    const eya_usize_t max_size = eya_allocated_array_get_max_size(self);
    return size > max_size;
}

void
eya_allocated_array_resize(eya_allocated_array_t *self, eya_usize_t size)
{
    eya_runtime_check_if(eya_allocated_array_is_max_size_exceeds(self, size),
                         EYA_RUNTIME_ERROR_EXCEEDS_MAX_SIZE);

    const eya_usize_t element_size =
        eya_memory_typed_get_element_size(eya_ptr_cast(eya_memory_typed_t, self));

    const eya_usize_t size_in_bytes = size * element_size;
    eya_allocated_range_resize(eya_ptr_cast(eya_allocated_range_t, self), size_in_bytes);
}