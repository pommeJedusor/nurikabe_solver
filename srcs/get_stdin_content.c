#include "nurikabe_solver.h"

char	*get_stdin_content()
{
	char	*stdin_content;
	int		size;
	int		nb_bytes_read;

	stdin_content = 0;
	size = 0;
	nb_bytes_read = BUFFER_SIZE;
	while (nb_bytes_read == BUFFER_SIZE)
	{
		stdin_content = realloc(stdin_content, sizeof(char) * (size + BUFFER_SIZE));
		if (stdin_content == 0)
			return (0);
		nb_bytes_read = read(STDIN_FILENO, &stdin_content[size], BUFFER_SIZE);
		size += nb_bytes_read;
	}
	stdin_content[size] = '\0';
	return (stdin_content);
}
