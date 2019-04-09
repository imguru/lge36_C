include ../Make.defines

PROGS =	checkopts defaultopts getsetopt negotiateopts \
		daytimecli02 daytimeudpsrv1 prtbufs setbufs

all:	${PROGS}

checkopts:	checkopts.o
		${CC} ${CFLAGS} -o $@ checkopts.o ${LIBS_XTI}

defaultopts:	defaultopts.o
		${CC} ${CFLAGS} -o $@ defaultopts.o ${LIBS_XTI}

getsetopt:	getsetopt.o
		${CC} ${CFLAGS} -o $@ getsetopt.o ${LIBS_XTI}

negotiateopts:	negotiateopts.o
		${CC} ${CFLAGS} -o $@ negotiateopts.o ${LIBS_XTI}

daytimecli02:	daytimecli02.o tcp_connect.o
		${CC} ${CFLAGS} -o $@ daytimecli02.o tcp_connect.o ${LIBS_XTI}

daytimeudpsrv1:	daytimeudpsrv1.o
		${CC} ${CFLAGS} -o $@ daytimeudpsrv1.o ${LIBS_XTI}

prtbufs:	prtbufs.o
		${CC} ${CFLAGS} -o $@ prtbufs.o ${LIBS_XTI}

setbufs:	setbufs.o
		${CC} ${CFLAGS} -o $@ setbufs.o ${LIBS_XTI}

clean:
		rm -f ${PROGS} ${CLEANFILES}
