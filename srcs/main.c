#include <stdio.h>
#include "nurikabe_solver.h"

int	main(void)
{
	char	*file_content;
	char	**lines;

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
	free_lines(lines);
}
