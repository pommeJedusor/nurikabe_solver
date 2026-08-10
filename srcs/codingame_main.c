#include "nurikabe_solver.h"

char	**get_lines_codingame(int nb_lines)
{
	int		i;
	int		j;
	char	**lines;

	lines = malloc(sizeof(char *) * (nb_lines + 1));
	if (lines == 0)
		return (0);
	while (i < nb_lines)
	{
		lines[i] = malloc(sizeof(char) * 33);
		if (lines[i] == 0)
		{
			free_lines(lines);
			return (0);
		}
		scanf("%[^\n]", lines[i]); fgetc(stdin);
		j = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] == '.')
				lines[i][j] = '_';
			j++;
		}
		i++;
	}
	lines[i] = 0;
	return (lines);
}

int	main()
{
	int			nb_lines;
	char		**lines;
	t_island	*islands;
	unsigned long long			***grid;
	unsigned long long			***cache_grid;
	int			i;
	int			bitset_size;
	t_dequeue	dequeue;

	scanf("%d", &nb_lines); fgetc(stdin);
	lines = get_lines_codingame(nb_lines);
	if (lines == 0)
		return (1);
	islands = get_islands(lines);
	if (islands == 0)
	{
		free_lines(lines);
		return (1);
	}

	bitset_size = get_bitset_size_from_islands(islands);
	grid = get_empty_grid(nb_lines, bitset_size);
	if (grid == 0)
	{
		free_lines(lines);
		free(islands);
		return (1);
	}
	cache_grid = get_empty_grid(nb_lines, bitset_size);
	if (cache_grid == 0)
	{
		free_lines(lines);
		free(islands);
		free_grid(grid);
		return (1);
	}
	initialise_grid(grid, islands);

	backtracking(grid, islands, cache_grid, dequeue);
	//deduction_solve(grid, islands, cache_grid, &dequeue);
	//deduction_solve(grid, islands, cache_grid, &dequeue);
	//deduction_solve(grid, islands, cache_grid, &dequeue);
	//print_islands(islands);
	//print_grid(grid, islands);
	//print_solution(grid, islands);
	//printf("\n");

	//print_solution(grid, islands);
	//printf("\n");

	free_grid(grid);
	free_grid(cache_grid);
	free(islands);
	free_lines(lines);
}
