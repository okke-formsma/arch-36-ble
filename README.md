# Okke's arch-36 keymap

## Building

The `Makefile` in this repository assumes that
https://github.com/joric/qmk is cloned into same parent directory as
this one and is named `qmk-nrf52`. The `nrf52-jorne` branch should be checked out.

* All prerequisites for QMK are required. 
* The nordic sdk should be downloaded from https://developer.nordicsemi.com/nRF5_SDK/nRF5_SDK_v15.x.x/ and extracted to the same parent directory as this one and is named `nRF5_SDK_15.0.0_a53641a`.
* The git@github.com:microsoft/uf2.git repository should be cloned into the same parent 
directory as this one and is named `uf2`.

It will copy the source from this directory into the qmk-nrf52 tree and
build using the makefile there.

To build the hex file run:

    make

To build and flash the keyboard run:

    make flash

