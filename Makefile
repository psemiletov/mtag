CXXFLAGS  += -O3
CXXFLAGS  += -std=c++0x
CXXFLAGS  += `pkg-config --cflags taglib`
LIBS += `pkg-config --libs taglib`
LDFLAGS += `pkg-config --libs taglib`

all:
	g++ -ltag $(CXXFLAGS) libretta_utils.cpp libretta_string_utils.cpp libretta_pairfile.cpp main.cpp -o mtag

PREFIX ?= /usr/local
MANDIR ?= ${PREFIX}/share/man

install: mtag
	install -m 0755 mtag $(PREFIX)/bin
	install man/man1/mtag.1 ${DESTDIR}${MANDIR}/man1
	install man/ru/man1/mtag.1 ${DESTDIR}${MANDIR}/ru/man1

install-man:
	install -D man/man1/mtag.1 ${DESTDIR}${MANDIR}/man1
	install -D man/ru/man1/mtag.1 ${DESTDIR}${MANDIR}/ru/man1


uninstall: mtag
	rm -f $(PREFIX)/bin/mtag
	rm -f ${DESTDIR}${MANDIR}/man1/mtag.1
	rm -f ${DESTDIR}${MANDIR}/ru/man1/mtag.1	