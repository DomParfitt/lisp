CC=clang
CFLAGS=-I ./include

DEPS=src/**/*.c src/*.c

main: $(DEPS)
	$(CC) $(DEPS) -o bin/main $(CFLAGS)
