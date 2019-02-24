VPATH = ../lib/:../dir_links/

CC=gcc
#CFLAGS=
IDIR=. ../lib/
LDIR=

empty :=
space := $(empty) $(empty)

CIDIR = $(if $(IDIR), $(addprefix -I, $(IDIR)), $(empty))
CLDIR = $(if $(LDIR), $(addprefix -L, $(LDIR)), $(empty))

BIN = t_unlink list_files testoffset nftw_dir_tree view_symlink

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

list_files : list_files.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

testoffset : testoffset.o
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

view_symlink : view_symlink.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

nftw_dir_tree : nftw_dir_tree.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

#src = $(wildcard *.c)
#srcname = $(notdir $(basename $(src)))

objsrc = $(addsuffix .c, $(BIN))
deps = $(addsuffix .d, $(BIN))
deps += $(DEPS)
.PHONY : test2
test2:
	@echo $(deps)

%.o : %.c
	$(CC) -c $< -o $@ $(CIDIR) $(CLDIR)

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
	$(CC) -MM $(CFLAGS) $(CIDIR) $< > $@.$$$$;\
	sed 's,\($*\)\.o[ :]*,\1.o $@:,g' <$@.$$$$ > $@;\
	rm -f $@.$$$$

.PHONY:clean
clean:
	rm *.o *.d $(BIN)
