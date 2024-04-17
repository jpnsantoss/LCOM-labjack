#ifndef _LCOM_iUART_H_
#define _LCOM_iUART_H_

#include <lcom/lcf.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM_PORT_NUM 8

#define COM1_VECTOR 0x0C
#define COM2_VECTOR 0x0B

#define IRQ_COM1 3
#define IRQ_COM2 4

#define COM_RECEIVE_BUFF 0
#define COM_TRANSMIT_BUFF 0
#define COM_INT_ENABLE 1
#define COM_INT_IDENTIF 2
#define COM_INT_FIFO 2
#define COM_LINE_CONTROL 3
#define COM_MODEM_CONTROL 4
#define COM_LINE_STATUS 5
#define COM_MODEM_STATUS 6
#define COM_SCRATCHPAD 7

#endif /* _LCOM_iUART_H */
