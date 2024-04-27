#include <lcom/lcf.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "i8042.h"
#include "i8254.h"


// mouse
int mouse_subscribe_int(uint8_t *bit_no);
int mouse_unsubscribe_int();
void (mouse_ih)();
void mouse_fill_packet(int *bytes, struct packet *pp);

// kbc
int kbc_write_input(uint8_t port, uint8_t input);
int kbc_read_output(uint8_t port, uint8_t *output, bool mouse);
int kbc_read_status(uint8_t *output);
int kbc_write(uint8_t intent, bool mouse);

//utils
int (util_get_LSB)(uint16_t val, uint8_t *lsb);
int (util_get_MSB)(uint16_t val, uint8_t *msb);
int (util_sys_inb)(int port, uint8_t *value);


