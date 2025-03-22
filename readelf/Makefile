.PHONY: all clean
CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic
EX0_FNAMES = readelf.c aux_func_zero.c aux_func_one.c aux_func_two.c aux_func_three.c


#default
all: 0-hreadelf


#exercise 0
0-hreadelf:
	$(CC) $(CCFLAGS) $(EX0_FNAMES) -o 0-hreadelf


clean:
	rm 0-hreadelf
