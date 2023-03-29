# soap - simple xdg-open replacement with fallback

BACKUP = xdg-open.sh

# install location
PREFIX = /usr/local
XDG_BACKUP = ${PREFIX}/bin/xdg-open.sh

# compiler and linker
CC = cc
CFLAGS = -pedantic -Wall -Wextra -O2 ${INCS}\
		 -DFALLBACK=\"${XDG_BACKUP}\ \%s\"
LDFLAGS = -s

SRC = soap.c
OBJ = ${SRC:.c=.o}


all: soap

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h

config.h:
	cp config.def.h $@

soap: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f soap ${OBJ}

install: all
	install -Dm755 soap ${PREFIX}/bin
	@test ! -f ${XDG_BACKUP} || (echo error: backup exists!; return 1)
	mv ${PREFIX}/bin/xdg-open ${XDG_BACKUP}
	ln -sf ${PREFIX}/bin/soap ${PREFIX}/bin/xdg-open

uninstall:
	@test -f ${XDG_BACKUP} || (echo error: no backup found!; return 1)
	rm -f ${PREFIX}/bin/soap
	mv ${XDG_BACKUP} ${PREFIX}/bin/xdg-open
