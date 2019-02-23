VPATH = ../lib/:../dir_links/

CC=gcc
#CFLAGS=
IDIR=.
LDIR=

empty :=
space := $(empty) $(empty)

CIDIR = $(if $(IDIR), $(addprefix -I, $(IDIR)), $(empty))
CLDIR = $(if $(LDIR), $(addprefix -L, $(LDIR)), $(empty))

BIN = t_unlink

.PHONY:all

all:$(BIN)
#obj = $($(BIN):%:%.o)
LIBSRCS = $(wildcard ../lib/*.c)
OBJS = $(addsuffix .o,$(notdir $(basename $(LIBSRCS))))
DEPS = $(subst .o,.d, $(OBJS))
tt = $(DEPS)
tt += $(OBJS)
.PHONY : test
test:
	@echo $(tt)

t_unlink : t_unlink.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

#src = $(wildcard *.c)
#srcname = $(notdir $(basename $(src)))

objsrc = $(addsuffix .c, $(BIN))
deps = $(addsuffix .d, $(BIN))
deps += $(DEPS)
.PHONY : test2
test2:
	@echo $(deps)

#$(obj): %.o : %.c
#	$(CC) -c $(CFLAGS) $< -o $@ -I$(IDIR) -L$(LDIR)

.PHONY:test.ggg
.PHONY:test.gogogo
test.ggg:
	@echo 'test...'

test.gogogo : %.gogogo : %.ggg


#source := $(wildcard *.c)

include $(deps)

$(deps): %.d : %.c
	@set -e;rm -f $@;\
	$(CC) -MM $(CFLAGS) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.0 $@:,g' <$@.$$$$ > $@;\
	rm -f $@.$$$$
#%.o : %.d

.PHONY:clean
clean:
	rm *.o *.d $(BIN)
