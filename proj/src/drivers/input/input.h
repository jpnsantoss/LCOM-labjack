#ifndef _LCOM_DRIVER_INPUT_H_
#define _LCOM_DRIVER_INPUT_H_

#include <lcom/lcf.h>
#include "i8042.h"

#define KBC_MAX_TRIES 10

typedef struct packet mouse_info_t;

// Keyboard Controller
int kbc_write_input(uint8_t port, uint8_t input);
int kbc_read_output(uint8_t port, uint8_t *output, bool mouse);
int kbc_write(uint8_t intent, bool mouse);

// Keyboard
int kbd_subscribe_int(uint8_t *bit_no);
int kbd_unsubscribe_int();

void (kbc_ih)();

// Mouse
int mouse_init(uint8_t *bit_no);
int mouse_disable();

int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();

void (mouse_ih)();

void mouse_fill_packet(uint8_t *bytes, struct packet *pp);
int mouse_read_packet();
mouse_info_t *mouse_get_info();

#endif
