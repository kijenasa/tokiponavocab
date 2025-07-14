CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Iinclude -g
LDFLAGS ?= -ljson-c

SRCS := ${wildcard src/*.c}
OBJS := ${SRCS:src/%.c=%.o}
TARGET=trainer
OUT_SUFFIX ?=

all: ${TARGET}${OUT_SUFFIX}

$(TARGET): ${OBJS}
	${CC} ${OBJS} -o $@ ${LDFLAGS}

%.o: src/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	rm -f ${OBJS} ${TARGET}

.PHONY: all clean
