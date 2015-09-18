CC=gcc
CFLAGS=-I.
OBJ = obj/boolchain.o obj/boolchain_test.o  obj/shift.o obj/boolchainmock.o

obj/%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

boolchain: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f obj/*.o