#include "nurikabe_solver.h"

void	island_borders_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	nb_islands;
	int	islands_id;
	int	water;
	int	border;

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
// checks for all the squares one island can go to using dikjstra
// if on a 2x2 three of the squares are alerady water then the last one can't be
