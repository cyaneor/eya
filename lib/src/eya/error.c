#include <eya/error.h>

#include <eya/nullptr.h>
#include <eya/runtime_check.h>
#include <eya/error_initializer.h>
#include <eya/runtime_error_code.h>

void
eya_error_unpack(const eya_error_t *self, eya_error_code_t *code, const char **desc)
{
    eya_runtime_check(self, EYA_RUNTIME_ERROR_NULL_POINTER);

    if (code)
    {
        *code = self->code;
    }

    if (desc)
    {
        *desc = self->desc;
    }
}

eya_error_code_t
eya_error_get_code(const eya_error_t *self)
{
    eya_error_code_t code;
    eya_error_unpack(self, &code, nullptr);
    return code;
}

const char *
eya_error_get_desc(const eya_error_t *self)
{
    const char *desc;
    eya_error_unpack(self, nullptr, &desc);
    return desc;
}

void
eya_error_set(eya_error_t *self, eya_error_code_t code, const char *desc)
{
    eya_runtime_check(self, EYA_RUNTIME_ERROR_NULL_POINTER);
    self->desc = desc;
    self->code = code;
}

void
eya_error_set_code(eya_error_t *self, eya_error_code_t code)
{
    eya_error_set(self, code, nullptr);
}

void
eya_error_assign(eya_error_t *self, const eya_error_t *other)
{
    eya_error_code_t code;
    const char      *desc;

    eya_error_unpack(other, &code, &desc);
    eya_error_set(self, code, desc);
}

void
eya_error_clear(eya_error_t *self)
{
    eya_error_t _t = eya_error_empty_initializer();
    eya_error_assign(self, &_t);
}

eya_error_code_t
eya_error_get_code_and_clear(eya_error_t *self)
{
    eya_error_code_t code = eya_error_get_code(self);
    eya_error_clear(self);
    return code;
}

bool
eya_error_is_equal_code_to(const eya_error_t *self, eya_error_code_t code)
{
    return eya_error_get_code(self) == code;
}

bool
eya_error_is_equal_code(const eya_error_t *self, const eya_error_t *other)
{
    const eya_error_code_t code = eya_error_get_code(other);
    return eya_error_is_equal_code_to(self, code);
}

bool
eya_error_is_equal_desc_to(const eya_error_t *self, const char *desc)
{
    return eya_error_get_desc(self) == desc;
}

bool
eya_error_is_equal_desc(const eya_error_t *self, const eya_error_t *other)
{
    const char *desc = eya_error_get_desc(other);
    return eya_error_is_equal_desc_to(self, desc);
}

bool
eya_error_is_equal(const eya_error_t *self, const eya_error_t *other)
{
    return eya_error_is_equal_code(self, other) && eya_error_is_equal_desc(self, other);
}

bool
eya_error_is_ok(const eya_error_t *self)
{
    return eya_error_is_equal_code_to(self, EYA_ERROR_CODE_NONE);
}