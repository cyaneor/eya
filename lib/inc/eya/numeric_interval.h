/**
 * @file numeric_interval.h
 * @brief Defines global interval constants for various numeric types.
 *
 * This header provides constant interval objects for both unsigned and signed
 * integer types, initialized with their respective minimum and maximum bounds.
 * Each interval is defined as a closed interval, encompassing all possible values
 * for the corresponding numeric type.
 *
 * The intervals are initialized using the corresponding bounds initializers
 * from @ref numeric_interval_bounds_initializer.h and use the types defined
 * in @ref numeric_interval_types.h.
 *
 * @see numeric_interval_types.h
 * @see numeric_interval_bounds_initializer.h
 */

#ifndef EYA_NUMERIC_INTERVAL_H
#define EYA_NUMERIC_INTERVAL_H

#include <eya/numeric_interval_bounds_initializer.h>
#include <eya/numeric_interval_types.h>

EYA_COMPILER(EXTERN_C_BEGIN)

/**
 * @var EYA_UCHAR_T_INTERVAL
 * @brief Constant interval for the `eya_uchar_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_uchar_t` type,
 * initialized with `eya_uchar_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_uchar_interval_t EYA_UCHAR_T_INTERVAL = {eya_uchar_interval_bounds_initializer};

/**
 * @var EYA_USHORT_T_INTERVAL
 * @brief Constant interval for the `eya_ushort_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_ushort_t` type,
 * initialized with `eya_ushort_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_ushort_interval_t EYA_USHORT_T_INTERVAL = {eya_ushort_interval_bounds_initializer};

/**
 * @var EYA_UINT_T_INTERVAL
 * @brief Constant interval for the `eya_uint_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_uint_t` type,
 * initialized with `eya_uint_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_uint_interval_t EYA_UINT_T_INTERVAL = {eya_uint_interval_bounds_initializer};

/**
 * @var EYA_ULONG_T_INTERVAL
 * @brief Constant interval for the `eya_ulong_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_ulong_t` type,
 * initialized with `eya_ulong_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_ulong_interval_t EYA_ULONG_T_INTERVAL = {eya_ulong_interval_bounds_initializer};

/**
 * @var EYA_ULLONG_T_INTERVAL
 * @brief Constant interval for the `eya_ullong_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_ullong_t` type,
 * initialized with `eya_ullong_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_ullong_interval_t EYA_ULLONG_T_INTERVAL = {eya_ullong_interval_bounds_initializer};

/**
 * @var EYA_SCHAR_T_INTERVAL
 * @brief Constant interval for the `eya_schar_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_schar_t` type,
 * initialized with `eya_schar_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_schar_interval_t EYA_SCHAR_T_INTERVAL = {eya_schar_interval_bounds_initializer};

/**
 * @var EYA_SSHORT_T_INTERVAL
 * @brief Constant interval for the `eya_sshort_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_sshort_t` type,
 * initialized with `eya_sshort_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_sshort_interval_t EYA_SSHORT_T_INTERVAL = {eya_sshort_interval_bounds_initializer};

/**
 * @var EYA_SINT_T_INTERVAL
 * @brief Constant interval for the `eya_sint_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_sint_t` type,
 * initialized with `eya_sint_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_sint_interval_t EYA_SINT_T_INTERVAL = {eya_sint_interval_bounds_initializer};

/**
 * @var EYA_SLONG_T_INTERVAL
 * @brief Constant interval for the `eya_slong_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_slong_t` type,
 * initialized with `eya_slong_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_slong_interval_t EYA_SLONG_T_INTERVAL = {eya_slong_interval_bounds_initializer};

/**
 * @var EYA_SLLONG_T_INTERVAL
 * @brief Constant interval for the `eya_sllong_t` type.
 *
 * Represents a closed interval containing all possible values of the `eya_sllong_t` type,
 * initialized with `eya_sllong_interval_bounds_initializer` and marked as closed with
 * `EYA_INTERVAL_FLAGS_CLOSED`.
 */
static const eya_sllong_interval_t EYA_SLLONG_T_INTERVAL = {eya_sllong_interval_bounds_initializer};

EYA_COMPILER(EXTERN_C_END)

#endif // EYA_NUMERIC_INTERVAL_H