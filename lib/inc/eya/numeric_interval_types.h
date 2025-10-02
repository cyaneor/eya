#ifndef EYA_NUMERIC_INTERVAL_TYPES_H
#define EYA_NUMERIC_INTERVAL_TYPES_H

#include <eya/interval_struct.h>
#include <eya/numeric_interval_bounds_types.h>

eya_interval_type(eya_uchar_interval_bounds, eya_uchar_interval);
eya_interval_type(eya_ushort_interval_bounds, eya_ushort_interval);
eya_interval_type(eya_uint_interval_bounds, eya_uint_interval);
eya_interval_type(eya_ulong_interval_bounds, eya_ulong_interval);
eya_interval_type(eya_ullong_interval_bounds, eya_ullong_interval);
eya_interval_type(eya_schar_interval_bounds, eya_schar_interval);
eya_interval_type(eya_sshort_interval_bounds, eya_sshort_interval);
eya_interval_type(eya_sint_interval_bounds, eya_sint_interval);
eya_interval_type(eya_slong_interval_bounds, eya_slong_interval);
eya_interval_type(eya_sllong_interval_bounds, eya_sllong_interval);

#endif // EYA_NUMERIC_INTERVAL_TYPES_H
