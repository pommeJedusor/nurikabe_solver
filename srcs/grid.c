#include "nurikabe_solver.h"

int	get_grid_size(int **grid)
{
	int	i;

	i = 0;
	while (grid[i])
		i++;
	return (i);
}

// returns NULL pointer for convenience
int	**free_grid(int **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (0);
}

int	**get_empty_grid(int size)
{
	int	**grid;
	int	y;
	int	x;

	grid = malloc(sizeof(int *) * (size + 1));
	if (grid == 0)
		return (0);
	y = 0;
	while (y < size)
	{
		grid[y] = malloc(sizeof(int) * (size + 1));
		if (grid[y] == 0)
			return (free_grid(grid));
		x = 0;
		while (x < size)
		{
			grid[y][x] = 0;
			x++;
		}
		grid[y][x] = -1;
		y++;
	}
	grid[y] = 0;
	return (grid);
}

int	**clone_grid(int **grid)
{
	int	**clone;
	int	y;
	int	x;

	clone = get_empty_grid(get_grid_size(grid));
	if (clone == 0)
		return (0);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			clone[y][x] = grid[y][x];
			x++;
		}
		y++;
	}
	return (clone);
}

void	print_grid(int **grid)
{
	int		x;
	int		y;
	char	digit;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			digit = count_bits(grid[y][x]) + '0';
			write(1, &digit, 1);
			x++;
		}
		write(1, "\n", 1);
		y++;
	}
}

void	print_solution(int **grid, t_island *islands)
{
	int		x;
	int		y;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x] != -1)
		{
			if (grid[y][x] == WATER)
				printf("~");
			else if (count_bits(grid[y][x]) == 1)
				printf("%c", islands[get_trailing_zeros(grid[y][x])].target_size + '0');
			else
				printf("?");
			x++;
		}
		printf("\n");
		y++;
	}
}
