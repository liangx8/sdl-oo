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

#CFLAGS +=-std=c++14

SRCS=$(wildcard *.cc)
OBJS=${SRCS:.cc=.o}
LDFLAGS=-Wall
LDFLAGS+=$(shell pkgconf sdl2 --libs)
LDFLAGS+=-lSDL2_image
LDFLAGS+=-lSDL2_ttf
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

