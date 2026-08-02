#include "nurikabe_solver.h"

int	count_islands(char **lines)
{
	int	x;
	int	y;
	int	counter;

	counter = 0;
	y = 0;
	while (lines[y])
	{
		x = 0;
		while (lines[y][x])
		{
			if (lines[y][x] != '_')
				counter++;
			x++;
		}
		y++;
	}
	return (counter);
}

void	print_islands(t_island *islands)
{
	int	i;

	i = 0;
	while (islands[i].id != -1)
	{
		printf("id: %d, current_size: %d target_size: %d, x: %d, y: %d\n", islands[i].id, islands[i].current_size, islands[i].target_size, islands[i].pos.x, islands[i].pos.y);
		i++;
	}
}

t_island	*get_islands(char **lines)
{
	int			x;
	int			y;
	int			i;
	int			nb_islands;
	t_island	*islands;

	nb_islands = count_islands(lines);
	islands = malloc(sizeof(t_island) * (nb_islands + 1));
	if (islands == 0)
		return (0);
	i = 0;
	y = 0;
	while (lines[y])
	{
		x = 0;
		while (lines[y][x])
		{
			if (lines[y][x] != '_')
			{
				islands[i].id = i;
				islands[i].current_size = 1;
				islands[i].target_size = lines[y][x] - '0';
				islands[i].pos.x = x;
				islands[i].pos.y = y;
				i++;
			}
			x++;
		}
		y++;
	}
	islands[i].id = -1;
	return (islands);
}
