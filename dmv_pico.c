#include <stdio.h>
#include <pico/stdio.h>
#include <pico/time.h>
#include <pico/multicore.h>

extern void handle_dmv_bus(void);

int main(void)
{
    stdio_init_all();

    multicore_launch_core1(handle_dmv_bus);

    for (;;) {
        printf("Hello WORLD!\n");
        sleep_ms(500);
    }
    return 0;
}
