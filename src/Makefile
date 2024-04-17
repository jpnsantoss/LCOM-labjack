# name of the program (Minix service)
PROG=proj

# source code files to be compiled
SRCS = proj.c lib/drivers/dvr_graphics.c lib/drivers/dvr_kbc.c lib/drivers/dvr_keyboard.c lib/drivers/dvr_mouse.c lib/drivers/dvr_timer.c

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
