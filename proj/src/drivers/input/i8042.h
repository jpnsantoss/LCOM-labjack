#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 Keyboard
 */

#define IRQ_KEYBOARD 1
#define IRQ_MOUSE 12

#define DELAY_US 20000

#define MAKECODE_BIT BIT(7)
#define TWOBITS 0xE0

#define STAT_REG 0x64
#define OUT_BUF 0x60

#define READ_CMD    0x20
#define WRITE_CMD   0x60
#define WRITE_CMD_MOUSE 0xD4

#define PARITY_BIT BIT(7)
#define TIMEOUT_BIT BIT(6)
#define MOUSE_BIT BIT(5)

#define FULL_INPUT BIT(1)
#define FULL_OUTPUT BIT(0)

#define ENABLE_INT BIT(0)

#define MOUSE_CTRL_LB BIT(0)
#define MOUSE_CTRL_RB BIT(1)
#define MOUSE_CTRL_MB BIT(2)
#define MOUSE_CTRL_X_SIG BIT(4)
#define MOUSE_CTRL_Y_SIG BIT(5)
#define MOUSE_CTRL_X_OFW BIT(6)
#define MOUSE_CTRL_Y_OFW BIT(7)

#define MOUSE_DATA_REPORT_ENABLE 0xF4
#define MOUSE_DATA_REPORT_DISABLE 0xF5

#endif /* _LCOM_I8042_H */
