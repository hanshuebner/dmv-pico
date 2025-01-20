#ifndef DMV_2651_H
#define DMV_2651_H

#include "signetics_2651_uart.h"

extern volatile ModeRegister1Union mode_register1;
extern volatile ModeRegister2Union mode_register2;
extern volatile CommandRegisterUnion command_register;
extern volatile StatusRegisterUnion status_register;

void handle_dmv_bus();
void handle_dmv_bus_test();

#endif // DMV_2651_H