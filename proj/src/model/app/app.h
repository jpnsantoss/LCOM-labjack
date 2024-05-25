#ifndef _LCOM_APP_H_
#define _LCOM_APP_H_

#include <lcom/lcf.h>
#include "../sprite/sprite.h"
#include "../animation/animation.h"
#include "../cursor/cursor.h"
#include "../../drivers/drivers.h"
#include "../game/game.h"

#define KB_ESC 0x81
#define KB_ENTER 0x9c
#define KB_X 0xad
#define KB_Y 0x95
#define KB_C 0xae

#define KB_0 0x8b
#define KB_1 0x82
#define KB_2 0x83
#define KB_3 0x84
#define KB_4 0x85
#define KB_5 0x86
#define KB_6 0x87
#define KB_7 0x88
#define KB_8 0x89
#define KB_9 0x8a

typedef enum {
	MAIN_MENU,
	GAME_BET,
	GAME_PLAY,
	GAME_OVER,
	EXIT,
	EXIT_CONFIRMATION
} app_state_t;

typedef struct {
	cursor_t		cursor;

	sprite_t		*background;
	queue_t 		*buttons_main_menu;
	queue_t			*buttons_game_playing;
	queue_t			*buttons_game_over;
	my_stack_t 	*xpms_numbers;

	animation_t *card_loop;
	
	game_t			game;
	app_state_t	state;
} app_t;

typedef struct {
  uint8_t kb;
  uint8_t mouse;
  uint8_t uart;
  uint8_t timer;
  uint8_t rtc;
} bit_no_t;

typedef enum {
	TIMER,
	KEYBOARD,
	MOUSE,
	RTC,
	UART
} interrupt_type_t;

app_t *app_init();
void 	app_destroy(app_t *app);
int		app_buttons_main_menu_init(queue_t **queue);
int		app_buttons_game_playing_init(queue_t **queue);

#endif
