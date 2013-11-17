
INSTALLDIR=/usr/lib/lua/5.1
CFLAGS=-Wall -shared -fPIC
INCDIR=-I/usr/include/lua5.1 -I/usr/local/include/sodium
LIBS=-llua5.1 -lsodium
LIBFILE=sodium.so

all:
	gcc $(CFLAGS) $(INCDIR) $(LIBS) -o $(LIBFILE) sodium.c
	@echo Type \"make install\" to install $(LIBFILE) in $(INSTALLDIR)

install:
	install $(LIBFILE) $(INSTALLDIR)

uninstall:
	rm -f $(INSTALLDIR)/$(LIBFILE)

clean:
	@echo Cleaning...
	@rm -f $(LIBFILE)
