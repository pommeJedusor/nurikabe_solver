#include "nurikabe_solver.h"

void	print_cache_grid(int **grid, int **cache_grid)
{
	int		x;
	int		y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (cache_grid[y][x] == -1)
				printf("o");
			else
				printf("%d", cache_grid[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	init_cache_grid(int **grid, int **cache_grid)
{
	int	x;
	int	y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			cache_grid[y][x] = -1;
			x++;
		}
		y++;
	}
}

void	fill_island(int **grid, t_island island, int **cache_grid)
{
	int	x;
	int	y;
	int	island_bitmap;

	island_bitmap = grid[island.pos.y][island.pos.x];
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (cache_grid[y][x] != -1)
				grid[y][x] = island_bitmap;
			x++;
		}
		y++;
	}
}

void	use_bfs_to_limit_island(int **grid, t_island island, int **cache_grid, t_dequeue *dequeue)
{
	int	x;
	int	y;
	int	island_bitmap;
	int	islands_bitmap_wihout_island;
	int	counter;

	island_bitmap = grid[island.pos.y][island.pos.x];
	islands_bitmap_wihout_island = 0b11111111111111111111111111111111 ^ island_bitmap;
	bfs(grid, island, cache_grid, dequeue);
	counter = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (cache_grid[y][x] == -1)
				grid[y][x] &= islands_bitmap_wihout_island;
			else
				counter++;
			x++;
		}
		y++;
	}
	if (counter == island.target_size)
		fill_island(grid, island, cache_grid);
}

void	use_bfs_to_limit_islands(int **grid, t_island *islands, int **cache_grid, t_dequeue *dequeue)
{
	int	i;

	i = 0;
	while (islands[i].id != -1)
	{
		use_bfs_to_limit_island(grid, islands[i], cache_grid, dequeue);
		i++;
	}
}

void	bfs(int **grid, t_island island, int **cache_grid, t_dequeue *dequeue)
{
	t_pos	cur_pos;
	t_pos	next_pos;
	int		max_cost;
	int		island_bitmap;

	initialise_dequeue(dequeue);
	init_cache_grid(grid, cache_grid);
	island.pos.cost = 0;
	max_cost = island.target_size - island.current_size;
	island_bitmap = grid[island.pos.y][island.pos.x];
	push_back(dequeue, island.pos);
	while (!is_empty(dequeue))
	{
		cur_pos = pop_front(dequeue);
		if (cur_pos.cost > max_cost || cache_grid[cur_pos.y][cur_pos.x] != -1 || (grid[cur_pos.y][cur_pos.x] & island_bitmap) == 0)
			continue ;
		cache_grid[cur_pos.y][cur_pos.x] = cur_pos.cost;
		if (cur_pos.y > 0)
		{
			next_pos = cur_pos;
			next_pos.y -= 1;
			if (grid[next_pos.y][next_pos.x] != island_bitmap)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
		if (cur_pos.x > 0)
		{
			next_pos = cur_pos;
			next_pos.x -= 1;
			if (grid[next_pos.y][next_pos.x] != island_bitmap)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
		if (grid[cur_pos.y + 1])
		{
			next_pos = cur_pos;
			next_pos.y += 1;
			if (grid[next_pos.y][next_pos.x] != island_bitmap)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
		if (grid[cur_pos.y][cur_pos.x + 1] != -1)
		{
			next_pos = cur_pos;
			next_pos.x += 1;
			if (grid[next_pos.y][next_pos.x] != island_bitmap)
				next_pos.cost++;
			push_back(dequeue, next_pos);
		}
	}
}
