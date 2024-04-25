#include "drivers.h"

int hook_id_uart = 4;

int (uart_subscribe_int)(uint8_t *bit_no)
{
	if (!bit_no) return 1;

	*bit_no = BIT(hook_id_uart);

	return sys_irqsetpolicy(IRQ_COM1, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_uart);
}

int (uart_unsubscribe_int)()
{
	if (hook_id_uart < 0) return 1;

	return sys_irqrmpolicy(&hook_id_uart);
}

int uart_read(int base_addr, uint8_t offset, uint8_t *out)
{
	return util_sys_inb(base_addr + offset, out);
}

int uart_write(int base_addr, uint8_t offset, uint8_t in)
{
	return sys_outb(base_addr + offset, in);
}

int	uart_DL_access(int com_num, bool enable)
{
	uint8_t response;
	int base_addr = com_num != 2 ? UART_COM1 : UART_COM2;

	if (com_num < 1 || com_num > 2) return 1;

	int retv = uart_read(base_addr, UART_LCR, &response);
	if (retv) return 1;

	if (enable) 
		response |= UART_LCR_DLAB;
	else
		response &= ~UART_LCR_DLAB;
	
	return uart_write(base_addr, UART_LCR, response);
}

int	uart_set_bit_rate(int com_num, int rate)
{
	uint8_t lsb, msb;

	int base_address = com_num != 2 ? UART_COM1 : UART_COM2;

	if (com_num < 1 || com_num > 2) return 1;

	if (util_get_LSB(UART_BASE_BIT_RATE / rate, &lsb)) return 1;
	if (util_get_MSB(UART_BASE_BIT_RATE / rate, &msb)) return 1;

	if (uart_DL_access(1, true)) return 1;

	if (uart_write(base_address, UART_DLL, lsb)) return 1;
	if (uart_write(base_address, UART_DLM, msb)) return 1;

	return uart_DL_access(1, false);
}

int uart_write_byte(int base_addr, uint8_t byte)
{
	uint8_t response;
	int attemps = MAX_TRIES;
	
	while (attemps > 0)
	{
		if (uart_read(base_addr, UART_LSR, &response)) return 1;

		if (response & UART_LSR_EMPTY_HOLD)
			return uart_write(base_addr, UART_THR, byte);

		attemps--;
		tickdelay(micros_to_ticks(UART_DELAY));
	}
	return 1;
}

int uart_read_byte(int base_addr, uint8_t *out)
{
	uint8_t response;
	int attemps = MAX_TRIES;
	
	while (attemps > 0)
	{
		if (uart_read(base_addr, UART_LSR, &response)) return 1;

		if (response & UART_LSR_HAS_DATA)
			return uart_read(base_addr, UART_RBR, out);
		
		attemps--;
		tickdelay(micros_to_ticks(UART_DELAY));
	}
	return 1;
}

int uart_wb_byte(int base_addr, uint8_t byte)
{
	uint8_t response;

	if (uart_write_byte(base_addr, byte)) return 1;
	printf("b\n");
	if (uart_read_byte(base_addr, &response)) return 1;
	printf("c\n");
	return response != SPROTO_OK;
}

int uart_write_msg(int com_num, uint8_t *msg)
{
	int base_addr = com_num != 2 ? UART_COM1 : UART_COM2;
	uint8_t response;

	if (com_num < 1 || com_num > 2) return 1;

	if (uart_wb_byte(base_addr, SPROTO_BEGIN)) return 1;

	for (uint8_t i = 0; i < SPROTO_MSG_SIZE; i++)
	{
		if (uart_wb_byte(base_addr, msg[i])) return 1;
	}

	if (uart_wb_byte(base_addr, SPROTO_END)) return 1;

	if (uart_read_byte(base_addr, &response)) return 1;
	return response != SPROTO_OK;
}

int uart_reset(int base_addr)
{
	uint8_t content;

	if (uart_read(base_addr, UART_LSR, &content)) return 1;

	if (content & UART_LSR_HAS_DATA)
		return uart_read(base_addr, UART_RBR, &content);
	
	return 0;
}

static uint8_t output = 0;
static int bytes[5];
static uint8_t idx = 0;

int uart_parse_byte()
{
	if (idx == 0 && output == SPROTO_BEGIN)
	{
		bytes[idx] = output;
		idx++;
		return 0;
	}
	if (idx == 4 && output == SPROTO_END)
	{
		bytes[idx] = output;
		idx = 0;
		return 1;
	}
	if (idx > 1 && idx < SPROTO_SIZE)
	{
		bytes[idx] = output;
		idx++;
		return 0;
	}
	return -1;
}

void (uart_ih)()
{
	uint8_t response;

	if (uart_read(UART_COM1, UART_IIR, &response)) return;

	if (response & UART_IIR_INT_NONE) return;

	response &= response & UART_IIR_INT_MASK;

	if (response != UART_IIR_INT_RECEIVED_DATA)
	{
		uart_reset(UART_COM1);
		uart_write_byte(UART_COM1, SPROTO_KO);
		return;
	}

	switch(uart_parse_byte())
	{
		case -1:
			uart_reset(UART_COM1);
			uart_write_byte(UART_COM1, SPROTO_KO);
			return;
		case 0:
			uart_write_byte(UART_COM1, SPROTO_OK);
			return;
		case 1:
			uart_write_byte(UART_COM1, SPROTO_OK);
			
			printf("BEGIN: %d\n\n%d\n%d\n%d\nEND:%d\n", 
				bytes[0], bytes[1], bytes[2], bytes[3], bytes[4]);
			
			// TODO: Handle content in bytes
			
			break;
	}
}

int uart_setup(int bit_rate)
{
	uint8_t cmd;

	cmd = UART_IER_ENABLE_INT_DATA | UART_IER_ENABLE_INT_LSR;
	if (uart_write(UART_COM1, UART_IER, cmd)) return 1;

	cmd = UART_LCR_8BITCHAR | UART_LCR_2STOP | UART_LCR_PARTIY_EVEN;
	if (uart_write(UART_COM1, UART_LCR, cmd)) return 1;

	if (uart_set_bit_rate(1, UART_DEFAULT_BIT_RATE)) return 1;

	return uart_reset(UART_COM1);
}
