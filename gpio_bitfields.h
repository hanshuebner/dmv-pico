#ifndef GPIO_BITFIELDS_H
#define GPIO_BITFIELDS_H

#include <stdint.h>

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
} gpio_port_t;

// Function to set the GPIO port
void set_gpio_port(volatile gpio_port_t *port, uint32_t value);

// Function to get the GPIO port value
uint32_t get_gpio_port(volatile gpio_port_t *port);

#endif // GPIO_BITFIELDS_H
