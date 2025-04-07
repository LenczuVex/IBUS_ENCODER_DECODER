CC=gcc
BUILDDIR=build/

$(BUILDDIR)libibus.o: | build
	$(CC) -c ibus.c -o $(BUILDDIR)libibus.o

build:
	mkdir -p build 1>/dev/null
