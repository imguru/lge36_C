include ../Make.defines

PROGS =	sntp

all:	${PROGS}

sntp:	main.o bind_ubcast.o bind_mcast.o read_loop.o sntp_send.o sntp_proc.o
		${CC} ${CFLAGS} -o $@ main.o bind_ubcast.o bind_mcast.o read_loop.o \
				sntp_send.o sntp_proc.o ${LIBS} 

clean:
		rm -f ${PROGS} ${CLEANFILES}
