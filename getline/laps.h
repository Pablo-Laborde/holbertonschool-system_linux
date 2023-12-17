#ifndef LAPS_FILE_H
#define LAPS_FILE_H

/*	Libraries	*/
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

typedef struct car_s* cars;

/*	Functions	*/
void race_state(int *id, size_t size);

/*	TAD		*/
cars create_car(int id);
cars ins_car(cars car, cars cl);
int check_car(int id, cars cl);
void del_car_list(cars cl);

#endif
