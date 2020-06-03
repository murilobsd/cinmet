# Copyright (c) 2020 Murilo Ijanc' <mbsd@m0x.ru>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

PREFIX?=	/usr/local

CC?=		cc
CFLAGS:=	-std=c89 -O2 -I. -I/usr/local/include #-Wall -Wunused \
		#-W -Werror
LDFLAGS:=	-L. -L/usr/local/lib
NAME:=		inmet
MAJOR:=		0
MINOR:=		3
VERSION:=	$(MAJOR).$(MINOR)
LIB:=		-lcurl
SLIB:=		lib$(NAME).a
DLIB:=		lib$(NAME).so
DLIBV:=		lib$(NAME).$(MAJOR).$(VERSION).so

# uncomment to enable debugging
#CLFAGS+=	-g -DDEBUG=1

SRC=		b64.c \
		request.c \
		utils.c \
		station.c

OBJ=		${SRC:.c=.o}

BIN=		inmet

$(OBJ): inmet.h

$(SLIB): $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

$(DLIB): $(DLIBV)
	ln -s $(DLIBV) $(DLIB)

$(DLIBV): $(OBJ)
	$(CC) $(CFLAGS) -shared -fPIC $(OBJ) -o $@

lib: $(SLIB) $(DLIB)

$(BIN): $(SLIB)
	$(CC) -o $@ main.c $(CFLAGS) $(LDFLAGS) -l$(NAME) $(LIB)

check: inmet
	valgrind --leak-check=yes ./$(BIN)
clean:
	rm -f *.o *.core *.out *.a *.so $(BIN)

re: clean lib

.PHONY: lib clean check re inmet
