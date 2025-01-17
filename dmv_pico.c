#include <stdio.h>
#include <pico/stdio.h>
#include <pico/multicore.h>
#include <tusb.h>
#include "dmv_2651.h"
#include "dmv_bus.h"
#include "signetics_2651_debug.h"

// define a printer to print the DmvBus structure
void print_DmvBus(const DmvBusUnion *bus_union) {
    if (!bus_union) {
        printf("DmvBusUnion pointer is NULL\n");
        return;
    }
    const DmvBus* bus = &bus_union->reg;

    printf("DmvBus Structure (0x%08x):\n", bus_union->raw);
    printf("  IRQ: %u\n", bus->irq);
    printf("  Reset_n: %u\n", bus->reset_n);
    printf("  IOR_n: %u\n", bus->ior_n);
    printf("  IOW_n: %u\n", bus->iow_n);
    printf("  Data: 0x%02X\n", bus->d);
    printf("  Address: 0x%X\n", bus->ba);
    printf("  Interface Select 0: %u\n", bus->ifsel0_n);
    printf("  Interface Select 1: %u\n", bus->ifsel1_n);
}

int main(void)
{
    stdio_init_all();

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Ready\n");

    printf("Starting second processor\n");
    multicore_launch_core1(handle_dmv_bus);

    printf("Waiting for data\n");
    for (;;) {
        uint32_t data = multicore_fifo_pop_blocking();
        putchar(data & 0xff);
        //print_CommandRegister(command_register.reg);
        //print_ModeRegister1(mode_register1.reg);
        //print_ModeRegister2(mode_register2.reg);
        //print_StatusRegister(status_register.reg);
    }
}
