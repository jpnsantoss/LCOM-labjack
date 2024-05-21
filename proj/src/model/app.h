#ifndef _LCOM_APP_H_
#define _LCOM_APP_H_

#include <lcom/lcf.h>
#include "game.h"
#include "../state/state.h"
#include "../sprite/sprite.h"
#include "../drivers/drivers.h"

typedef struct {
	sprite_t *cursor;
	sprite_t *background;
	// sprite_t *main_menu;
	// sprite_t *game_betting;
	// sprite_t *game;
	game_t	game;
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

typedef struct {
	app_state_t				state;
	interrupt_type_t	interrupt;
	
} ev_listener_t;

app_t *app_init();
void updateCursorPos(mouse_info_t *mouse_info);

#endif
