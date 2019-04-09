include ../Make.defines

all:	${LIBFREE_OBJS}
		ar rv ${LIBUNP_NAME} $?
		${RANLIB} ${LIBUNP_NAME}

clean:
		rm -f ${PROGS} ${CLEANFILES}
