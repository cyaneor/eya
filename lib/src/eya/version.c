#include <eya/version.h>
#include <eya/stringify.h>

const eya_char_t *
eya_version(void)
{
    return eya_stringify_va(EYA_VERSION_MAJOR.EYA_VERSION_MINOR.EYA_VERSION_PATCH);
}

eya_return_t
eya_version_major(void)
{
    return EYA_VERSION_MAJOR;
}

eya_return_t
eya_version_minor(void)
{
    return EYA_VERSION_MINOR;
}

eya_return_t
eya_version_patch(void)
{
    return EYA_VERSION_PATCH;
}