#include "okke_compat.h"
#include "quantum.h"
#ifdef COMPAT_MODE
    inline void tap_code16(uint16_t code) { register_code16(code); unregister_code16(code); }
#endif