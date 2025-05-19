.PHONY: all clean
CC = gcc
CCFLAGS = -g -Wall -Werror -Wextra -pedantic
NAME = strace_0
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=o)

#default
all: $(NAME)


#strace_0
$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) $< -o $@
	rm -f $(OBJ)


#clean
clean:
	rm -f $(OBJ) $(NAME)
