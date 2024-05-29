#ifndef _LCOM_STACK_H_
#define _LCOM_STACK_H_

#include <lcom/lcf.h>

/** @defgroup data_structures Data Structures */

/** 
 * @defgroup stack_t Stack 
 * @ingroup data_structures
 * @{
 *
 * @brief Container which follows the LIFO (Last in, First out) principle.
*/

typedef struct {
	void 	**content;
	size_t	base_size;
	size_t	curr_size;
	size_t	end_pos;
} my_stack_t;

my_stack_t	*stack_create(size_t size);
int			stack_push(my_stack_t *stack, void *content);
void		*stack_pop(my_stack_t *stack);
size_t	stack_size(my_stack_t *stack);
int			stack_full(my_stack_t *stack);
int			stack_empty(my_stack_t *stack);
void		stack_destroy(my_stack_t **stack, void (*f)(void *));
void 		*stack_at(my_stack_t *stack, size_t pos);

/** @} */

#endif /* _LCOM_STACK_H_ */