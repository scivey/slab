CC=gcc
CFLAGS=--std=c99
INC=-I./src
LINK=

OBJ=$(addprefix ./src/, \
		memory_slab.o \
		free_list.o \
		point.o \
	)

app: ./src/main.o $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $< $(OBJ) $(LINK)

./src/%.o:./src/%.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

test: ./tests/tests.cpp $(OBJ)
	g++ --std=c++11 -I./tests -I./src -o ./test_runner $< $(OBJ)

.PHONY: clean

clean:
	rm -f src/*.o
	rm -f tests/*.o
