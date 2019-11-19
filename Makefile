CC =gcc
INCLUDE = -I./tools

LIBS = ./tools/build/libtool.a

target = test

all:
	$(CC) test.c $(LIBS) -o $(target) $(INCLUDE)
clean:
	rm -rf $(target)
