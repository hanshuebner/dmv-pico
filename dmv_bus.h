#ifndef DMV_BUS_H
#define DMV_BUS_H

#include <stdint.h>
#include <hardware/gpio.h>

// GPIO Port Bitfield Mapping for Raspberry Pi Pico
// This structure assumes a 32-bit GPIO register
// Adjust the bit positions as needed for your specific use case

#pragma pack(1)
typedef struct {
    unsigned int irq : 1;      // Interrupt Request
    unsigned int reset_n : 1;  // Reset (negative logic)
    unsigned int ior_n : 1;    // I/O Read (negative logic)
    unsigned int iow_n : 1;    // I/O Write (negative logic)
    unsigned int d : 8;        // Data bits (d0 to d7)
    unsigned int ba : 3;       // Address bits (ba2 to ba0)
    unsigned int ifsel0_n : 1; // Interface Select 0 (negative logic)
    unsigned int ifsel1_n : 1; // Interface Select 1 (negative logic)
} DmvBus;
#pragma pack()

typedef union {
    uint32_t raw;
    DmvBus reg;
} DmvBusUnion;

static const uint32_t dmv_bus_data_mask = 0x00000ff0;

#endif // DMV_BUS_H