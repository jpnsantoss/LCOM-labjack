#ifndef _LCOM_APP_H_
#define _LCOM_APP_H_

#include <lcom/lcf.h>
#include "../game/game.h"
#include "../../sprite/sprite.h"
#include "../../drivers/drivers.h"

typedef enum {
	MAIN_MENU,
	GAME_BETTING,
	GAME_PLAYING,
	GAME_OVER,
	EXIT
} app_state_t;

typedef struct {
	sprite_t *cursor;
	sprite_t *background;
	sprite_t *play_button;
	sprite_t *exit_button;
	// sprite_t *main_menu;
	// sprite_t *game_betting;
	// sprite_t *game;
	game_t	game;
	app_state_t state;
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
void updateCursorPos(mouse_info_t *mouse_info);

#endif
