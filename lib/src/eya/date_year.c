#include <eya/date_year.h>

#include <eya/date_util.h>
#include <eya/runtime_check.h>
#include <eya/runtime_error_code.h>

bool
eya_date_year_is_valid(eya_date_year_t self)
{
    return eya_date_is_valid_year(EYA_DATE_YEAR_T_MIN, EYA_DATE_YEAR_T_MAX, self);
}

bool
eya_date_year_is_leap(eya_date_year_t self)
{
    eya_runtime_check(eya_date_year_is_valid(self), EYA_RUNTIME_ERROR_OUT_OF_RANGE);
    return eya_date_is_leap_year(self);
}