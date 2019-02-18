CFLAGS = \
	-I . \

DEST = /usr/include/wfsm

CFLAGS=-g -I . -I../.. -Wall -Wextra
CLASSES = $(wildcard *_class.h)
SRCS = $(patsubst %_class.h,%.c,$(CLASSES))
HEADERS = $(patsubst %.c,%.h,$(SRCS))

all: $(CLASSES) $(SRCS) $(HEADERS)
	cc $(CFLAGS) -o test $(SRCS) test.c

clean:
	rm -f *~ $(PROGS) test

.PHONY: clean run
