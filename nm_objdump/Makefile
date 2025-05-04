.PHONY: all clean
CC = gcc
CCFLAGS = -g -Wall -Werror -Wextra -pedantic
NM_SRC = hnm.c dnm_32.c dnm_64.c
NM_NAME = hnm


all: hnm


hnm:
	$(CC) $(CCFLAGS) $(NM_SRC) -o $(NM_NAME)


clean:
	rm hnm
