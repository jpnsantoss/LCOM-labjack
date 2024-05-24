#include <lcom/lcf.h>
#include "drivers/drivers.h"
#include "model/game/game.h"
#include "model/app/app.h"
#include "ev_listener/ev_listener.h"
#include "data_structures/stack.h"

int counter = 0;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[])
{
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv)) return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int close_app()
{
	if (uart_disable()) return 1;

	if (mouse_disable()) return 1;

	if (kbd_unsubscribe_int()) return 1;

	if (timer_unsubscribe_int()) return 1;

	return vg_exit();
}

int (proj_main_loop)(int argc, char **argv)
{
  bit_no_t bit_no;
	int ipc_status;
	message msg;

  vg_init_mode();

  if (timer_subscribe_int(&bit_no.timer)) return 1;

	if (timer_set_frequency(0, 30)) return 1;

	if (uart_setup(UART_DEFAULT_BIT_RATE)) return 1;

	if (uart_subscribe_int(&bit_no.uart)) return 1;
	
 	if (mouse_init(&bit_no.mouse)) return 1;

  if (kbd_subscribe_int(&bit_no.kb)) return 1;

	app_t *app = app_init();
	if (app == NULL) close_app();
	
	counter = 0;

	while (app->state != EXIT)
	{
    if (driver_receive(ANY, &msg, &ipc_status)) continue;

    if (!is_ipc_notify(ipc_status)) continue;

		if (_ENDPOINT_P(msg.m_source) != HARDWARE) continue;

		if (msg.m_notify.interrupts & bit_no.mouse)
		{
			handle_interrupt(app, MOUSE);
		}

		if (msg.m_notify.interrupts & bit_no.uart)
		{
			printf("UART IH\n");
			handle_interrupt(app, UART);
		}

		if (msg.m_notify.interrupts & bit_no.rtc)
		{
			handle_interrupt(app, RTC);
		}

		if (msg.m_notify.interrupts & bit_no.kb)
		{
			handle_interrupt(app, KEYBOARD);
		}

		if (msg.m_notify.interrupts & bit_no.timer)
		{
			handle_interrupt(app, TIMER);
		}
	}

	app_destroy(app);
  return close_app();
}
