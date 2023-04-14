CC := gcc
CFLAGS := -std=gnu99 -Wextra -Wall \
		  -O3 -g -Iinclude/

LINK := -lraylib -lm


all: ladder
.PHONY: all

override CFILES := $(shell find ./src -type f -name '*.c')
override OFILES := $(shell find ./obj -type f -name '*.o')


ladder:
	@mkdir -p bin/ obj/
	$(foreach file, $(CFILES), $(CC) $(CFLAGS) -c $(file) -o obj/$(basename $(notdir $(file))).o;)

	gcc $(OFILES) -o bin/ladder $(LINK) -lgcc

clean:
	rm -rf obj/ bin/