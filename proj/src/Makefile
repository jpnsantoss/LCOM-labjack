
.PATH: ${.CURDIR}/drivers
.PATH: ${.CURDIR}/drivers/graphics
.PATH: ${.CURDIR}/drivers/input
.PATH: ${.CURDIR}/drivers/rtc
.PATH: ${.CURDIR}/drivers/serial_port
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/containers
.PATH: ${.CURDIR}/xpm
.PATH: ${.CURDIR}/models/card
.PATH: ${.CURDIR}/models/game
.PATH: ${.CURDIR}/models/player

# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = proj.c dvr_graphics.c dvr_kbc.c dvr_keyboard.c dvr_mouse.c dvr_timer.c dvr_uart.c utils.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D_LCOM_OPTIMIZED_

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

fclean:
	rm -fr proj *.a *.o a.out

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
