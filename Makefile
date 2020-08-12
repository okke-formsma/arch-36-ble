KEYBOARD = arch_36_ble
KEYMAP = okke

NRFSDK15_ROOT=/home/okke/dev/nRF5_SDK_15.0.0_a53641a
QMK_ROOT=../qmk-nrf52

SRC = $(shell find keyboards users -type f)
COPIED = $(addprefix ${QMK_ROOT}/,$(SRC))
DIRS = $(sort $(foreach file,$(COPIED),$(dir $(file))))

.PHONY: ALL
ALL: master.dfu slave.dfu
slave: slave.dfu
master: master.dfu

.PHONY: flash_master flash_slave
flash_master: master.dfu
	printf "Put device in dfu mode"
	while [ ! -f /media/${USER}/NRF52BOOT/current.uf2 ]; do sleep 1; printf "."; done; printf "\n"
	cp master.dfu /media/${USER}/NRF52BOOT/
flash_slave: slave.dfu
	printf "Put device in dfu mode"
	while [ ! -f /media/${USER}/NRF52BOOT/current.uf2 ]; do sleep 1; printf "."; done; printf "\n"
	cp slave.dfu /media/${USER}/NRF52BOOT/

master.dfu: ${QMK_ROOT}/.build/${KEYBOARD}_master_${KEYMAP}.hex
	python ../uf2/utils/uf2conv.py $< -c -f 0xADA52840 -o $@

slave.dfu: ${QMK_ROOT}/.build/${KEYBOARD}_slave_${KEYMAP}.hex
	python ../uf2/utils/uf2conv.py $< -c -f 0xADA52840 -o $@

${QMK_ROOT}/.build/${KEYBOARD}_master_${KEYMAP}.hex: $(COPIED)
	export NRFSDK15_ROOT=${NRFSDK15_ROOT} && make -C ${QMK_ROOT} ${KEYBOARD}/master:${KEYMAP}

${QMK_ROOT}/.build/${KEYBOARD}_slave_${KEYMAP}.hex: $(COPIED)
	export NRFSDK15_ROOT=${NRFSDK15_ROOT} && make -C ${QMK_ROOT} ${KEYBOARD}/slave:${KEYMAP}

.PHONY: clean
clean:
	rm -rf ${QMK_ROOT}/keyboard/${keyboard} || true
	rm -rf ${QMK_ROOT}/.build/ || true
	rm master.dfu || true
	rm slave.dfu || true


# this part copies all changed files into the qmk dir
$(DIRS):
	mkdir -p $@

define make-goal
${QMK_ROOT}/$1: $1 | ${QMK_ROOT}/$2
	cp $$< $$@
endef

$(foreach file,$(SRC),$(eval $(call make-goal,$(file),$(dir $(file)))))
