include ../Make.defines

PROGS =	serv01

all:	${PROGS}

# serv01: one fork per client (traditional concurrent server).
serv01:	serv01.o web_child.o sig_chld_waitpid.o 
		${CC} ${CFLAGS} -o $@ serv01.o web_child.o sig_chld_waitpid.o ${LIBS_XTI}

clean:
		rm -f ${PROGS} ${CLEANFILES}
