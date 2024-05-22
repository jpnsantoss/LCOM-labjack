#ifndef _LCOM_LIST_H_
#define _LCOM_LIST_H_

#include <lcom/lcf.h>

typedef struct queue_s {
	void 	**content;
	size_t	base_size;
	size_t	curr_size;
	size_t	front_pos;
	size_t	end_pos;
} queue_t;

queue_t	*queue_create(size_t size);
int			queue_push(queue_t *queue, void *content);
void		*queue_pop(queue_t *queue);
void		*queue_at(queue_t *queue, size_t pos);
void 		**queue_at_ref(queue_t *queue, size_t pos);
size_t	queue_size(queue_t *queue);
int			queue_full(queue_t *queue);
int			queue_empty(queue_t *queue);
void		queue_destroy(queue_t **queue, void (*f)(void *));
void		queue_shuffle(queue_t *queue);

#endif
