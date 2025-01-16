#ifndef DMV_BUS_H
#define DMV_BUS_H

#include <stdint.h>
#include <hardware/gpio.h>

// GPIO Port Bitfield Mapping for Raspberry Pi Pico
// This structure assumes a 32-bit GPIO register
// Adjust the bit positions as needed for your specific use case

typedef struct {
    uint32_t irq : 1;      // Interrupt Request
    uint32_t reset_n : 1;  // Reset (negative logic)
    uint32_t ior_n : 1;    // I/O Read (negative logic)
    uint32_t iow_n : 1;    // I/O Write (negative logic)
    uint32_t d : 8;        // Data bits (d0 to d7)
    uint32_t ba : 3;       // Address bits (ba2 to ba0)
    uint32_t ifsel0_n : 1; // Interface Select 0 (negative logic)
    uint32_t ifsel1_n : 1; // Interface Select 1 (negative logic)
    uint32_t reserved : 15; // Reserved bits (to pad to 32 bits)
} DmvBus;

typedef union {
    uint32_t raw;
    DmvBus reg;
} DmvBusUnion;

static const uint32_t dmv_bus_data_mask = 0x00000ff0;

#endif // DMV_BUS_H