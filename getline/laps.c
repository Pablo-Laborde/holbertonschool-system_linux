#include "laps.h"


/*  Structures Definitions  */
struct car_s {
	int no;
	int laps;
	struct car_s* next;
};
typedef struct car_s* cars;


int main(void)
{
	int i[] = {1, 2, 3};
	race_state(i, 3);
	return (0);
}
/**
* race_state- function
* @id: int*
* @ize: size_t
* Return: void
*/
void race_state(int *id, size_t size)
{
	size_t i = 0;
	static cars race = NULL;

	for (i = 0; i < size; i++)
	{
	}
}


/**
* create_car- function
* @id: int
* Return: cars
*/
cars create_car(int id)
{
	cars	car = NULL;

	car = malloc(sizeof(struct car_s));
	return (NULL);
}


/**
* check_car- function
* @car: cars
* @car_list: cars*
* Return: int
*/
int check_car(cars car, cars* car_list)
{
	int		flag = 0;
	cars	cl = NULL;

	if ((car_list) && (*car_list) && (car))
	{
		cl = *car_list;
		while (!flag && cl)
		{
			if (car->no == cl->no)
				flag = 1;
			cl = cl->next;
		}
	}
	return (flag);
}