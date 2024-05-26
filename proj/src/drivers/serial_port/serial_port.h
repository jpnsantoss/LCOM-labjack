#ifndef _LCOM_DRIVER_SERIAL_PORT_H_
#define _LCOM_DRIVER_SERIAL_PORT_H_

#include <lcom/lcf.h>
#include "iUART.h"
#include "../../data_structures/queue.h"

int (uart_subscribe_int)(uint8_t *bit_no);
int (uart_unsubscribe_int)();
int (uart_read)(int base_addr, uint8_t offset, uint8_t *out);
int (uart_write)(int base_addr, uint8_t offset, uint8_t in);
int	(uart_DL_access)(int base_addr, int enable);
int	(uart_set_bit_rate)(int base_addr, int rate);
int (uart_fifo_read)(int base_addr);
int (uart_fifo_write)(int base_addr);
int (uart_send_byte)(uint8_t byte);
int (uart_get_byte)(uint8_t *byte);
int (uart_ih)();
int (uart_init)(uint8_t *bit_no, int bit_rate);
int (uart_disable)();

#endif
