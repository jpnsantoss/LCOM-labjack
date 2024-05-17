#ifndef STATE_H
#define STATE_H

typedef enum {
	MAIN_MENU,
	PAUSE_MENU,
	GAME_BETTING,
	GAME_PLAYING,
	GAME_OVER,
	EXIT
} app_state_t;

int set_state(app_state_t state);

app_state_t get_state();

#endif
