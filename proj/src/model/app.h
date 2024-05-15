#ifndef _LCOM_APP_H_
#define _LCOM_APP_H_

#include <lcom/lcf.h>

typedef struct {
  uint8_t kb;
  uint8_t mouse;
  uint8_t uart;
  uint8_t timer;
  uint8_t rtc;
} bit_no_t;

typedef enum app_state_s {
	MAIN_MENU,
	PAUSE_MENU,
	GAME_BETTING,
	GAME_PLAYING,
	GAME_OVER
} app_state_t;

typedef enum interrupt_type_s {
	TIMER,
	KEYBOARD,
	MOUSE,
	RTC,
	UART
} interrupt_type_t;

typedef struct ev_listener_s {
	app_state_t				app_state;
	interrupt_type_t	interrupt;
	
} ev_listener_t;

#endif
