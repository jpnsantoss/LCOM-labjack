#ifndef _LCOM_EV_LISTENER_H_
#define _LCOM_EV_LISTENER_H_

#include "../drivers/drivers.h"
#include "../drawer/drawer.h"
#include "../model/sprite/sprite.h"
#include "../model/game/game.h"
#include "../model/app/app.h"
#include "../model/animation/animation.h"
#include "../assets/cards/rotate1.xpm"
#include "../assets/cards/rotate2.xpm"

typedef void(*handler)(app_t *, interrupt_type_t);

void	handle_interrupt(app_t *app, interrupt_type_t interrupt);
void	handle_general(app_t *app, interrupt_type_t interrupt);

void	handle_main_menu(app_t *app, interrupt_type_t interrupt);

void	handle_game_playing(app_t *app, interrupt_type_t interrupt);
void	handle_hit(void *ptr);

void	handle_game_betting(app_t *app, interrupt_type_t interrupt);
void	handle_game_over(app_t *app, interrupt_type_t interrupt);

void	handle_bet_value(app_t *app, interrupt_type_t interrupt);
void	handle_bet_value_check(app_t *app);

void	handle_dealer_turn(app_t *app, interrupt_type_t interrupt);
void	add_dealer_single_animation(app_t *app);

#endif
