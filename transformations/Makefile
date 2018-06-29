CC=g++
CFLAGS=-Werror -I.
DEPS = bmp.h exceptions.h matrix.h obj.h transform.h
OBJ = exceptions.o main.o matrix.o obj.o transform.o

all: transformations

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

transformations: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

PHONY: clean

clean:
	rm -rf *.o
