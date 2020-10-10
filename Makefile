SRC = $(shell find keyboards -type f)

COPIED = $(addprefix ../qmk_firmware/,$(SRC))

DIRS = $(sort $(foreach file,$(COPIED),$(dir $(file))))

.PHONY: flash

arch_36_okke.hex: ../qmk_firmware/arch_36_okke.hex
	cp $< $@

../qmk_firmware/arch_36_okke.hex: $(COPIED)
	make -C ../qmk_firmware arch_36:okke

flash: $(COPIED)
	make -C ../qmk_firmware arch_36:okke:avrdude

flash-left: $(COPIED)
	make -C ../qmk_firmware arch_36:okke:avrdude-split-left

flash-right: $(COPIED)
	make -C ../qmk_firmware arch_36:okke:avrdude-split-right

$(DIRS):
	mkdir -p $@

define make-goal
../qmk_firmware/$1: $1 | ../qmk_firmware/$2
	cp $$< $$@
endef

$(foreach file,$(SRC),$(eval $(call make-goal,$(file),$(dir $(file)))))
