include ../Make.defines

PROGS =	daytimeudpcli1 daytimeudpcli2 daytimeudpcli3 daytimeudpcli4 \
		daytimeudpsrv1 daytimeudpsrv2

all:	${PROGS}

daytimeudpcli1:	daytimeudpcli1.o
		${CC} ${CFLAGS} -o $@ daytimeudpcli1.o ${LIBS_XTI}

daytimeudpcli2:	daytimeudpcli2.o
		${CC} ${CFLAGS} -o $@ daytimeudpcli2.o ${LIBS_XTI}

daytimeudpcli3:	daytimeudpcli3.o
		${CC} ${CFLAGS} -o $@ daytimeudpcli3.o ${LIBS_XTI}

daytimeudpcli4:	daytimeudpcli4.o
		${CC} ${CFLAGS} -o $@ daytimeudpcli4.o ${LIBS_XTI}

daytimeudpsrv1:	daytimeudpsrv1.o
		${CC} ${CFLAGS} -o $@ daytimeudpsrv1.o ${LIBS_XTI}

daytimeudpsrv2:	daytimeudpsrv2.o
		${CC} ${CFLAGS} -o $@ daytimeudpsrv2.o ${LIBS_XTI}

clean:
		rm -f ${PROGS} ${CLEANFILES}
