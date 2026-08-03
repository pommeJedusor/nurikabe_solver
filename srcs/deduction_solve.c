#include "nurikabe_solver.h"

void	full_island_borders_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	nb_islands;
	int	water;
	int	island_id;

	y = 0;
	nb_islands = get_islands_length(islands);
	water = 1 << nb_islands;
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
			island_id = get_trailing_zeros(grid[y][x]);
			if (islands[island_id].current_size == islands[island_id].target_size)
			{
				if (y != 0 && grid[y - 1][x] != grid[y][x])
					grid[y - 1][x] = water;
				if (x != 0 && grid[y][x - 1] != grid[y][x])
					grid[y][x - 1] = water;
				if (grid[y + 1] && grid[y + 1][x] != grid[y][x])
					grid[y + 1][x] = water;
				if (grid[y][x + 1] != -1 && grid[y][x + 1] != grid[y][x])
					grid[y][x + 1] = water;
			}
			x++;
		}
		y++;
	}
}

// if 2 different islands are next to the same square then that square is water
void	common_border_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	island_counter;
	int	water;

	water = 1 << get_islands_length(islands);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			island_counter = 0;
			if (y > 0 && count_bits(grid[y - 1][x]) == 1 && grid[y - 1][x] != water)
				island_counter |= grid[y - 1][x];
			if (x > 0 && count_bits(grid[y][x - 1]) == 1 && grid[y][x - 1] != water)
				island_counter |= grid[y][x - 1];
			if (grid[y + 1] && count_bits(grid[y + 1][x]) == 1 && grid[y + 1][x] != water)
				island_counter |= grid[y + 1][x];
			if (grid[y][x + 1] != -1 && count_bits(grid[y][x + 1]) == 1 && grid[y][x + 1] != water)
				island_counter |= grid[y][x + 1];
			if (count_bits(island_counter) > 1)
				grid[y][x] = water;
			x++;
		}
		y++;
	}
}

// checks for all the squares one island can go to using dikjstra
// if on a 2x2 three of the squares are alerady water then the last one can't be
