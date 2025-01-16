
#include <hardware/gpio.h>
#include <pico/multicore.h>

#include "dmv_bus.h"
#include "signetics_2651_uart.h"

static const int BITS_IN_USE = 17;

void
init_gpio() {
    for (int i = 0; i < BITS_IN_USE; i++) {
        gpio_set_function(i, GPIO_FUNC_NULL);
        gpio_disable_pulls(i);
        gpio_set_input_enabled(i, true);
    }
}

volatile ModeRegister1Union mode_register1;
volatile ModeRegister2Union mode_register2;
volatile CommandRegisterUnion command_register;
volatile StatusRegisterUnion status_register;
volatile uint8_t syn1 = 0;
volatile uint8_t syn2 = 0;
volatile uint8_t dle = 0;

void
handle_dmv_bus() {
    uint8_t write_syn_ptr = 0;
    uint8_t write_mode_ptr = 0;
    uint8_t read_syn_ptr = 0;

    status_register.raw = 0;
    status_register.reg.data_carrier_detect = 1;
    status_register.reg.data_set_ready = 1;

    init_gpio();
    DmvBusUnion state;
    DmvBusUnion old_state;
    old_state.raw = state.raw = gpio_get_all();

    // ReSharper disable once CppDFAEndlessLoop
    while (true) {
        do {
            state.raw = gpio_get_all();
        } while (state.reg.ifsel0_n || (state.reg.ior_n && state.reg.iow_n));

        // interface selected
        if (state.reg.ba < 4 && !state.reg.ior_n) {
            // read - switch data direction, present bits on GPIO
            gpio_set_dir_out_masked(dmv_bus_data_mask);

            switch (state.reg.ba) {
            case 0:
                // read data
                if (multicore_fifo_rvalid()) {
                    state.reg.d = multicore_fifo_pop_blocking_inline();
                }
                break;
            case 1:
                // read status
                status_register.reg.tx_ready = multicore_fifo_wready();
                status_register.reg.rx_ready = multicore_fifo_rvalid();
                status_register.reg.tx_empty = status_register.reg.tx_ready;
                state.reg.d = status_register.raw;
                break;
            case 2:
                // read mode register 1/2
                switch (read_syn_ptr++) {
                    case 0:
                        state.reg.d = mode_register1.raw;
                        break;
                    case 1:
                        state.reg.d = mode_register2.raw;
                        break;
                    default:
                }
                if (read_syn_ptr == 2) {
                    read_syn_ptr = 0;
                }
                break;
            case 3:
                // read command register
                state.reg.d = command_register.raw;
                read_syn_ptr = 0;
                write_mode_ptr = 0;
                write_syn_ptr = 0;
                break;
            default:
            }
            gpio_put_masked(dmv_bus_data_mask, state.raw);

            // wait until end of cycle
            do {
                state.raw = gpio_get_all();
            } while (!state.reg.ifsel0_n);

            // interface deselected, switch data bit direction back to input
            gpio_set_dir_in_masked(dmv_bus_data_mask);

        } else if (state.reg.ba >= 4 && !state.reg.iow_n) {
            switch (state.reg.ba) {
            case 4:
                /* write data */
                if (multicore_fifo_wready()) {
                    multicore_fifo_push_blocking(state.reg.d);
                } else {
                    status_register.reg.overrun_error = 1;
                }
                break;
            case 5:
                /* write SYN1/SYN2/DLE */
                switch (write_syn_ptr++) {
                    case 0:
                        syn1 = state.reg.d;
                        break;
                    case 1:
                        syn2 = state.reg.d;
                        break;
                    case 2:
                        dle = state.reg.d;
                        break;
                    default:
                }
                if (write_syn_ptr == 3) {
                    write_syn_ptr = 0;
                }
                break;
            case 6:
                /* write mode register 1/2 */
                switch (write_mode_ptr++) {
                    case 0:
                        mode_register1.raw = state.reg.d;
                        break;
                    case 1:
                        mode_register2.raw = state.reg.d;
                        break;
                    default:
                }
                if (write_mode_ptr == 2) {
                    write_mode_ptr = 0;
                }
                break;
            case 7:
                /* write command register */
                command_register.raw = state.reg.d;
                break;
            default:
            }

            do {
                state.raw = gpio_get_all();
            } while (state.reg.ifsel0_n == 0);
        }
    }
}
