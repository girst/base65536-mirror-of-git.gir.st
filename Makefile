# base65536
# (C) 2016 Tobias Girstmair, http://isticktoit.net/
# released under the GNU GPL v3. See LICENSE for details.

.PHONY: all clean test
CC=gcc
CFLAGS=-std=c99 -Werror -Wall -Wextra

all: base65536

base65536:
	$(CC) $(CFLAGS) base65536.c main.c -o base65536

gentree:
	$(CC) $(CFLAGS) generate_struct.c -o gentree

clean:
	rm -f base65536 gentree

test: clean all
	./base65536 test/everyByte|./base65536 -d|diff -s test/everyByte -
	./base65536 test/everyPairOfBytes|./base65536 -d|diff -s test/everyPairOfBytes -
	./base65536 test/lena_std.tif|./base65536 -d|diff -s test/lena_std.tif -

