#include "ev_listener.h"
#include "../drivers/drivers.h"
#include "../drawer/drawer.h"

extern uint8_t scancode;
extern int timer_counter;

state_handler_t listeners[] = {
  { MAIN_MENU, handle_main_menu },
  { GAME_BETTING, handle_game_betting },
};

void handle_interrupt(app_t *app, ev_listener_t listener)
{
	listeners[listener.state].handle(app, listener.interrupt);
	handle_general(app, listener.interrupt);
}

void handle_general(app_t *app, interrupt_type_t interrupt)
{
	mouse_info_t info;

	switch (interrupt)
	{
		case KEYBOARD:
			kbc_ih();
			if(scancode == KEYBOARD_ESC) set_state(EXIT);
			break;
		case MOUSE:
			mouse_ih();
			// mouseSync();
			if(mouse_read_packet(&info))
			{
				printf("dx: %d, dy: %d\n", info.delta_x, info.delta_y);
				printf("rb: %d, mb: %d, lb: %d\n", info.rb, info.mb, info.lb);
				updateCursorPos(&info);
			}
			break;
		case UART:
			uart_ih();
			break;
		case TIMER:
			timer_int_handler();
			if (timer_counter % 60) {
				timer_counter = 0;
				draw_screen(app);
			}
			break;
		case RTC:
			break;
	}
}

void handle_main_menu(app_t *app, interrupt_type_t interrupt)
{
  if (interrupt == TIMER) {
    // Handle the interrupt here
  }
}

// Function to handle the interrupts in the game start
void handle_game_betting(app_t *app, interrupt_type_t interrupt)
{
  if (interrupt == MOUSE) {
    // Handle the interrupt here
  }
}
