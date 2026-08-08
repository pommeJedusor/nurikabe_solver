#include "nurikabe_solver.h"

int	main(int argc, char **argv)
{
	char		*file_name;
	char		*file_content;
	char		**lines;
	t_island	*islands;
	int			**grid;
	int			**cache_grid;
	int			i;
	t_dequeue	dequeue;

	file_name = "maps/map3";
	if (argc == 2)
		file_name = argv[1];
	file_content = get_file_content(file_name);
	if (file_content == 0)
		return (1);
	lines = split_lines(file_content);
	free(file_content);
	if (file_content == 0)
		return (1);
	i = 0;
	while (lines[i])
	{
		//printf("%s\n", lines[i]);
		i++;
	}
	//printf("\n");

	islands = get_islands(lines);

	grid = get_empty_grid(i);
	cache_grid = get_empty_grid(i);
	initialise_grid(grid, islands);

	backtracking(grid, islands, cache_grid, dequeue);
	//deduction_solve(grid, islands, cache_grid, &dequeue);
	//print_islands(islands);
	//print_grid(grid);
	//printf("\n");

	//print_solution(grid, islands);
	//printf("\n");

	free_grid(grid);
	free_grid(cache_grid);
	free(islands);
	free_lines(lines);
}
