#include "laps.h"


/*  Structures Definitions  */
struct car_s {
	int no;
	int laps;
	struct car_s* next;
};


int main(void)
{
	int i[] = {1, 2, 3};
	race_state(i, 3);
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
	cars car = NULL;
	static cars race = NULL;

	if (size > 0)
	{
		for (i = 0; i < size; i++)
		{
			if (check_car(id[i], race))
			{
				printf("%i\n", id[0]);
			}
			else
			{
				car = create_car(id[i]);
				race = ins_car(car, race);
			}
		}
	}
	else
	{
		del_car_list(race);
		race = NULL;
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
	if (car)
	{
		car->no = id;
		car->laps = 0;
		car->next = NULL;
	}
	return (car);
}


/**
* ins_car- function
* @car: cars
* @cl: cars
* Return: cars
*/
cars ins_car(cars car, cars cl)
{
	if (car)
	{
		if (cl)
		{
			if (car->no < cl->no)
			{
				car->next = cl;
				return (car);
			}
			else
				cl->next = ins_car(car, cl->next);
		}
		else
			return (car);
	}
	return (cl);
}


/**
* check_car- function
* @id: int
* @cl: cars
* Return: int
*/
int check_car(int id, cars cl)
{
	int		flag = 0;

	if (cl)
	{
		while (!flag && cl)
		{
			if (id == cl->no)
				flag = 1;
			cl = cl->next;
		}
	}
	return (flag);
}

/**
* del_car_list- function
* @car_list: cars
*/
void del_car_list(cars cl)
{
	if (cl)
	{
		del_car_list(cl->next);
		free(cl);
	}
}
