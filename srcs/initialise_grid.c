#include <nurikabe_solver.h>

void	get_full_bitmap_for_islands(int nb_islands, unsigned long long *bitmap)
{
	int	i;

	i = 0;
	while (i < nb_islands)
	{
		if (i % 64 == 0)
			bitmap[i / 64ULL] = 0;
		bitmap[i / 64ULL] |= 1ULL << (i % 64ULL);
		i++;
	}
}

void	initialise_grid(unsigned long long ***grid, t_island *islands)
{
	int					i;
	int					nb_island;
	int					x;
	int					y;
	unsigned long long	island_bitmap[MAX_BITSET_SIZE];

	nb_island = get_islands_length(islands);
	get_full_bitmap_for_islands(nb_island, island_bitmap);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			copy_bitset(grid[y][x], island_bitmap, get_bitset_size_from_islands(islands));
			x++;
		}
		y++;
	}
	i = 1;
	while (islands[i].id != -1)
	{
		copy_bitset(grid[islands[i].pos.y][islands[i].pos.x], EMPTY_BITSET, get_bitset_size_from_islands(islands));
		grid[islands[i].pos.y][islands[i].pos.x][islands[i].id / 64] = 1ULL << (islands[i].id % 64ULL);
		i++;
	}
}
