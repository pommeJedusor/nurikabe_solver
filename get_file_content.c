#include "nurikabe_solver.h"

int	get_file_size(char *file_name)
{
	int		fd;
	int		nb_bytes_read;
	int		size;
	char	buffer[BUFFER_SIZE];

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (-1);
	size = 0;
	nb_bytes_read = BUFFER_SIZE;
	while (nb_bytes_read == BUFFER_SIZE)
	{
		nb_bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_bytes_read == -1)
		{
			close(fd);
			return (-1);
		}
		size += nb_bytes_read;
	}
	close(fd);
	return (size);
}

int	read_file_content(char *file_name, char *buffer, int file_size)
{
	int		fd;
	int		nb_bytes_read;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	nb_bytes_read = read(fd, buffer, file_size);
	if (nb_bytes_read == -1)
	{
		close(fd);
		return (1);
	}
	buffer[file_size] = '\0';
	close(fd);
	return (0);
}

char	*get_file_content(char *file_name)
{
	int		file_size;
	char	*file_content;

	file_size = get_file_size(file_name);
	if (file_size == -1)
		return (0);
	file_content = malloc(sizeof(char) * (file_size + 1));
	if (file_content == 0)
		return (0);
	if (read_file_content(file_name, file_content, file_size) != 0)
	{
		free(file_content);
		return (0);
	}
	return (file_content);
}
