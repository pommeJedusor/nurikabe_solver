#include "nurikabe_solver.h"

int	are_there_empty_squares(int **grid)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (count_bits(grid[y][x]) == 0)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	are_islands_in_place(int **grid, t_island *islands)
{
	int		i;
	t_pos	pos;

	i = 1;
	while (islands[i].id != -1)
	{
		pos = islands[i].pos;
		if (grid[pos.y][pos.x] != 1 << islands[i].id)
			return (0);
		i++;
	}
	return (1);
}

t_pos	find_first_water(int **grid)
{
	t_pos	pos;

	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x] != -1)
		{
			if (grid[pos.y][pos.x] & WATER)
				return (pos);
			pos.x += 1;
		}
		pos.y += 1;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

int	isolated_island_part(int **grid, t_island *islands, int **cache_grid, t_dequeue *dequeue)
{
	t_pos	pos;
	int		i;
	int		island_bitmap;

	initialise_dequeue(dequeue);
	empty_cache_grid(grid, cache_grid);
	i = 0;
	while (islands[i].id != -1)
	{
		island_bitmap = 1 << i;
		if (i == 0)
			push_back(dequeue, find_first_water(grid));
		else
			push_back(dequeue, islands[i].pos);
		while (!is_empty(dequeue))
		{
			pos = pop_front(dequeue);
			if (pos.x < 0 || pos.y < 0 || grid[pos.y] == 0 || grid[pos.y][pos.x] == -1
					|| (grid[pos.y][pos.x] & island_bitmap) == 0
					|| cache_grid[pos.y][pos.x] & island_bitmap)
				continue ;
			cache_grid[pos.y][pos.x] |= island_bitmap;
			push_back(dequeue, (t_pos){ pos.x - 1, pos.y, -1 });
			push_back(dequeue, (t_pos){ pos.x + 1, pos.y, -1 });
			push_back(dequeue, (t_pos){ pos.x, pos.y - 1, -1 });
			push_back(dequeue, (t_pos){ pos.x, pos.y + 1, -1 });
		}
		i++;
	}
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x] != -1)
		{
			if (cache_grid[pos.y][pos.x] != grid[pos.y][pos.x])
				return (1);
			pos.x += 1;
		}
		pos.y += 1;
	}
	return (0);
}

int	is_valid(int **grid, t_island *islands, int **cache_grid, t_dequeue *dequeue)
{
	if (are_islands_in_place(grid, islands) == 0)
		return (0);
	if (are_there_empty_squares(grid))
		return (0);
	if (isolated_island_part(grid, islands, cache_grid, dequeue))
		return (0);
	//todo add water square check
	return (1);
}
