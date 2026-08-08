#include "nurikabe_solver.h"

int	get_islands_length(t_island *array)
{
	int	i;

	i = 0;
	while (array[i].id != -1)
		i++;
	return (i);
}

t_island	*clone_islands(t_island *array)
{
	t_island	*clone;
	int 		i;

	clone = malloc(sizeof(t_island) * (get_islands_length(array) + 1));
	if (clone == 0)
		return (0);
	i = 0;
	while (array[i].id != -1)
	{
		clone[i] = array[i];
		i++;
	}
	clone[i] = array[i];
	return (clone);
}

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

int	get_nb_lines(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}

t_island	*get_islands(char **lines)
{
	int			x;
	int			y;
	int			i;
	int			nb_islands;
	t_island	*islands;

	nb_islands = count_islands(lines);
	islands = malloc(sizeof(t_island) * (nb_islands + 2));
	if (islands == 0)
		return (0);
	islands[0].id = 0;
	islands[0].current_size = 0;
	islands[0].target_size = get_nb_lines(lines) * get_nb_lines(lines);
	islands[0].pos.x = -1;
	i = 1;
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
				islands[0].target_size -= lines[y][x] - '0';
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
