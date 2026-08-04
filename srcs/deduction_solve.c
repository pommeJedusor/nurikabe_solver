#include "nurikabe_solver.h"

void	island_borders_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	islands_id;
	int	border;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (grid[y][x] == WATER || count_bits(grid[y][x]) != 1)
			{
				x++;
				continue ;
			}
			border = WATER | grid[y][x];
			islands_id = get_trailing_zeros(grid[y][x]) - 1;
			if (islands[islands_id].current_size == islands[islands_id].target_size)
				border = WATER;
			if (y != 0 && grid[y - 1][x] != grid[y][x])
				grid[y - 1][x] &= border;
			if (x != 0 && grid[y][x - 1] != grid[y][x])
				grid[y][x - 1] &= border;
			if (grid[y + 1] && grid[y + 1][x] != grid[y][x])
				grid[y + 1][x] &= border;
			if (grid[y][x + 1] != -1 && grid[y][x + 1] != grid[y][x])
				grid[y][x + 1] &= border;
			x++;
		}
		y++;
	}
}

void	no_water_square_rule(int **grid)
{
	int	x;
	int	y;
	int	water_counter;

	y = 0;
	while (grid[y] && grid[y + 1])
	{
		x = 0;
		while (grid[y][x] != -1 && grid[y][x + 1] != -1)
		{
			water_counter = 0;
			if (grid[y][x] == WATER)
				water_counter++;
			if (grid[y + 1][x] == WATER)
				water_counter++;
			if (grid[y][x + 1] == WATER)
				water_counter++;
			if (grid[y + 1][x + 1] == WATER)
				water_counter++;
			if (water_counter == 3)
			{
				if (grid[y][x] != WATER && (grid[y][x] & WATER))
					grid[y][x] ^= WATER;
				if (grid[y + 1][x] != WATER && (grid[y + 1][x] & WATER))
					grid[y + 1][x] ^= WATER;
				if (grid[y][x + 1] != WATER && (grid[y][x + 1] & WATER))
					grid[y][x + 1] ^= WATER;
				if (grid[y + 1][x + 1] != WATER && (grid[y + 1][x + 1] & WATER))
					grid[y + 1][x + 1] ^= WATER;
			}
			x++;
		}
		y++;
	}
}

int	get_grid_hash(int **grid)
{
	int	sum;
	int	x;
	int	y;

	sum = 0;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			sum += count_bits(grid[y][x]);
			x++;
		}
		y++;
	}
	return (sum);
}

void	deduction_solve(int **grid, t_island *islands, int **cache_grid, t_dequeue *dequeue)
{
	int	prev_hash;
	int	hash;

	prev_hash = -1;
	hash = get_grid_hash(grid);
	while (prev_hash != hash)
	{
		island_borders_rule(grid, islands);
		no_water_square_rule(grid);
		use_bfs_to_limit_islands(grid, islands, cache_grid, dequeue);
		extend_islands(grid, cache_grid, dequeue, islands);
		prev_hash = hash;
		hash = get_grid_hash(grid);
	}
}

// extends group as long as the island isn't full and there is only one square it can extend to
