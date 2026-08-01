#include <stdio.h>
#include "nurikabe_solver.h"

int	main(void)
{
	char	*file_content;

	file_content = get_file_content("maps/map1");
	if (file_content == 0)
	{
		return (1);
	}
	printf("%s", file_content);
	free(file_content);
}
