#include "nurikabe_solver.h"

int	main(void)
{
	char		*file_content;
	char		**lines;
	t_island	*islands;
	int			**grid;

	file_content = get_file_content("maps/map1");
	if (file_content == 0)
		return (1);
	lines = split_lines(file_content);
	free(file_content);
	if (file_content == 0)
		return (1);
	printf("%s\n", lines[0]);
	printf("%s\n", lines[1]);
	printf("%s\n", lines[2]);
	printf("%s\n", lines[3]);
	printf("%s\n", lines[4]);
	islands = get_islands(lines);
	print_islands(islands);
	grid = get_empty_grid(5);
	print_grid(grid);
	free_grid(grid);
	free(islands);
	free_lines(lines);
}
