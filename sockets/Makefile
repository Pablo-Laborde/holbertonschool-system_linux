.PHONY: all clean
CC = gcc
CCFLAGS = -Wall -Werror -Wextra -pedantic -g



todo_api_0:
	$(CC) $(CCFLAGS) 4-server.c side_f40.c side_f41.c -o todo_api_0

todo_api_1:
	$(CC) $(CCFLAGS) 5-server.c side_f40.c side_f50.c -o todo_api_1

todo_api_2:
	$(CC) $(CCFLAGS) 6-server.c side_f40.c side_f50.c side_f60.c -o todo_api_2

todo_api_3:
	$(CC) $(CCFLAGS) 7-server.c side_f40.c side_f50.c side_f60.c side_f70.c -o todo_api_3


#clean
clean:
	rm todo_api_0 todo_api_1 todo_api_2 todo_api_3
