prefix = /usr

CC=gcc

VERSION=1.7.0
CTOR_DEST=ctor
BINDIR=${prefix}/bin

OBJS=ctor.o


all:	ctor

tree:	$(OBJS)
	$(CC) $(LDFLAGS) -o $(CTOR_DEST) $(OBJS)

$(OBJS): %.o:	%.c ctor.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	if [ -x $(CTOR_DEST) ]; then rm $(CTOR_DEST); fi
	if [ -f ctor.o ]; then rm *.o; fi
	rm -f *~

install: ctor
	install -d $(BINDIR)
	
	if [ -e $(CTOR_DEST) ]; then \
		install $(CTOR_DEST) $(BINDIR)/$(CTOR_DEST); \
	fi
	
	