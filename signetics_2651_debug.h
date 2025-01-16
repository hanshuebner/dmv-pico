#ifndef SIGNETICS_2651_DEBUG_H
#define SIGNETICS_2651_DEBUG_H

#include "signetics_2651_uart.h"

const char* MR10_Mode_to_string(MR10_Mode mode);
const char* MR12_CharacterLength_to_string(MR12_CharacterLength length);
const char* MR14_ParityControl_to_string(MR14_ParityControl control);
const char* MR15_ParityType_to_string(MR15_ParityType type);
const char* MR17_StopBitLength_to_string(MR17_StopBitLength length);
void print_ModeRegister1(ModeRegister1 reg);

const char* MR20_BaudRate_to_string(MR20_BaudRate rate);
const char* MR24_ReceiverClock_to_string(MR24_ReceiverClock clock);
const char* MR25_TransmitterClock_to_string(MR25_TransmitterClock clock);
void print_ModeRegister2(ModeRegister2 reg);

const char* CR7_OperatingMode_to_string(CR7_OperatingMode mode);
const char* CR5_RequestToSend_to_string(CR5_RequestToSend rts);
const char* CR4_ResetError_to_string(CR4_ResetError reset);
void print_CommandRegister(CommandRegister reg);

void print_StatusRegister(StatusRegister reg);

#endif // SIGNETICS_2651_DEBUG_H