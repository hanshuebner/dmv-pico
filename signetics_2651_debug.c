#include <stdio.h>
#include "signetics_2651_uart.h"

const char* MR10_Mode_to_string(MR10_Mode mode) {
    switch (mode) {
        case MR10_SYNCHRONOUS_1X_RATE: return "SYNCHRONOUS_1X";
        case MR10_ASYNCHRONOUS_1X_RATE: return "ASYNCHRONOUS_1X";
        case MR10_ASYNCHRONOUS_16X_RATE: return "ASYNCHRONOUS_16X";
        case MR10_ASYNCHRONOUS_64X_RATE: return "ASYNCHRONOUS_64X";
        default: return "UNKNOWN";
    }
}

const char* MR12_CharacterLength_to_string(MR12_CharacterLength length) {
    switch (length) {
        case MR12_5_BITS: return "5";
        case MR12_6_BITS: return "6";
        case MR12_7_BITS: return "7";
        case MR12_8_BITS: return "8";
        default: return "UNKNOWN";
    }
}

const char* MR14_ParityControl_to_string(MR14_ParityControl control) {
    return control == MR14_PARITY_DISABLED ? "DISABLED" : "ENABLED";
}

const char* MR15_ParityType_to_string(MR15_ParityType type) {
    return type == MR15_PARITY_ODD ? "ODD" : "EVEN";
}

const char* MR17_StopBitLength_to_string(MR17_StopBitLength length) {
    switch (length) {
        case MR17_INVALID: return "INVALID";
        case MR17_1_STOP_BIT: return "1";
        case MR17_1_5_STOP_BITS: return "1.5";
        case MR17_2_STOP_BITS: return "2";
        default: return "UNKNOWN";
    }
}

void print_ModeRegister1(ModeRegister1 reg) {
    printf("ModeRegister1:\n");
    printf("  mode: %s\n", MR10_Mode_to_string(reg.mode));
    printf("  char_length: %s\n", MR12_CharacterLength_to_string(reg.char_length));
    printf("  parity_control: %s\n", MR14_ParityControl_to_string(reg.parity_control));
    printf("  parity_type: %s\n", MR15_ParityType_to_string(reg.parity_type));
    printf("  stop_bit_length: %s\n", MR17_StopBitLength_to_string(reg.stop_bit_length));
}

const char* MR20_BaudRate_to_string(MR20_BaudRate rate) {
    switch (rate) {
        case MR20_BAUD_50: return "50";
        case MR20_BAUD_75: return "75";
        case MR20_BAUD_110: return "110";
        case MR20_BAUD_134_5: return "134_5";
        case MR20_BAUD_150: return "150";
        case MR20_BAUD_300: return "300";
        case MR20_BAUD_600: return "600";
        case MR20_BAUD_1200: return "1200";
        case MR20_BAUD_1800: return "1800";
        case MR20_BAUD_2000: return "2000";
        case MR20_BAUD_2400: return "2400";
        case MR20_BAUD_3600: return "3600";
        case MR20_BAUD_4800: return "4800";
        case MR20_BAUD_7200: return "7200";
        case MR20_BAUD_9600: return "9600";
        case MR20_BAUD_19200: return "19200";
        default: return "UNKNOWN";
    }
}
const char* MR24_ReceiverClock_to_string(MR24_ReceiverClock clock) {
    return clock == MR24_RECEIVER_EXTERNAL ? "RECEIVER_EXTERNAL" : "RECEIVER_INTERNAL";
}

const char* MR25_TransmitterClock_to_string(MR25_TransmitterClock clock) {
    return clock == MR25_TRANSMITTER_EXTERNAL ? "TRANSMITTER_EXTERNAL" : "TRANSMITTER_INTERNAL";
}

void print_ModeRegister2(ModeRegister2 reg) {
    printf("ModeRegister2:\n");
    printf("  transmitter_clock: %s\n", MR25_TransmitterClock_to_string(reg.transmitter_clock));
    printf("  receiver_clock: %s\n", MR24_ReceiverClock_to_string(reg.receiver_clock));
    printf("  baud_rate: %s\n", MR20_BaudRate_to_string(reg.baud_rate));
}

const char* CR7_OperatingMode_to_string(CR7_OperatingMode mode) {
    switch (mode) {
        case CR7_NORMAL_OPERATION: return "NORMAL_OPERATION";
        case CR7_ASYNCHRONOUS_ECHO_MODE: return "ASYNCHRONOUS_ECHO_MODE";
        case CR7_LOCAL_LOOPBACK: return "LOCAL_LOOPBACK";
        case CR7_REMOTE_LOOPBACK: return "REMOTE_LOOPBACK";
        default: return "UNKNOWN";
    }
}

const char* CR5_RequestToSend_to_string(CR5_RequestToSend rts) {
    return rts == CR5_RTS_HIGH ? "RTS_HIGH" : "RTS_LOW";
}

const char* CR4_ResetError_to_string(CR4_ResetError reset) {
    return reset == CR4_NORMAL ? "NORMAL" : "RESET";
}

void print_CommandRegister(CommandRegister reg) {
    printf("CommandRegister:\n");
    printf("  tx_enable: %u\n", reg.tx_enable);
    printf("  dtr_control: %u\n", reg.dtr_control);
    printf("  rx_enable: %u\n", reg.rx_enable);
    printf("  force_break: %u\n", reg.force_break);
    printf("  reset_error: %s\n", CR4_ResetError_to_string(reg.reset_error));
    printf("  request_to_send: %s\n", CR5_RequestToSend_to_string(reg.request_to_send));
    printf("  operating_mode: %s\n", CR7_OperatingMode_to_string(reg.operating_mode));
}

void print_StatusRegister(StatusRegister reg) {
    printf("StatusRegister:\n");
    printf("  tx_ready: %u\n", reg.tx_ready);
    printf("  rx_ready: %u\n", reg.rx_ready);
    printf("  tx_empty: %u\n", reg.tx_empty);
    printf("  parity_error: %u\n", reg.parity_error);
    printf("  overrun_error: %u\n", reg.overrun_error);
    printf("  framing_error: %u\n", reg.framing_error);
    printf("  data_carrier_detect: %u\n", reg.data_carrier_detect);
    printf("  data_set_ready: %u\n", reg.data_set_ready);
}