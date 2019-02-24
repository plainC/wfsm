CFLAGS = \
	-I . \

DEST = /usr/include/wfsm

CFLAGS=-g -I . -I../.. -Wall -Wextra
CLASSES = $(wildcard *_class.h)
SRCS = $(patsubst %_class.h,%.c,$(CLASSES))
HEADERS = $(patsubst %.c,%.h,$(SRCS))

all: $(CLASSES) $(SRCS) $(HEADERS)
	cc $(CFLAGS) -o test $(SRCS) test.c

unit_test: $(CLASSES) $(SRCS) $(HEADERS)
	cc $(CFLAGS) -o unit_test $(SRCS) unit_test.c

clean:
	rm -f *~ $(PROGS) test unit_test .gdb_history

.PHONY: clean run
