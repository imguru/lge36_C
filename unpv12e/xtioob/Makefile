include ../Make.defines

PROGS =	tcprecv01 tcprecv02 tcprecv03 tcprecv04 tcprecv05

all:	${PROGS}

tcprecv01:	tcprecv01.o
		${CC} ${CFLAGS} -o $@ tcprecv01.o ${LIBS_XTI}

tcprecv02:	tcprecv02.o
		${CC} ${CFLAGS} -o $@ tcprecv02.o ${LIBS_XTI}

tcprecv03:	tcprecv03.o
		${CC} ${CFLAGS} -o $@ tcprecv03.o ${LIBS_XTI}

tcprecv04:	tcprecv04.o
		${CC} ${CFLAGS} -o $@ tcprecv04.o ${LIBS_XTI}

tcprecv05:	tcprecv05.o
		${CC} ${CFLAGS} -o $@ tcprecv05.o ${LIBS_XTI}

clean:
		rm -f ${PROGS} ${CLEANFILES}
