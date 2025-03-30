.PHONY: all clean
CC = gcc
CCFLAGS = -g -Wall -Werror -Wextra -pedantic
SRC = $(wildcard *.c)
NAME = hnm


all: hnm


hnm:
	$(CC) $(CCFLAGS) $(SRC) -o $(NAME)


clean:
	rm hnm
