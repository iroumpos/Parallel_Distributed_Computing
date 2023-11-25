CC = gcc
EXEC = inner_p matrix_mul
FLAGS = -Wall

all: $(EXEC)

innep_p: inner_p.c
	$(CC) $(FLAGS) -o $@ inner_p.c

matrix_mul: matrix_mul.c
	$(CC) $(FLAGS) -o $@ matrix_mul.c

clean:
	rm -f *.o $(EXEC)
