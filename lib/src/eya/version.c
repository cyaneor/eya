#include <eya/version.h>
#include <eya/runtime_check_ref.h>

eya_ushort_t
eya_version_major(const eya_version_t *self)
{
    eya_runtime_check_ref(self);
    return self->major;
}

eya_uchar_t
eya_version_minor(const eya_version_t *self)
{
    eya_runtime_check_ref(self);
    return self->minor;
}

eya_uchar_t
eya_version_patch(const eya_version_t *self)
{
    eya_runtime_check_ref(self);
    return self->patch;
}