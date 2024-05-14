#ifndef _LCOM_GAME_H_
#define _LCOM_GAME_H_

#include <lcom/lcf.h>
#include "../containers/queue/queue.h"

typedef enum game_state_s {
	MAIN_MENU,
	PAUSE_MENU,
	GAME_BETTING,
	GAME_PLAYING,
	GAME_OVER
} game_state_t;

typedef struct game_s {
	uint8_t bit_no_kb;
	uint8_t bit_no_mouse;
	uint8_t bit_no_uart;
	uint8_t bit_no_timer;
	uint8_t bit_no_rtc;

	game_state_t state = MAIN_MENU;
	queue_t *cards;
} game_t;

#endif
