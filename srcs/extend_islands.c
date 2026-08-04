#include "nurikabe_solver.h"

void	extend_island(int **grid, t_pos pos, int **cache_grid, t_dequeue *dequeue, t_island *island)
{
	t_pos	cur_pos;
	t_pos	next_pos;
	t_pos	last_pos;
	int		potential_extend_nb;

	if (cache_grid[pos.y][pos.x] != -1)
		return ;
	last_pos.x = -1;
	potential_extend_nb = 0;
	initialise_dequeue(dequeue);
	push_back(dequeue, pos);
	while (!is_empty(dequeue))
	{
		cur_pos = pop_front(dequeue);
		if (cache_grid[cur_pos.y][cur_pos.x] != -1)
			continue ;
		if ((grid[cur_pos.y][cur_pos.x] & grid[pos.y][pos.x]) == 0)
			continue ;
		if (grid[cur_pos.y][cur_pos.x] != grid[pos.y][pos.x])
		{
			potential_extend_nb++;
			last_pos = cur_pos;
			continue ;
		}
		cache_grid[cur_pos.y][cur_pos.x] = 0;
		if (cur_pos.y > 0)
		{
			next_pos = cur_pos;
			next_pos.y -= 1;
			push_back(dequeue, next_pos);
		}
		if (cur_pos.x > 0)
		{
			next_pos = cur_pos;
			next_pos.x -= 1;
			push_back(dequeue, next_pos);
		}
		if (grid[cur_pos.y + 1])
		{
			next_pos = cur_pos;
			next_pos.y += 1;
			push_back(dequeue, next_pos);
		}
		if (grid[cur_pos.y][cur_pos.x + 1] != -1)
		{
			next_pos = cur_pos;
			next_pos.x += 1;
			push_back(dequeue, next_pos);
		}
	}
	if (potential_extend_nb == 1)
	{
		grid[last_pos.y][last_pos.x] = grid[pos.y][pos.x];
		island->current_size += 1;
	}
}

void	extend_islands(int **grid, int **cache_grid, t_dequeue *dequeue, t_island *islands)
{
	t_pos	pos;
	int		island_id;

	init_cache_grid(grid, cache_grid);
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x] != -1)
		{
			if (count_bits(grid[pos.y][pos.x]) != 1)
			{
				pos.x++;
				continue ;
			}
			island_id = get_trailing_zeros(grid[pos.y][pos.x]);
			if (islands[island_id].current_size != islands[island_id].target_size)
				extend_island(grid, pos, cache_grid, dequeue, &islands[island_id]);
			pos.x++;
		}
		pos.y++;
	}
}
