prefix = /usr

CC=gcc

VERSION=1.7.0
TREE_DEST=ctor
BINDIR=${prefix}/bin
MAN=tree.1
MANDIR=${prefix}/man/man1
OBJS=ctor.o

# Uncomment options below for your particular OS:

# Linux defaults:
#CFLAGS=-ggdb -Wall -DLINUX -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#CFLAGS=-O4 -Wall  -DLINUX -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64
#LDFLAGS=-s

# Uncomment for FreeBSD:
#CFLAGS=-O2 -Wall -fomit-frame-pointer
#LDFLAGS=-s
#OBJS+=strverscmp.o

# Uncomment for Solaris:
#CC=cc
#CFLAGS=-xO0 -v
#LDFLAGS=
#OBJS+=strverscmp.o
#MANDIR=${prefix}/share/man/man1

# Uncomment for Cygwin:
#CFLAGS=-O2 -Wall -fomit-frame-pointer -DCYGWIN
#LDFLAGS=-s
#TREE_DEST=tree.exe
#OBJS+=strverscmp.o

# Uncomment for OS X:
CC=cc
CFLAGS=-O2 -Wall -fomit-frame-pointer -no-cpp-precomp
LDFLAGS=
MANDIR=/usr/share/man/man1


# Uncomment for HP/UX:
#CC=cc
#CFLAGS=-O2 -DAportable -Wall
#LDFLAGS=
#OBJS+=strverscmp.o

# Uncomment for OS/2:
#CFLAGS=-02 -Wall -fomit-frame-pointer -Zomf -Zsmall-conv
#LDFLAGS=-s -Zomf -Zsmall-conv
#OBJS+=strverscmp.o

# Uncomment for HP NonStop:
#prefix = /opt
#CC=c89
#CFLAGS=-Wextensions -WIEEE_float -g -Wnowarn=1506 -D_XOPEN_SOURCE_EXTENDED=1 \
#	 -Wallow_cplusplus_comments
#LDFLAGS=
#OBJS+=strverscmp.o


#------------------------------------------------------------

all:	ctor

tree:	$(OBJS)
	$(CC) $(LDFLAGS) -o $(TREE_DEST) $(OBJS)

$(OBJS): %.o:	%.c ctor.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	if [ -x $(TREE_DEST) ]; then rm $(TREE_DEST); fi
	if [ -f ctor.o ]; then rm *.o; fi
	rm -f *~

install: ctor
	install -d $(BINDIR)
	install -d $(MANDIR)
	if [ -e $(TREE_DEST) ]; then \
		install $(TREE_DEST) $(BINDIR)/$(TREE_DEST); \
	fi
	install doc/$(MAN) $(MANDIR)/$(MAN)

	