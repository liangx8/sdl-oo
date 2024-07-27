.PHONY: clean
CC=g++
RM=rm -rf
CFLAGS=-Wall
#CFLAGS+=$(shell pkgconf sdl2 --cflags)
TARGET=block

ifeq (${OPTS}X,X)
	CFLAGS+=-O2
else
	CFLAGS+=${OPTS}
endif

#CFLAGS +=-std=c++14

SRCS=$(wildcard *.cc)
SRCS+=$(wildcard soo/*.cc)
OBJS=${SRCS:.cc=.o}
LDFLAGS=-Wall
LDFLAGS+=-lSDL2
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
	${RM} ${TARGET} *~
	find -name \*.o -exec ${RM} \{} \;
	find -name \*~ -exec ${RM} \{} \;


#%.o:%.cpp
.cc.o:
	${CC} -c $< ${CFLAGS} -o $@

