#ifndef _LCOM_LIST_H_
#define _LCOM_LIST_H_

#include <lcom/lcf.h>

typedef struct queue_s {
	void		**content;
	int			size;
} queue_t;

#endif