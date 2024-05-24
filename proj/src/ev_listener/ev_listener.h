#ifndef _LCOM_EV_LISTENER_H_
#define _LCOM_EV_LISTENER_H_

#include "../drivers/drivers.h"
#include "../drawer/drawer.h"
#include "../model/sprite/sprite.h"
#include "../model/game/game.h"
#include "../model/app/app.h"

typedef void(*handler)(app_t *, interrupt_type_t);

extern handler listeners[];

void	handle_interrupt(app_t *app, interrupt_type_t interrupt);

void	handle_general(app_t *app, interrupt_type_t interrupt);

void	handle_main_menu(app_t *app, interrupt_type_t interrupt);
void	handle_game_playing(app_t *app, interrupt_type_t interrupt);
void	handle_game_betting(app_t *app, interrupt_type_t interrupt);
void	handle_game_over(app_t *app, interrupt_type_t interrupt);
void	handle_bet_value(app_t *app, interrupt_type_t interrupt);

#endif
