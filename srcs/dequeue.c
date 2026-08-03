#include "nurikabe_solver.h"

void	initialise_dequeue(t_dequeue *dequeue)
{
	dequeue->front_i = 0;
	dequeue->back_i = 0;
}

int	is_empty(t_dequeue *dequeue)
{
	return (dequeue->front_i == dequeue->back_i);
}

int	is_full(t_dequeue *dequeue)
{
	return (dequeue->front_i == (dequeue->back_i + 1) % DEQUEUE_SIZE);
}

t_pos	pop_front(t_dequeue *dequeue)
{
	t_pos	pos;

	if (is_empty(dequeue))
		pos.x = -1;
	else
	{
		pos = dequeue->queue[dequeue->front_i];
		dequeue->front_i = (dequeue->front_i + 1) % DEQUEUE_SIZE;
	}
	return (pos);
}

t_pos	pop_back(t_dequeue *dequeue)
{
	t_pos	pos;

	if (is_empty(dequeue))
		pos.x = -1;
	else
	{
		dequeue->back_i = (dequeue->back_i - 1) % DEQUEUE_SIZE;
		pos = dequeue->queue[dequeue->back_i];
	}
	return (pos);
}

int	push_front(t_dequeue *dequeue, t_pos pos)
{
	if (is_full(dequeue))
		return (1);
	dequeue->front_i = (dequeue->front_i - 1) % DEQUEUE_SIZE;
	dequeue->queue[dequeue->front_i] = pos;
	return (0);
}

int	push_back(t_dequeue *dequeue, t_pos pos)
{
	if (is_full(dequeue))
		return (1);
	dequeue->queue[dequeue->back_i] = pos;
	dequeue->back_i = (dequeue->back_i + 1) % DEQUEUE_SIZE;
	return (0);
}
