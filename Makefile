CXXFLAGS  += -W
CXXFLAGS  += -O3
CXXFLAGS  += -std=c++0x
CXXFLAGS  += `pkg-config --cflags taglib`
LIBS += `pkg-config --libs taglib`
LDFLAGS += `pkg-config --libs taglib`

all:
	g++ $(LIBS) $(CXXFLAGS) libretta_utils.cpp libretta_string_utils.cpp pairfile.cpp main.cpp -o mtag ${LDFLAGS}

prefix ?= /usr/local
MANDIR ?= ${prefix}/share/man

install: mtag
	install -m 0755 mtag $(prefix)/bin
	install -m 0644 -D man/man1/mtag.1.gz ${DESTDIR}${MANDIR}/man1/mtag.1.gz
	install -m 0644 -D man/ru/man1/mtag.1.gz ${DESTDIR}${MANDIR}/ru/man1/mtag.1.gz
	install -m 0644 -D man/de/man1/mtag.1.gz ${DESTDIR}${MANDIR}/de/man1/mtag.1.gz

install-man:
	install -m 0644 -D man/man1/mtag.1.gz ${DESTDIR}${MANDIR}/man1
	install -m 0644 -D man/ru/man1/mtag.1.gz ${DESTDIR}${MANDIR}/ru/man1
	install -m 0644 -D man/de/man1/mtag.1.gz ${DESTDIR}${MANDIR}/de/man1

uninstall: mtag
	rm -f $(prefix)/bin/mtag
	rm -f ${DESTDIR}${MANDIR}/man1/mtag.1.gz
	rm -f ${DESTDIR}${MANDIR}/ru/man1/mtag.1.gz	
	rm -f ${DESTDIR}${MANDIR}/de/man1/mtag.1.gz	
