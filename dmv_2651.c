
#include <hardware/gpio.h>
#include <pico/multicore.h>

#include "dmv_bus.h"
#include "signetics_2651_uart.h"

void
init_gpio() {
    for (int i = 0; i < 30; i++) {
        gpio_set_function(i, GPIO_FUNC_NULL);
        gpio_disable_pulls(i);
        gpio_set_input_enabled(i, true);
    }
}

void
handle_dmv_bus() {
    ModeRegister1Union mode_register1;
    ModeRegister2Union mode_register2;
    bool mode_register1_set = false;
    CommandRegisterUnion command_register;
    StatusRegisterUnion status_register;

    init_gpio();
    dmv_bus_t state = dmv_bus_get();
    // ReSharper disable once CppDFAEndlessLoop
    while (true) {
        do {
            state = dmv_bus_get();
        } while (state.ifsel0_n == 1 || (state.ior_n == 1 && state.iow_n == 1));

        // interface selected
        if (state.ba < 4) {
            // read - switch data direction, present bits on GPIO
            gpio_set_dir_out_masked(dmv_bus_data_mask);

            switch (state.ba) {
            case 0:
                // read data
            case 1:
                // read status
            case 2:
                // read mode register 1/2
            case 3:
                // read command register
            }

            // wait until end of cycle
            do {
                state = dmv_bus_get();
            } while (state.ifsel0_n == 0 && (state.ior_n == 0 || state.iow_n == 0));

            // interface deselected, switch data bit direction back to input
            gpio_set_dir_in_masked(dmv_bus_data_mask);

        } else {
            // write - wait until rising edge of write pulse before processing the data
            do {
                state = dmv_bus_get();
            } while (state.ifsel0_n == 0 && (state.ior_n == 0 || state.iow_n == 0));

            switch (state.ba) {
            case 4:
                // write data
                if (multicore_fifo_wready()) {
                    multicore_fifo_push_blocking(state.d);
                } else {
                    // 
                    status_register.reg.overrun_error = 1;
                }
                break;
            case 5:
                // write SYN1/SYN2/DLE (not implemented)
                break;
            case 6:
                // write mode register 1/2
                if (mode_register1_set) {
                    mode_register2.raw = state.d;
                    mode_register1_set = false;
                } else {
                    mode_register1.raw = state.d;
                    mode_register1_set = true;
                }
                break;
            case 7:
                // write command register
                command_register.raw = state.d;
                break;
            }
        }

    }
}
