include ../Make.defines

OBJS = main.o cleanup.o pcap.o udpcksum.o udpread.o udpwrite.o
PROGS =	udpcksum

all:	${PROGS}

udpcksum:	${OBJS}
		${CC} ${CFLAGS} -o $@ ${OBJS} /usr/local/lib/libpcap.a ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
