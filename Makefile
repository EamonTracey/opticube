CC=gcc
CFLAGS=-O3 -Wall -Werror

opticube:
	$(CC) $(CFLAGS) \
		src/algorithm.c \
		src/main.c \
		src/cube.c \
		src/queue.c \
		src/solve.c \
		src/state.c \
		src/table.c \
		-o opticube

.PHONY: clean
clean:
	rm -fr depths
	rm -f opticube
