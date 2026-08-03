#include <nurikabe_solver.h>

int	get_islands_length(t_island *array)
{
	int	i;

	i = 0;
	while (array[i].id != -1)
		i++;
	return (i);
}

int	get_full_bitmap_for_islands(int nb_islands)
{
	int	bitmap;

	bitmap = 0;
	while (nb_islands >= 0)
	{
		bitmap |= 1 << nb_islands;
		nb_islands--;
	}
	return (bitmap);
}

void	initialise_grid(int **grid, t_island *islands)
{
	int	i;
	int	island_bitmap;
	int	nb_island;
	int	x;
	int	y;

	nb_island = get_islands_length(islands);
	island_bitmap = get_full_bitmap_for_islands(nb_island);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			grid[y][x] = island_bitmap;
			x++;
		}
		y++;
	}
	i = 0;
	while (islands[i].id != -1)
	{
		grid[islands[i].pos.y][islands[i].pos.x] = 0b10 << islands[i].id;
		i++;
	}
}
