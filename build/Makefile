VPATH = ../lib/:../dir_links/:../inotify/:../signals/:../timers/:../procexec/:../threads/

CC=gcc
#CFLAGS=
IDIR=. ../lib/
LDIR=

empty :=
space := $(empty) $(empty)

CIDIR = $(if $(IDIR), $(addprefix -I, $(IDIR)), $(empty))
CLDIR = $(if $(LDIR), $(addprefix -L, $(LDIR)), $(empty))

BIN = t_unlink list_files testoffset nftw_dir_tree view_symlink\
	  t_dirbasename demo_inotify watcher ouch intquit t_kill\
	  sig_sender sig_receiver noreentrant sigmask_longjmp\
	  t_sigaltstack t_sigqueue catch_rtsigs t_sigsuspend\
	  t_sigwaitinfo signalfd_sigval real_timer timed_read\
	  t_nanosleep ptmr_sigev_signal ptmr_sigev_thread\
	  demo_timerfd t_fork fork_file_sharing fork_whos_on_first\
	  fork_sig_sync exit_handlers multi_wait child_status\
	  make_zombie multi_SIGCHLD test_three make_zombie_v2\
	  envargs t_execve t_system my_execlp acct_on acct_view\
	  t_clone simple_thread thread_incr thread_incr_mutex\
	  thread_multijoin

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


thread_multijoin : thread_multijoin.o $(OBJS)
	$(CC) -pthread $^ -o $@ $(CIDIR) $(CLDIR)

thread_incr_mutex : thread_incr_mutex.o $(OBJS)
	$(CC) -pthread $^ -o $@ $(CIDIR) $(CLDIR)

thread_incr : thread_incr.o $(OBJS)
	$(CC) -pthread $^ -o $@ $(CIDIR) $(CLDIR)

simple_thread : simple_thread.o $(OBJS)
	$(CC) -pthread $^ -o $@ $(CIDIR) $(CLDIR)

t_clone : t_clone.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

acct_view : acct_view.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

acct_on : acct_on.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

my_execlp : my_execlp.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

t_system : t_system.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

envargs : envargs.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

t_execve : t_execve.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

make_zombie_v2 : make_zombie_v2.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

test_three : test_three.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

multi_SIGCHLD : multi_SIGCHLD.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

make_zombie : make_zombie.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

child_status : child_status.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

multi_wait : multi_wait.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

exit_handlers : exit_handlers.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

fork_sig_sync : fork_sig_sync.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

fork_whos_on_first : fork_whos_on_first.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

fork_file_sharing :fork_file_sharing.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

t_fork : t_fork.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

demo_timerfd : demo_timerfd.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) -lrt

ptmr_sigev_thread : ptmr_sigev_thread.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) -lrt

ptmr_sigev_signal : ptmr_sigev_signal.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) -lrt

t_nanosleep : t_nanosleep.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

timed_read : timed_read.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

real_timer : real_timer.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

signalfd_sigval : signalfd_sigval.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

t_sigwaitinfo : t_sigwaitinfo.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

t_sigsuspend : t_sigsuspend.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

t_sigqueue : t_sigqueue.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

catch_rtsigs : catch_rtsigs.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

t_sigaltstack : t_sigaltstack.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) 

sigmask_longjmp : sigmask_longjmp.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) -DUSE_SIGSETJMP 

noreentrant : noreentrant.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR) -lcrypt

sig_receiver : sig_receiver.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

t_kill : t_kill.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

sig_sender: sig_sender.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

intquit : intquit.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

ouch : ouch.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

watcher : watcher.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)	

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

t_dirbasename : t_dirbasename.o $(OBJS)
	$(CC) $^ -o $@ $(CIDIR) $(CLDIR)

demo_inotify: demo_inotify.o $(OBJS)
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
