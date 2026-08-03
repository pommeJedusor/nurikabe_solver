#include "nurikabe_solver.h"

void	island_borders_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	islands_id;
	int	water;
	int	border;

	y = 0;
	water = 1 << get_islands_length(islands);
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (grid[y][x] == water || count_bits(grid[y][x]) != 1)
			{
				x++;
				continue ;
			}
			border = water | grid[y][x];
			islands_id = get_trailing_zeros(grid[y][x]);
			if (islands[islands_id].current_size == islands[islands_id].target_size)
				border = water;
			if (y != 0)
				grid[y - 1][x] &= border;
			if (x != 0)
				grid[y][x - 1] &= border;
			if (grid[y + 1])
				grid[y + 1][x] &= border;
			if (grid[y][x + 1] != -1)
				grid[y][x + 1] &= border;
			x++;
		}
		y++;
	}
}

void	no_water_square_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	water_counter;
	int	water;

	water = 1 << get_islands_length(islands);
	y = 0;
	while (grid[y] && grid[y + 1])
	{
		x = 0;
		while (grid[y][x] != -1 && grid[y][x + 1] != -1)
		{
			water_counter = 0;
			if (grid[y][x] == water)
				water_counter++;
			if (grid[y + 1][x] == water)
				water_counter++;
			if (grid[y][x + 1] == water)
				water_counter++;
			if (grid[y + 1][x + 1] == water)
				water_counter++;
			if (water_counter == 3)
			{
				grid[y][x] = water;
				grid[y + 1][x] = water;
				grid[y][x + 1] = water;
				grid[y + 1][x + 1] = water;
			}
			x++;
		}
		y++;
	}
}

// checks for all the squares one island can go to using dikjstra
// if number of available square for an island is equal to target_size - current_size
// link water/islands
