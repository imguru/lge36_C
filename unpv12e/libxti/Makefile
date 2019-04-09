include ../Make.defines

all:	${LIBXTI_OBJS}
		ar rv ${LIBUNPXTI_NAME} $?
		${RANLIB} ${LIBUNPXTI_NAME}

clean:
		rm -f ${PROGS} ${CLEANFILES}
