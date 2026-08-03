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

	file_name = "maps/map1";
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
		printf("%s\n", lines[i]);
		i++;
	}

	islands = get_islands(lines);
	print_islands(islands);

	grid = get_empty_grid(i);
	cache_grid = get_empty_grid(i);
	initialise_grid(grid, islands);
	print_grid(grid);
	printf("\n");

	island_borders_rule(grid, islands);
	print_grid(grid);
	printf("\n");

	no_water_square_rule(grid);
	print_grid(grid);
	printf("\n");

	use_bfs_to_limit_islands(grid, islands, cache_grid, &dequeue);
	no_water_square_rule(grid);
	print_islands(islands);
	print_grid(grid);
	printf("\n");
	use_bfs_to_limit_islands(grid, islands, cache_grid, &dequeue);
	island_borders_rule(grid, islands);
	print_islands(islands);
	print_grid(grid);
	printf("\n");

	print_solution(grid);
	printf("\n");

	free_grid(grid);
	free_grid(cache_grid);
	free(islands);
	free_lines(lines);
}
