#include <eya/addr.h>
#include <eya/static_assert.h>

eya_static_assert(sizeof(eya_uaddr_t) == sizeof(void *),
                  "eya_uaddr_t size must exactly match pointer size");

eya_static_assert(sizeof(eya_saddr_t) == sizeof(void *),
                  "eya_saddr_t size must exactly match pointer size");