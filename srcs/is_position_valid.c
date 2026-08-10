#include "nurikabe_solver.h"

int	are_there_empty_squares(const unsigned long long ***grid, int bitset_size)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (count_bitset_bits(grid[y][x], bitset_size) == 0)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	are_islands_in_place(const unsigned long long ***grid, t_island *islands)
{
	int		i;
	t_pos	pos;
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	i = 1;
	while (islands[i].id != -1)
	{
		pos = islands[i].pos;
		if (count_bitset_bits(grid[pos.y][pos.x], bitset_size) != 1
				|| grid[pos.y][pos.x][islands[i].id / 64] != 1ULL << (islands[i].id % 64))
			return (0);
		i++;
	}
	return (1);
}

t_pos	find_first_water_only(const unsigned long long ***grid, int bitset_size)
{
	t_pos	pos;

	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x])
		{
			if (cmp_bitsets(grid[pos.y][pos.x], WATER, bitset_size) == 0)
				return (pos);
			pos.x += 1;
		}
		pos.y += 1;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

t_pos	find_first_water(const unsigned long long ***grid)
{
	t_pos	pos;

	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x])
		{
			if (grid[pos.y][pos.x][0] & 1)
				return (pos);
			pos.x += 1;
		}
		pos.y += 1;
	}
	pos.x = -1;
	pos.y = -1;
	return (pos);
}

int	isolated_island_part_and_max_size(const unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue)
{
	t_pos				pos;
	int					i;
	int					max_potential_size;
	int					bitset_size;
	unsigned long long	island_bitmap[MAX_BITSET_SIZE];

	bitset_size = get_bitset_size_from_islands(islands);
	initialise_dequeue(dequeue);
	empty_cache_grid(grid, cache_grid, bitset_size);
	i = 0;
	while (islands[i].id != -1)
	{
		max_potential_size = 0;
		copy_bitset(island_bitmap, EMPTY_BITSET, bitset_size);
		island_bitmap[i / 64] = 1ULL << (i % 64);
		if (i == 0)
			push_back(dequeue, find_first_water(grid));
		else
			push_back(dequeue, islands[i].pos);
		while (!is_empty(dequeue))
		{
			pos = pop_front(dequeue);
			if (pos.x < 0 || pos.y < 0 || grid[pos.y] == 0 || grid[pos.y][pos.x] == 0
					|| (grid[pos.y][pos.x][i / 64] & (1ULL << (i % 64))) == 0
					|| cache_grid[pos.y][pos.x][i / 64] & (1ULL << (i % 64)))
				continue ;
			max_potential_size++;
			bitset_or(cache_grid[pos.y][pos.x], island_bitmap, bitset_size);
			push_back(dequeue, (t_pos){ pos.x - 1, pos.y, -1 });
			push_back(dequeue, (t_pos){ pos.x + 1, pos.y, -1 });
			push_back(dequeue, (t_pos){ pos.x, pos.y - 1, -1 });
			push_back(dequeue, (t_pos){ pos.x, pos.y + 1, -1 });
		}
		if (max_potential_size < islands[i].target_size)
			return (1);
		i++;
	}
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x])
		{
			copy_bitset(island_bitmap, cache_grid[pos.y][pos.x], bitset_size);
			bitset_and(island_bitmap, grid[pos.y][pos.x], bitset_size);
			if (cmp_bitsets(island_bitmap, cache_grid[pos.y][pos.x], bitset_size) != 0)
				return (1);
			pos.x += 1;
		}
		pos.y += 1;
	}
	return (0);
}

int	is_water_square(const unsigned long long ***grid, int bitset_size)
{
	t_pos	pos;

	pos.y = 0;
	while (grid[pos.y + 1])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x + 1])
		{
			if (cmp_bitsets(grid[pos.y][pos.x], WATER, bitset_size) == 0
					&& cmp_bitsets(grid[pos.y][pos.x + 1], WATER, bitset_size) == 0
					&& cmp_bitsets(grid[pos.y + 1][pos.x], WATER, bitset_size) == 0
					&& cmp_bitsets(grid[pos.y + 1][pos.x + 1], WATER, bitset_size) == 0)
				return (1);
			pos.x += 1;
		}
		pos.y += 1;
	}
	return (0);
}

int	are_islands_touching(const unsigned long long ***grid, int bitset_size)
{
	t_pos	pos;
	pos.y = 0;
	while (grid[pos.y])
	{
		pos.x = 0;
		while (grid[pos.y][pos.x])
		{
			if (count_bitset_bits(grid[pos.y][pos.x], bitset_size) == 1
					&& cmp_bitsets(grid[pos.y][pos.x], WATER, bitset_size) != 0)
			{
				if (grid[pos.y + 1]
						&& count_bitset_bits(grid[pos.y + 1][pos.x], bitset_size) == 1
						&& cmp_bitsets(grid[pos.y][pos.x], grid[pos.y + 1][pos.x], bitset_size) != 0
						&& cmp_bitsets(grid[pos.y + 1][pos.x], WATER, bitset_size) != 0)
					return (1);
				if (grid[pos.y][pos.x + 1]
						&& count_bitset_bits(grid[pos.y][pos.x + 1], bitset_size) == 1
						&& cmp_bitsets(grid[pos.y][pos.x], grid[pos.y][pos.x + 1], bitset_size) != 0
						&& cmp_bitsets(grid[pos.y][pos.x + 1], WATER, bitset_size) != 0)
					return (1);
			}
			pos.x += 1;
		}
		pos.y += 1;
	}
	return (0);
}

int	is_valid(const unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue)
{
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	if (are_islands_in_place(grid, islands) == 0)
		return (0);
	if (are_there_empty_squares(grid, bitset_size))
		return (0);
	if (isolated_island_part_and_max_size(grid, islands, cache_grid, dequeue))
		return (0);
	if (is_water_square(grid, bitset_size))
		return (0);
	if (are_islands_touching(grid, bitset_size))
		return (0);
	return (1);
}
