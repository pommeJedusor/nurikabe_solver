#include "nurikabe_solver.h"

int	get_grid_size(unsigned long long ***grid)
{
	int	i;

	i = 0;
	while (grid[i])
		i++;
	return (i);
}

// returns NULL pointer for convenience
unsigned long long	***free_grid(unsigned long long ***grid)
{
	int	y;
	int	x;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			free(grid[y][x]);
			x++;
		}
		free(grid[y]);
		y++;
	}
	free(grid);
	return (0);
}

unsigned long long	***get_empty_grid(int size, int bitset_size)
{
	unsigned long long	***grid;
	int					x;
	int					y;

	grid = malloc(sizeof(unsigned long long **) * (size + 1));
	if (grid == 0)
		return (0);
	y = 0;
	while (y < size)
	{
		grid[y] = malloc(sizeof(unsigned long long *) * (size + 1));
		grid[y + 1] = 0;
		if (grid[y] == 0)
			return (free_grid(grid));
		x = 0;
		while (x < size)
		{
			grid[y][x] = malloc(sizeof(unsigned long long) * bitset_size);
			if (grid[y][x] == 0)
				return (free_grid(grid));
			copy_bitset(grid[y][x], EMPTY_BITSET, bitset_size);
			x++;
		}
		grid[y][x] = 0;
		y++;
	}
	return (grid);
}

unsigned long long	***clone_grid(unsigned long long ***grid, int bitset_size)
{
	unsigned long long	***clone;
	int	x;
	int	y;
	int	z;

	clone = get_empty_grid(get_grid_size(grid), bitset_size);
	if (clone == 0)
		return (0);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			z = 0;
			while (z < bitset_size)
			{
				clone[y][x][z] = grid[y][x][z];
				z++;
			}
			x++;
		}
		y++;
	}
	return (clone);
}

void	print_grid(unsigned long long ***grid, t_island *islands)
{
	int		x;
	int		y;
	char	digit;
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			digit = count_bitset_bits(grid[y][x], bitset_size) + '0';
			write(1, &digit, 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

void	print_solution(unsigned long long ***grid, t_island *islands)
{
	int		x;
	int		y;
	int		bitset_size;

	bitset_size = get_bitset_size_from_islands(islands);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{

			if (cmp_bitsets(grid[y][x], WATER, bitset_size) == 0)
				printf("~");
			else if (count_bitset_bits(grid[y][x], bitset_size) == 1)
				printf("%c", islands[get_bitset_trailing_zeros(grid[y][x], bitset_size)].target_size + '0');
			else
				printf("?");
			x++;
		}
		printf("\n");
		y++;
	}
}
