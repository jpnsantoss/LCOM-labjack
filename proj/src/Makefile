
.PATH: ${.CURDIR}/drivers/graphics
.PATH: ${.CURDIR}/drivers/input
.PATH: ${.CURDIR}/drivers/rtc
.PATH: ${.CURDIR}/drivers/serial_port
.PATH: ${.CURDIR}/drivers/timer
.PATH: ${.CURDIR}/drivers/utils
.PATH: ${.CURDIR}/data_structures
.PATH: ${.CURDIR}/ev_listener
.PATH: ${.CURDIR}/model/card
.PATH: ${.CURDIR}/model/game
.PATH: ${.CURDIR}/model/app
.PATH: ${.CURDIR}/model/player
.PATH: ${.CURDIR}/model/sprite
.PATH: ${.CURDIR}/model/animation
.PATH: ${.CURDIR}/model/cursor
.PATH: ${.CURDIR}/drawer

# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = proj.c
# drivers
SRCS += dvr_graphics.c dvr_kbc.c dvr_keyboard.c dvr_mouse.c dvr_timer.c dvr_rtc.c dvr_uart.c utils.c
# data_structs
SRCS += queue.c stack.c ev_listener.c
# models
SRCS += sprite.c app.c drawer.c player.c card.c game.c cursor.c animation.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D__LCOM_OPTIMIZED__

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

fclean:
	rm -fr *.a *.o proj trace.txt output.txt

cln:
	rm -fr *.a *.o

cb: all cln

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
