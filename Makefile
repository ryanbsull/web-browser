CC = gcc
CFLAGS = -lm -g
SRC_FILES := $(wildcard src/*.c)
OUTPUT_FILES := $(patsubst src/%.c,build/%.o,$(SRC_FILES))

all: w-browse

w-browse: $(OUTPUT_FILES) browser.c
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c
	@if [ ! -d "build" ]; then mkdir build; fi
	$(CC) -g -c $^ -o $@ 

clean:
	rm -rf build/ w-browse*

