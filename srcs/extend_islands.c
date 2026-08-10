#include "nurikabe_solver.h"

int	count_water(unsigned long long ***grid, int bitset_size)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (cmp_bitsets(grid[y][x], WATER, bitset_size) == 0)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	extend_island(unsigned long long ***grid, t_pos pos, unsigned long long ***cache_grid, t_dequeue *dequeue, t_island *island, int bitset_size)
{
	t_pos	cur_pos;
	t_pos	next_pos;
	t_pos	last_pos;
	int		potential_extend_nb;

	if (cmp_bitsets(cache_grid[pos.y][pos.x], UNINITIALISED_BITSET, bitset_size) != 0)
		return ;
	last_pos.x = -1;
	last_pos.y = -1;
	potential_extend_nb = 0;
	initialise_dequeue(dequeue);
	push_back(dequeue, pos);
	while (!is_empty(dequeue))
	{
		cur_pos = pop_front(dequeue);
		if (cmp_bitsets(cache_grid[cur_pos.y][cur_pos.x], UNINITIALISED_BITSET, bitset_size) != 0)
			continue ;
		copy_bitset(cache_grid[cur_pos.y][cur_pos.x], grid[cur_pos.y][cur_pos.x], bitset_size);
		bitset_and(cache_grid[cur_pos.y][cur_pos.x], grid[pos.y][pos.x], bitset_size);
		if (cmp_bitsets(cache_grid[cur_pos.y][cur_pos.x], EMPTY_BITSET, bitset_size) == 0)
		{
			copy_bitset(cache_grid[cur_pos.y][cur_pos.x], UNINITIALISED_BITSET, bitset_size);
			continue ;
		}
		if (cmp_bitsets(grid[cur_pos.y][cur_pos.x], grid[pos.y][pos.x], bitset_size) != 0)
		{
			copy_bitset(cache_grid[cur_pos.y][cur_pos.x], UNINITIALISED_BITSET, bitset_size);
			if (last_pos.x != cur_pos.x || last_pos.y != cur_pos.y)
				potential_extend_nb++;
			last_pos = cur_pos;
			continue ;
		}
		copy_bitset(cache_grid[cur_pos.y][cur_pos.x], EMPTY_BITSET, bitset_size);
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
		if (grid[cur_pos.y][cur_pos.x + 1])
		{
			next_pos = cur_pos;
			next_pos.x += 1;
			push_back(dequeue, next_pos);
		}
	}
	if (potential_extend_nb == 1)
	{
		copy_bitset(grid[last_pos.y][last_pos.x], grid[pos.y][pos.x], bitset_size);
		island->current_size += 1;
		// reninitialise the cache_grid to avoid bugs
		init_cache_grid(grid, cache_grid, bitset_size);
	}
}

void	extend_islands(unsigned long long ***grid, unsigned long long ***cache_grid, t_dequeue *dequeue, t_island *islands)
{
	t_pos	pos;
	int		island_id;
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	init_cache_grid(grid, cache_grid, bitset_size);
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x])
		{
			if (count_bitset_bits(grid[pos.y][pos.x], bitset_size) != 1)
			{
				pos.x++;
				continue ;
			}
			island_id = get_bitset_trailing_zeros(grid[pos.y][pos.x], bitset_size);
			if (islands[island_id].current_size != islands[island_id].target_size)
				extend_island(grid, pos, cache_grid, dequeue, &islands[island_id], bitset_size);
			pos.x++;
		}
		pos.y++;
	}
}
