// Copyright (c) 2022 by benggee
//
// file		: thread_pool.h
// since	: 2022-07-30
// desc		: 

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include "hh.h"

// callback function
typedef void *(*thread_pool_task_fn)(void *arg);

// task resource
typedef struct _task {
	thread_pool_task_fn process;
	void *arg;
	struct _task *next;
} thread_pool_task;

// thread poll 
typedef struct {
	pthread_t *thread_id;
	int threads_limit;
	int destroy_flag;		// is destroy, 0 destroy 1 do not destroy
	thread_pool_task *queue_head;
	int task_wait_queue;
	pthread_mutex_t queue_lock;
	pthread_cond_t  queue_ready;
} thread_pool_t;


// author	: benggee
// date		: 2022-07-30
// purpose	: Init thread pool
void thread_pool_init(thread_pool_t *pool, int ehreads_limit);

// author	: benggee
// date		: 2022-07-30
// purpose	: Thread pool destrory
int thread_pool_destroy(thread_pool_t *pool);

// author	: benggee
// date		: 2022-07-30
// purpose	: Add task to thread pool
int thread_pool_add_task(thread_pool_t *pool, thread_pool_task_fn process, void *arg);


#endif
