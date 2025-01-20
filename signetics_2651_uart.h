#ifndef SIGNETICS_2651_UART_H
#define SIGNETICS_2651_UART_H

#pragma pack(1)

#include <stdint.h>

// Mode Register 1 (MR1) Definitions
typedef enum {
    MR10_SYNCHRONOUS_1X_RATE = 0b00,
    MR10_ASYNCHRONOUS_1X_RATE = 0b01,
    MR10_ASYNCHRONOUS_16X_RATE = 0b10,
    MR10_ASYNCHRONOUS_64X_RATE = 0b11
} MR10_Mode;

typedef enum {
    MR12_5_BITS = 0b00,
    MR12_6_BITS = 0b01,
    MR12_7_BITS = 0b10,
    MR12_8_BITS = 0b11
} MR12_CharacterLength;

typedef enum {
    MR14_PARITY_DISABLED = 0,
    MR14_PARITY_ENABLED = 1
} MR14_ParityControl;

typedef enum {
    MR15_PARITY_ODD = 0,
    MR15_PARITY_EVEN = 1
} MR15_ParityType;

typedef enum {
    MR17_INVALID = 0b00,
    MR17_1_STOP_BIT = 0b01,
    MR17_1_5_STOP_BITS = 0b10,
    MR17_2_STOP_BITS = 0b11
} MR17_StopBitLength;

typedef struct {
    MR10_Mode mode : 2;
    MR12_CharacterLength char_length : 2;
    MR14_ParityControl parity_control : 1;
    MR15_ParityType parity_type : 1;
    uint8_t reserved : 2;
    MR17_StopBitLength stop_bit_length : 2;
} ModeRegister1;

typedef union {
    uint8_t raw;
    ModeRegister1 reg;
} ModeRegister1Union;

// Mode Register 2 (MR2) Definitions
typedef enum {
    MR20_BAUD_50 = 0b0000,
    MR20_BAUD_75 = 0b0001,
    MR20_BAUD_110 = 0b0010,
    MR20_BAUD_134_5 = 0b0011,
    MR20_BAUD_150 = 0b0100,
    MR20_BAUD_300 = 0b0101,
    MR20_BAUD_600 = 0b0110,
    MR20_BAUD_1200 = 0b0111,
    MR20_BAUD_1800 = 0b1000,
    MR20_BAUD_2000 = 0b1001,
    MR20_BAUD_2400 = 0b1010,
    MR20_BAUD_3600 = 0b1011,
    MR20_BAUD_4800 = 0b1100,
    MR20_BAUD_7200 = 0b1101,
    MR20_BAUD_9600 = 0b1110,
    MR20_BAUD_19200 = 0b1111
} MR20_BaudRate;

typedef enum {
    MR24_RECEIVER_EXTERNAL = 0,
    MR24_RECEIVER_INTERNAL = 1
} MR24_ReceiverClock;

typedef enum {
    MR25_TRANSMITTER_EXTERNAL = 0,
    MR25_TRANSMITTER_INTERNAL = 1
} MR25_TransmitterClock;

typedef struct {
    MR25_TransmitterClock transmitter_clock : 1;
    MR24_ReceiverClock receiver_clock : 1;
    MR20_BaudRate baud_rate : 4;
    uint8_t reserved : 2;
} ModeRegister2;

typedef union {
    uint8_t raw;
    ModeRegister2 reg;
} ModeRegister2Union;

// Command Register (CR) Definitions
typedef enum {
    CR7_NORMAL_OPERATION = 0b00,
    CR7_ASYNCHRONOUS_ECHO_MODE = 0b01,
    CR7_LOCAL_LOOPBACK = 0b10,
    CR7_REMOTE_LOOPBACK = 0b11
} CR7_OperatingMode;

typedef enum {
    CR5_RTS_HIGH = 0,
    CR5_RTS_LOW = 1
} CR5_RequestToSend;

typedef enum {
    CR4_NORMAL = 0,
    CR4_RESET = 1
} CR4_ResetError;

typedef struct {
    uint8_t tx_enable : 1;
    uint8_t dtr_control : 1;
    uint8_t rx_enable : 1;
    uint8_t force_break : 1;
    CR4_ResetError reset_error : 1;
    CR5_RequestToSend request_to_send : 1;
    CR7_OperatingMode operating_mode : 2;
} CommandRegister;

typedef union {
    uint8_t raw;
    CommandRegister reg;
} CommandRegisterUnion;

// Status Register (SR) Definitions
typedef struct {
    uint8_t tx_ready : 1;
    uint8_t rx_ready : 1;
    uint8_t tx_empty : 1;
    uint8_t parity_error : 1;
    uint8_t overrun_error : 1;
    uint8_t framing_error : 1;
    uint8_t data_carrier_detect : 1;
    uint8_t data_set_ready : 1;
} StatusRegister;

typedef union {
    uint8_t raw;
    StatusRegister reg;
} StatusRegisterUnion;

#pragma pack()

#endif // SIGNETICS_2651_UART_H