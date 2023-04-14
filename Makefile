CC := gcc
CFLAGS := -std=gnu99 -Wextra -Wall \
		  -O3 -g -Iinclude/

LINK := -lraylib -lm


all: ladder
.PHONY: all


ladder:
	@mkdir -p bin/
	$(CC) $(LINK) src/ladder.c $(CFLAGS) -o bin/ladder

clean:
	rm -rf obj/ bin/