#include "../thread_pool.h"

void *task_test(void *arg) 
{
	printf("\t\tworking on task %d\n", (int *)arg);
	sleep(1);
	return NULL;
}

void thread_pool_demo(void) 
{
	thread_pool_t pool;
	int i = 0;

	thread_pool_init(&pool, 2);
	sleep(1);

	for (i = 0; i < 5; i++) {
		sleep(1);
		thread_pool_add_task(&pool, task_test, (void *)&i);
	}

	sleep(4);

	thread_pool_destroy(&pool);
}


int main(int argc, char argv[]) 
{
	thread_pool_demo();

	return 0;
}
