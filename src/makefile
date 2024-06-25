.PHONY: clean
CC=g++
RM=rm -rf
CFLAGS=-Wall
CFLAGS+=$(shell pkgconf sdl2 --cflags)
TARGET=soo

ifeq (${OPTS}X,X)
	CFLAGS+=-O2
else
	CFLAGS+=${OPTS}
endif

SRCS=$(wildcard *.cc)
OBJS=${SRCS:.cc=.o}
LDFLAGS=-Wall
LDFLAGS+=$(shell pkgconf sdl2 --libs) -lSDL2_image
LDFLAGS+=# -static

all:${TARGET}
	@echo "*** Done ***"
release:${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LDFLAGS}
	strip	${TARGET}
	@echo "*** Done ***"
${TARGET}:${OBJS}
	${CC} -o $@ ${OBJS} ${LDFLAGS}
clean:
	${RM} *.o ${TARGET} *~


#%.o:%.cpp
.cc.o:
	${CC} -c $< ${CFLAGS}

