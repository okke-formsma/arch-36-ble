SRC += okke.c \
       okke_process_record.c \
	   okke_compat.c

# Virtual DIP switch configuration (+1000)
BOOTMAGIC_ENABLE = no

# Commands for debug and configuration
COMMAND_ENABLE = no

# Console for debug (+400)
CONSOLE_ENABLE = no
ifdef CONSOLE_ENABLE
  ifeq ($(strip $(KEYLOGGER_ENABLE)), yes)
    OPT_DEFS += -DKEYLOGGER_ENABLE
  endif
endif

# Audio control and System control (+450)
EXTRAKEY_ENABLE = yes

ifneq ($(strip $(DISABLE_LTO)), yes)
  LINK_TIME_OPTIMIZATION_ENABLE = yes
endif

ifeq ($(strip $(MAKE_BOOTLOADER)), yes)
  OPT_DEFS += -DMAKE_BOOTLOADER
endif

# Mouse keys (+4700)
MOUSEKEY_ENABLE = yes

# Nkey Rollover - if this doesn't work, see here:
# https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE ?= yes

# # Enable the OLED Driver (+5000)
# OLED_DRIVER_ENABLE ?= no
# ifneq ($(strip $(OLED_DRIVER_ENABLE)), no)
#   SRC += tynanbe_oled.c
# endif
 
SPACE_CADET_ENABLE = no

TAP_DANCE_ENABLE ?= no

UNICODE_ENABLE ?= no