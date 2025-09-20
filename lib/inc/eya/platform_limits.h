#ifndef EYA_PLATFORM_LIMITS_H
#define EYA_PLATFORM_LIMITS_H

#include <limits.h>

#ifndef EYA_CHAR_BIT
#    ifdef CHAR_BIT
#        define EYA_CHAR_BIT CHAR_BIT
#    else
#        error "CHAR_BIT not defined"
#    endif // CHAR_BIT
#endif     // EYA_CHAR_BIT

#endif // EYA_PLATFORM_LIMITS_H
