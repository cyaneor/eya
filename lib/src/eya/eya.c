#include <eya/eya.h>
#include <eya/version_initializer.h>

/**
 * @var eya_version_t m_version
 * @brief Global variable storing the EYA library version.
 *
 * This variable is initialized using the eya_version_initializer macro with the major,
 * minor, and patch version numbers defined in the EYA library.
 */
static eya_version_t m_version =
    eya_version_initializer(EYA_VERSION_MAJOR, EYA_VERSION_MINOR, EYA_VERSION_PATCH);

eya_version_t *
eya_version(void)
{
    return &m_version;
}