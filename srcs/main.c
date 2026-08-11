#include "nurikabe_solver.h"

int	solves_from_file_content(char *file_content)
{
	char		**lines;
	t_island	*islands;
	unsigned long long			***grid;
	unsigned long long			***cache_grid;
	int			i;
	int			bitset_size;
	t_dequeue	dequeue;
	int			backtracking_result;

	if (file_content == 0)
		return (1);
	if (is_input_valid(file_content) == 0)
	{
		free(file_content);
		return (1);
	}
	lines = split_lines(file_content);
	free(file_content);
	if (lines == 0)
		return (1);
	i = 0;
	while (lines[i])
		i++;
	islands = get_islands(lines);
	if (islands == 0)
	{
		free_lines(lines);
		return (1);
	}
	bitset_size = get_bitset_size_from_islands(islands);
	grid = get_empty_grid(i, bitset_size);
	if (grid == 0)
	{
		free_lines(lines);
		free(islands);
		return (1);
	}
	cache_grid = get_empty_grid(i, bitset_size);
	if (cache_grid == 0)
	{
		free_lines(lines);
		free(islands);
		free_grid(grid);
		return (1);
	}
	initialise_grid(grid, islands);
	backtracking_result = backtracking(grid, islands, cache_grid, dequeue);
	free_grid(grid);
	free_grid(cache_grid);
	free(islands);
	free_lines(lines);
	return (backtracking_result == 0);
}

int	main(int argc, char **argv)
{
	char		*file_content;
	int			i;
	int			backtracking_result;
	int			final_result;

	final_result = 0;
	if (argc >= 2)
	{
		i = 1;
		while (i < argc)
		{
			if (i != 1)
				printf("\n");
			if (argc != 2 && argv[i][0] == '-' && argv[i][1] == '\0')
				printf("<-- standard input -->\n");
			else if (argc != 2)
				printf("<-- %s -->\n", argv[i]);
			if (argv[i][0] == '-' && argv[i][1] == '\0')
				file_content = get_stdin_content();
			else
				file_content = get_file_content(argv[i]);
			backtracking_result = solves_from_file_content(file_content);
			if (backtracking_result == 1)
				fprintf(stderr, "map invalid or failed to solve map\n");
			final_result |= backtracking_result;
			i++;
		}
	}
	else
	{
		final_result = solves_from_file_content(get_stdin_content());
		if (final_result == 1)
			fprintf(stderr, "map invalid or failed to solve map\n");
	}
	return (final_result);
}
