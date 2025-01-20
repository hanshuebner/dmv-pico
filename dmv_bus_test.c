#include <stdio.h>
#include <pico/stdio.h>
#include <pico/multicore.h>
#include <tusb.h>
#include "dmv_2651.h"
#include "dmv_bus.h"

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
    printf("Bus test ready\n");

    printf("Starting second processor\n");
    multicore_launch_core1(handle_dmv_bus_test);

    printf("Running\n");
    printf("mask is 0x%08x\n", dmv_bus_data_mask);
    uint8_t input = 0;
    for (;;) {
//        multicore_fifo_push_blocking(input++);
        uint32_t wrote = multicore_fifo_pop_blocking_inline();
        printf("Wrote 0x%08X\n", wrote);
    }
}
