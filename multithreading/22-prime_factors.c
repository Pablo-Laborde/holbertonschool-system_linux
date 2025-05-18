#include "multithreading.h"



/**
* create_task - func
* @entry: task_entrey_t
* @param: void *
* Return: task_t *
*/
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task = NULL;

	task = malloc(sizeof(task_t));
	memset(task, 0, sizeof(task_t));
	task->entry = entry;
	task->param = param;
	task->status = PENDING;
	task->result = NULL;
	return (task);
}


/**
* destroy_task - func
* @task: task_t
*/
void destroy_task(task_t *task)
{
	//pthread_mutex_destroy(&task->lock);
	list_destroy(task->result, free);
	free(task->result);
	free(task);
}


/**
* exec_tasks - func
* @tasks: list_t const *
* Return: void *
*/
void *exec_tasks(list_t const *tasks)
{
	node_t *node = NULL;
	task_t *task = NULL;
	size_t size = 0, i = 0;

	if (!tasks)
		return (NULL);
	node = tasks->head;
	size = tasks->size;
	while (node && (i < size))
	{
		task = node->content;
		if (task->status == PENDING)
		{
			task->status = STARTED;
			tprintf("[%d] Started\n", i);
			task->result = task->entry(task->param);
			tprintf("[%d] Success\n", i);
			task->status = SUCCESS;
		}
		i++;
		node = node->next;
	}
	return (NULL);
}
