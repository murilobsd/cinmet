VERSION		 = 0.0.1
OBJS		 = inmet.o 

all: inmet

inmet: libinmet.a main.o
	$(CC) -o $@ main.o libinmet.a $(LDFLAGS)

libinmet.a: $(OBJS) $(COMPAT_OBJS)
	$(AR) rs $@ $(OBJS) $(COMPAT_OBJS)

install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(LIBDIR)
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	$(INSTALL_PROGRAM) inmet $(DESTDIR)$(BINDIR)
	$(INSTALL_LIB) libinmet.a $(DESTDIR)$(LIBDIR)
	$(INSTALL_DATA) inmet.h $(DESTDIR)$(INCLUDEDIR)

inmet.tar.gz.sha512: inmet.tar.gz
	sha512 inmet.tar.gz >$@

inmet.tar.gz:
	mkdir -p .dist/inmet-$(VERSION)/
	install -m 0644 *.c *.h Makefile LICENSE .dist/inmet-$(VERSION)
	( cd .dist/ && tar zcf ../$@ ./ )
	rm -rf .dist/

$(OBJS) main.o: inmet.h

clean:
	rm -f $(OBJS) main.o
	rm -f inmet.tar.gz.sha512 inmet.tar.gz
	rm -f inmet libinmet.a 
