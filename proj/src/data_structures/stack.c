#include "stack.h"

my_stack_t *stack_create(size_t size)
{
	my_stack_t	*stack;

	stack = malloc(sizeof(my_stack_t));
	if (stack == NULL) return NULL;

	stack->content = malloc(size * sizeof(void *));
	if (stack->content == NULL)
	{
		free(stack);
		return NULL;
	}

	stack->base_size = size;
	stack->curr_size = 0;
	stack->front_pos = 0;
	stack->end_pos = 0;

	return stack;
}

size_t stack_size(my_stack_t *stack)
{
	if (!stack) return 0;

	return stack->base_size;
}

int stack_full(my_stack_t *stack)
{
	if (!stack) return 0;

	return stack->base_size == stack->curr_size;
}

int stack_empty(my_stack_t *stack)
{
	if (!stack) return 0;

	return stack->curr_size == 0;
}

void stack_destroy(my_stack_t **stack, void (*f)(void *))
{
	if ((*stack)->front_pos < (*stack)->end_pos)
	{
		for (size_t i = (*stack)->front_pos; i <= (*stack)->end_pos; i++)
			free((*stack)->content[i]);
	}
	else if ((*stack)->curr_size != 0)
	{
		for (size_t i = 0; i <= (*stack)->end_pos; i++)
			free((*stack)->content[i]);
		
		for (size_t i = (*stack)->front_pos; i < (*stack)->base_size; i++)
			free((*stack)->content[i]);
	}
	free(*stack);
	*stack = NULL;
}

void *stack_pop(my_stack_t *stack)
{
	if (stack_empty(stack)) return NULL;

	void *result = stack->content[stack->end_pos];

	stack->curr_size -= 1;
	stack->front_pos = stack->front_pos == stack->base_size - 1 ? 0 : stack->front_pos + 1;
	stack->end_pos--;

	return result;
}

int stack_push(my_stack_t *stack, void *content)
{
	if (stack_full(stack) || content == NULL) return 1;

	stack->curr_size += 1;
	stack->end_pos++;
	stack->content[stack->end_pos] = content;
	return 0;
}
