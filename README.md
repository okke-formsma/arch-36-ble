# Okke's arch-36 keymap

## Building

The `Makefile` in this repository assumes that the following directories exist in the parent directory of this directory:

* `qmk-nrf52`: https://github.com/joric/qmk, brach `nrf52-jorne`
* `nRF5_SDK_15.0.0_a53641a`: The extracted nordic sdk from https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/.
* `uf2`: clone git@github.com:microsoft/uf2.git

The makefile will copy the source from this directory into the qmk-nrf52 tree and
build using the makefile there.

To build flash to your device run:

    make flash_master
    make flash_slave

To clean up all build files run:

    make clean
