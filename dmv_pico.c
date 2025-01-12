#include <stdio.h>
#include <pico/stdio.h>
#include <pico/time.h>

int main(void)
{
    stdio_init_all();

    for (;;) {
        printf("Hello WORLD!\n");
        sleep_ms(500);
    }
    return 0;
}
