#include "nurikabe_solver.h"

void	empty_cache_grid(const unsigned long long ***grid, unsigned long long ***cache_grid, int bitset_size)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			copy_bitset(cache_grid[y][x], EMPTY_BITSET, bitset_size);
			x++;
		}
		y++;
	}
}

void	init_cache_grid(unsigned long long ***grid, unsigned long long ***cache_grid, int bitset_size)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			copy_bitset(cache_grid[y][x], UNINITIALISED_BITSET, bitset_size);
			x++;
		}
		y++;
	}
}

void	fill_island(unsigned long long ***grid, t_island island, unsigned long long ***cache_grid, int bitset_size)
{
	int					x;
	int					y;
	unsigned long long	island_bitmap[MAX_BITSET_SIZE];

	copy_bitset(island_bitmap, grid[island.pos.y][island.pos.x], bitset_size);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (cmp_bitsets(cache_grid[y][x], UNINITIALISED_BITSET, bitset_size) != 0)
				copy_bitset(grid[y][x], island_bitmap, bitset_size);
			x++;
		}
		y++;
	}
}

void	use_bfs_to_limit_island(unsigned long long ***grid, t_island *island, unsigned long long ***cache_grid, t_dequeue *dequeue, int bitset_size)
{
	int	x;
	int	y;
	int	island_square_count;
	int	island_size;
	unsigned long long	island_bitmap[MAX_BITSET_SIZE];

	copy_bitset(island_bitmap, grid[island->pos.y][island->pos.x], bitset_size);
	bfs(grid, *island, cache_grid, dequeue, bitset_size);
	island_square_count = 0;
	island_size = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (cmp_bitsets(cache_grid[y][x], UNINITIALISED_BITSET, bitset_size) == 0
					&& grid[y][x][island->id / 64] & (1ULL << (island->id % 64)))
				grid[y][x][island->id / 64] ^= 1ULL << (island->id % 64);
			else
				island_square_count++;
			if (cmp_bitsets(grid[y][x], island_bitmap, bitset_size) == 0)
				island_size++;
			x++;
		}
		y++;
	}
	island->current_size = island_size;
	if (island_square_count == island->target_size)
	{
		island->current_size = island->target_size;
		fill_island(grid, *island, cache_grid, bitset_size);
	}
}

void	use_bfs_to_limit_islands(unsigned long long ***grid, t_island *islands, unsigned long long ***cache_grid, t_dequeue *dequeue)
{
	int	i;
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	i = 1;
	while (islands[i].id != -1)
	{
		//printf("test, grid\n");
		//print_grid(grid, islands);
		//printf("cache_grid\n");
		//print_grid(cache_grid, islands);
		use_bfs_to_limit_island(grid, &islands[i], cache_grid, dequeue, bitset_size);
		//printf("grid\n");
		//print_grid(grid, islands);
		//printf("cache_grid\n");
		//print_grid(cache_grid, islands);
		//printf("end test\n\n");
		i++;
	}
}

void	bfs(unsigned long long ***grid, t_island island, unsigned long long ***cache_grid, t_dequeue *dequeue, int bitset_size)
{
	t_pos	cur_pos;
	t_pos	next_pos;
	int		max_cost;
	unsigned long long	island_bitmap[MAX_BITSET_SIZE];

	initialise_dequeue(dequeue);
	init_cache_grid(grid, cache_grid, bitset_size);
	island.pos.cost = 0;
	max_cost = island.target_size - island.current_size;
	copy_bitset(island_bitmap, grid[island.pos.y][island.pos.x], bitset_size);
	push_back(dequeue, island.pos);
	while (!is_empty(dequeue))
	{
		cur_pos = pop_front(dequeue);
		if (cur_pos.cost > max_cost
				|| (cache_grid[cur_pos.y][cur_pos.x][0] <= (unsigned long long)cur_pos.cost && cache_grid[cur_pos.y][cur_pos.x][0] != ULLONG_MAX)
				|| (grid[cur_pos.y][cur_pos.x][island.id / 64] & (1ULL << (island.id % 64))) == 0)
			continue ;
		cache_grid[cur_pos.y][cur_pos.x][0] = cur_pos.cost;
		if (cur_pos.y > 0)
		{
			next_pos = cur_pos;
			next_pos.y -= 1;
			if (cmp_bitsets(grid[next_pos.y][next_pos.x], island_bitmap, bitset_size) != 0)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
		if (cur_pos.x > 0)
		{
			next_pos = cur_pos;
			next_pos.x -= 1;
			if (cmp_bitsets(grid[next_pos.y][next_pos.x], island_bitmap, bitset_size) != 0)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
		if (grid[cur_pos.y + 1])
		{
			next_pos = cur_pos;
			next_pos.y += 1;
			if (cmp_bitsets(grid[next_pos.y][next_pos.x], island_bitmap, bitset_size) != 0)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
		if (grid[cur_pos.y][cur_pos.x + 1])
		{
			next_pos = cur_pos;
			next_pos.x += 1;
			if (cmp_bitsets(grid[next_pos.y][next_pos.x], island_bitmap, bitset_size) != 0)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
	}
}
