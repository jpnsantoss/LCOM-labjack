#ifndef _LCOM_IUART_H_
#define _LCOM_IUART_H_

#include <lcom/lcf.h>

#define UART_BASE_BIT_RATE 115200
#define UART_DEFAULT_BIT_RATE 9600
#define UART_DELAY 10000
#define UART_MAX_TRIES 4

#define UART_COM1 0x3F8 // Base address
#define UART_COM2 0x2F8 // Base address

#define UART_COM1_VECTOR 0x0C
#define UART_COM2_VECTOR 0x0B

#define IRQ_COM1 4
#define IRQ_COM2 3

#define UART_RBR 0 // R - Receiver Buffer
#define UART_THR 0 // W - Transmitter Holding
#define UART_IER 1 // R/W - Interrupt Enable
#define UART_IIR 2 // R - Interrupt Identification
#define UART_FCR 2 // W - FIFO Control
#define UART_LCR 3 // R/W - Line Control
#define UART_MCR 4 // R/W - Modem Control
#define UART_LSR 5 // R - Line Status
#define UART_MSR 6 // R - Modem Status
#define UART_SR  7 // R/W - Scratchpad

/**
 * R/W - Divisor Latch LSB
 * Enabled if DLAB of LCR is set to 1
*/
#define UART_DLL 0
/**
 * R/W - Divisor Latch MSB 
 * Enabled if DLAB of LCR is set to 1
*/
#define UART_DLM 1 

#define UART_LCR_5BITCHAR 				0
#define UART_LCR_6BITCHAR 				BIT(0)
#define UART_LCR_7BITCHAR 				BIT(1)
#define UART_LCR_8BITCHAR 				BIT(0) | BIT(1)
#define UART_LCR_1STOP 					0
#define UART_LCR_2STOP 					BIT(2)
#define UART_LCR_PARITY_NONE 			0
#define UART_LCR_PARITY_ODD 			BIT(3)
#define UART_LCR_PARTIY_EVEN 			BIT(3) | BIT(4)
#define UART_LCR_PARITY_1 				BIT(3) | BIT(5)
#define UART_LCR_PARITY_0 				BIT(3) | BIT(4) | BIT(5)
#define UART_LCR_BREAK_CTRL 			BIT(6)
#define UART_LCR_DLAB 					BIT(7)

#define UART_LSR_HAS_DATA 				BIT(0)
#define UART_LSR_ERR_OVERRUN 			BIT(1)
#define UART_LSR_ERR_PARITY 			BIT(2)
#define UART_LSR_ERR_FRAMING 			BIT(3)
#define UART_LSR_ERR							BIT(1) | BIT(2) | BIT(3)
#define UART_LSR_BREAK_INTERRUPT 		BIT(4)
#define UART_LSR_EMPTY_HOLD 			BIT(5)
#define UART_LSR_ALL_EMPTY 				BIT(6)
#define UART_LSR_ERR_FIFO 				BIT(7)

#define UART_IER_ENABLE_INT_DATA 		BIT(0)
#define UART_IER_ENABLE_INT_THR	 		BIT(1)
#define UART_IER_ENABLE_INT_LSR 		BIT(2)
#define UART_IER_ENABLE_INT_MODEM 		BIT(3)

#define UART_IIR_NO_INTS				BIT(0)

#define UART_IIR_INT_MASK				BIT(1) | BIT(2) | BIT(3)
#define UART_IIR_INT_MODEM 				0
#define UART_IIR_INT_NONE				BIT(1)
#define UART_IIR_INT_RECEIVED_DATA 		BIT(2)
#define UART_IIR_INT_CHAR_TIMEOUT		BIT(3)
#define UART_IIR_INT_LINE_STATUS		BIT(2) | BIT(3)

#define UART_IIR_64BITFIFO				BIT(5)
#define UART_IIR_FIFO_UNUSABLE			BIT(7)
#define UART_IIR_FIFO_ENABLED			BIT(6) | BIT(7)

#define UART_FCR_FIFO_ENABLE			BIT(0)
#define UART_FCR_FIFO_RCVR_CLEAR 		BIT(1)
#define UART_FCR_FIFO_XMIT_CLEAR		BIT(2)
#define UART_FCR_6EBITFIFO_ENABLE 		BIT(5)
#define UART_FCR_FIFO_RCVR_1BYTE 		0
#define UART_FCR_FIFO_RCVR_4BYTE  		BIT(6)
#define UART_FCR_FIFO_RCVR_8BYTE		BIT(7)
#define UART_FCR_FIFO_RCVR_14BYTE 		BIT(6) | BIT(7)

#endif /* _LCOM_IUART_H */
