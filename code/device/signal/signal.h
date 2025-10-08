#ifndef _DEVICE_SIGNAL_H_
#define _DEVICE_SIGNAL_H_

#include "zf_common_typedef.h"
#include "zf_driver_uart.h"

#define SIGNAL_RX_BUF_SIZE 64
#define SIGNAL_PAYLOAD_MAX 60

typedef struct
{
    vuint8 cmd;
    vuint8 len; // payload 长度
    vint16 front_dis;
    vint16 left_dis;
    vint16 right_dis;
} signal_message_t;

typedef struct
{
    uart_index_enum uartn;
    vuint8 rx_buf[SIGNAL_RX_BUF_SIZE];
    vuint8 data_cnt;
    vuint8 receive_flag;
} signal_obj_t;

signal_obj_t signal_uart_init(uart_index_enum uartn, uart_rx_pin_enum rx_pin, uart_tx_pin_enum tx_pin, vuint32 baud);
void signal_uart_handler(signal_obj_t *signal);
signal_message_t signal_pop_data(signal_obj_t *signal);

#endif