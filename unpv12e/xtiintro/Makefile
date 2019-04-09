include ../Make.defines

PROGS =	daytimecli01 daytimecli02 daytimecli03 \
	daytimesrv01 daytimesrv02 daytimesrv03 prtinfo strerror tiname

all:	${PROGS}

daytimecli01:	daytimecli01.o
		${CC} ${CFLAGS} -o $@ daytimecli01.o ${LIBS_XTI}

daytimecli02:	daytimecli02.o
		${CC} ${CFLAGS} -o $@ daytimecli02.o ${LIBS_XTI}

daytimecli03:	daytimecli03.o
		${CC} ${CFLAGS} -o $@ daytimecli03.o ${LIBS_XTI}

daytimesrv01:	daytimesrv01.o
		${CC} ${CFLAGS} -o $@ daytimesrv01.o ${LIBS_XTI}

daytimesrv02:	daytimesrv02.o
		${CC} ${CFLAGS} -o $@ daytimesrv02.o ${LIBS_XTI}

daytimesrv03:	daytimesrv03.o
		${CC} ${CFLAGS} -o $@ daytimesrv03.o ${LIBS_XTI}

prtinfo:	prtinfo.o
		${CC} ${CFLAGS} -o $@ prtinfo.o ${LIBS_XTI}

strerror:	strerror.o
		${CC} ${CFLAGS} -o $@ strerror.o ${LIBS_XTI}

tiname:	tiname.o
		${CC} ${CFLAGS} -o $@ tiname.o ${LIBS_XTI}

clean:
		rm -f ${PROGS} ${CLEANFILES}
