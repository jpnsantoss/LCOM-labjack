#include "drivers.h"

int hook_id_uart = 4;
int timer_counter = 0;

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

void (uart_ih)()
{

}
