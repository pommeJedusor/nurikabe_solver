#include "nurikabe_solver.h"

int	count_bits(int number)
{
	int	counter;

	counter = 0;
	while (number)
	{
		number &= number - 1;
		counter++;
	}
	return (counter);
}

void	full_island_borders_rule(int **grid, t_island *islands)
{
	int	x;
	int	y;
	int	nb_islands;

	y = 0;
	nb_islands = get_islands_length(islands);
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (grid[y][x] == 1 << nb_islands || count_bits(grid[y][x]) != 1)
			{
				x++;
				continue ;
			}
			if (islands[grid[y][x]].current_size == islands[grid[y][x]].target_size)
			{
				if (y != 0 && grid[y - 1][x] != grid[y][x])
					grid[y - 1][x] = 1 << nb_islands;
				if (x != 0 && grid[y][x - 1] != grid[y][x])
					grid[y][x - 1] = 1 << nb_islands;
				if (grid[y + 1] && grid[y + 1][x] != grid[y][x])
					grid[y + 1][x] = 1 << nb_islands;
				if (grid[y][x + 1] != -1 && grid[y][x + 1] != grid[y][x])
					grid[y][x + 1] = 1 << nb_islands;
			}
			x++;
		}
		y++;
	}
}
