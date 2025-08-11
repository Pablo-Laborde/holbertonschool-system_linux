#ifndef SOCKETS_H
#define SOCKETS_H


#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>


/* Functions */

/* side_f40.c */
int create_socket(void);
void bind_socket(int socket_fd, int port);
void listen_socket(int socket_fd, int port);
int accept_client(int socket_fd);
char *get_input(int client_fd);

/* side_f41.c */
void break_input(char *msg);

/* side_f50.c */
void print_ppq(char **arr);
char *spliter(char *str, char *delim, int n);
char **add_to_arr(char **arr, char *str, int size);
char **ppq(char *msg);
void free_arr(char **arr);

/* side_f60.c */
void print_ha(char **arr);
char **ha(char *msg);

/* side_f70 */
char *get_input_2(int client_fd);
char **split_body(char *rr);
char *retrieve_path(char *rr);
void print_bp(char *path, char **arr);


#endif
