#include "thread_pool.h"

static void *pool_thread_server(void *arg);


void thread_pool_init(thread_pool_t *pool, int threads_limit) 
{
	pool->threads_limit = threads_limit;
	pool->queue_head = NULL;
	pool->task_wait_queue = 0;
	pool->destroy_flag = 0;
	pool->thread_id = (pthread_t *) calloc(threads_limit, sizeof(pthread_t));

	int i = 0;

	pthread_mutex_init(&(pool->queue_lock), NULL);
	pthread_cond_init(&(pool->queue_ready), NULL);

	for (i = 0; i < threads_limit; i++) {
		pthread_create(&(pool->thread_id[i]), NULL, pool_thread_server, pool);
	}

	return;
}


int thread_pool_destroy(thread_pool_t *pool) 
{
	thread_pool_task *head = NULL;
	int i;

	pthread_mutex_lock(&(pool->queue_lock));
	if (pool->destroy_flag)
		return -1;

	pool->destroy_flag = 1;
	pthread_mutex_unlock(&pool->queue_lock);
	pthread_cond_broadcast(&(pool->queue_ready));

	for (i = 0; i < pool->threads_limit; i++)
		pthread_join(pool->thread_id[i], NULL);
	
	free(pool->thread_id);

	pthread_mutex_lock(&(pool->queue_lock));
	while(pool->queue_head != NULL) {
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free(head);
	}

	pthread_mutex_unlock(&(pool->queue_lock));
	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->queue_ready));

	return 0;
}


static void enqueue_task(thread_pool_t *pool, thread_pool_task_fn process, void *arg) 
{
	thread_pool_task *task = NULL;
	thread_pool_task *member = NULL;

	pthread_mutex_lock(&(pool->queue_lock));

	if (pool->task_wait_queue >= pool->threads_limit) {
		printf("task_in_queue > threads_limit !\n");
		pthread_mutex_unlock(&(pool->queue_lock));
		return;
	}

	task = (thread_pool_task *) calloc(1, sizeof(thread_pool_task));
	assert(task != NULL);
	task->process = process;
	task->arg = arg;
	task->next = NULL;
	pool->task_wait_queue++;
	member = pool->queue_head;

	if (member != NULL) {
		while(member->next != NULL)
			member = member->next;
		member->next = task;
	} else {
		pool->queue_head = task;
	}

	printf("\ttasks %d\n", pool->task_wait_queue);
	
	pthread_cond_signal(&(pool->queue_ready));
	pthread_mutex_unlock(&(pool->queue_lock));
}


static thread_pool_task *dequeue_task(thread_pool_t *pool)
{
	thread_pool_task *task = NULL;

	pthread_mutex_lock(&(pool->queue_lock));
	if (pool->destroy_flag) {
		pthread_mutex_unlock(&(pool->queue_lock));
		printf("thread 0x%lx will be destroyed\n", pthread_self());
		pthread_exit(NULL);
	}

	if (pool->task_wait_queue == 0) {
		while((pool->task_wait_queue == 0) && (!pool->destroy_flag)) {
			printf("thread 0x%lx is waitting\n", pthread_self());
			pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
		}
	} else {
		pool->task_wait_queue--;
		task = pool->queue_head;
		pool->queue_head = task->next;
		printf("thread 0x%lx received a task\n", pthread_self());
	}

	pthread_mutex_unlock(&(pool->queue_lock));
	return task;
}

int thread_pool_add_task(thread_pool_t *pool, thread_pool_task_fn process, void *arg)
{
	enqueue_task(pool, process, arg);
	return 0;
}

static void *pool_thread_server(void *arg) 
{
	thread_pool_t *pool = NULL;

	pool = (thread_pool_t *)arg;
	while(1) {
		thread_pool_task *task = NULL;
		task = dequeue_task(pool);
		if (task != NULL) {
			printf("thread 0x%lx is busy\n", pthread_self());
			task->process(task->arg);
			free(task);
			task = NULL;
		}
	}
	pthread_exit(NULL);
	return NULL;
}
